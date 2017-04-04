/**
  * \file msgstorage.h
  * \author Christian Neuberger
  * \date 22.11.2016
  *
  * \brief Dynamic storage of huge amounts of messages with automated serializing to and from temporary files
  */
#ifndef MSGSTORAGE_H
#define MSGSTORAGE_H

class MainWindow;
class FileParser;

#include <QObject>
#include "TimestampedMsg.h"
#include "datastorage.h"

#include "IFileParsable.h"
#include "fileparser.h"

/**
 * \brief MsgStorage to store huge numbers of messages
 * 
 * \todo Make template!.. somehow
 */
template<class MsgType>
class TemplateMsgStorage : public IFileParsable
{
public:
    /**
     * @brief Constructs a MsgStorage object with the given metrics
     *
     */
    TemplateMsgStorage() :
        msgStore(1000,3)
    {
    }

    virtual ~TemplateMsgStorage(){}
    /**
     * @brief at
     * @param index
     * @return
     *
     * \note This function returns a copy of the retrieved Msg because
     *       it cannot be guaranteed that the retrieved Msg is held in
     *       RAM; it can even not be guaranteed that a reference would
     *       be up to date...
     */
    MsgType at(const size_t index)
    {
        return msgStore.at(index);
    }
    /* Msg at(const size_t index) const; */

    MsgType operator[](const size_t index)
    {
        return msgStore[index];
    }

    /**
     * \brief clears the MsgStorage
     * 
     * \warning This does not free the contained elements!
     */
    void clear()
    {
        msgStore.clear();
        emit sgnl_StoreCleared();
    }

    /**
     * \brief returns the current size of the MsgStorage
     */
    int size() const
    {
        return msgStore.size();
    }
    /**
     * \brief returns whether the MsgStorage is empty
     */
    bool isEmpty() const
    {
        return msgStore.isEmpty();
    }

    void appendMsg(const MsgType &newMsg)
    {
        msgStore.append(newMsg);
        emit sgnl_MsgAdded(newMsg);
    }

    /**
     * \brief parses the whole MsgStorage to a JSON document
     */
    QJsonDocument ParseToJson() const
    {
        return QJsonDocument();
    }
    /**
     * \brief reads in a MsgStorage from a JSON document
     */
    bool ParseFromJson(const QJsonArray &jsonMsgsArray)
    {
        return false;
    }


    QString saveMsgStorage(const QString &saveLocation)
    {
        return msgStore.saveDataStorage(saveLocation);
    }

signals:
    virtual void sgnl_MsgAdded(const MsgType &addedMsg) = 0;
    virtual void sgnl_StoreCleared() = 0;

protected slots:
    virtual void slt_addMsg(const MsgType &newMsg)
    {
        appendMsg(newMsg);
    }

private:
friend class MainWindow;
    DataStorage<MsgType> msgStore;
};

class MsgStorage : public QObject, public TemplateMsgStorage<Msg>
{
    Q_OBJECT
public:
    MsgStorage(){}

    void accept(FileParser *visitor)
    {
        visitor->visit(*this);
    }
signals:
    virtual void sgnl_MsgAdded(const Msg &addedMsg);
    virtual void sgnl_StoreCleared();

private slots:
    virtual void slt_addMsg(const Msg &newMsg)
    {
        TemplateMsgStorage<Msg>::slt_addMsg(newMsg);
    }

private:
    friend class MainWindow;
};

class TimestampedMsgStorage :
    public QObject,
    public TemplateMsgStorage<TimestampedMsg>
{
    Q_OBJECT
public:
    TimestampedMsgStorage(){}

    void accept(FileParser *visitor)
    {
        visitor->visit(*this);
    }

signals:
    virtual void sgnl_MsgAdded(const TimestampedMsg &addedMsg);
    virtual void sgnl_StoreCleared();

private slots:
    virtual void slt_addMsg(const TimestampedMsg &newMsg)
    {
        TemplateMsgStorage<TimestampedMsg>::slt_addMsg(newMsg);
    }

private:
    friend class MainWindow;
};
#endif // MSGSTORAGE_H
