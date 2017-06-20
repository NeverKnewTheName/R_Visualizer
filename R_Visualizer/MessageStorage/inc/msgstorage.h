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

#include "IReportable.h"

#include "IFileParsable.h"
#include "fileparser.h"

/**
 * @defgroup MsgStorageGroup Message Storage
 * 
 * @{
 */

/**
 * \brief MsgStorage to store huge numbers of messages
 * 
 * \todo Make template!.. somehow
 */
template<class MsgType>
class TemplateMsgStorage :
    public IFileParsable
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
    virtual MsgType at(const size_t index)
    {
        return msgStore.at(index);
    }

    virtual MsgType operator[](const size_t index)
    {
        return msgStore[index];
    }

    /**
     * \brief clears the MsgStorage
     * 
     * \warning This does not free the contained elements!
     */
    virtual void clear()
    {
        msgStore.clear();
        emit sgnl_StoreCleared();
    }

    /**
     * \brief returns the current size of the MsgStorage
     */
    virtual int size() const
    {
        return msgStore.size();
    }
    /**
     * \brief returns whether the MsgStorage is empty
     */
    virtual bool isEmpty() const
    {
        return msgStore.isEmpty();
    }

    virtual void appendMsg(const MsgType &newMsg)
    {
        msgStore.append(newMsg);
        emit sgnl_MsgAdded(newMsg, size()-1);
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

//signals:
    virtual void sgnl_MsgAdded(const MsgType &addedMsg, const int index) = 0;
    virtual void sgnl_StoreCleared() = 0;

public:// slots:
    virtual void slt_addMsg(const MsgType &newMsg)
    {
        appendMsg(newMsg);
    }

private:
    DataStorage<MsgType> msgStore;
};

class MsgStorage :
        public QObject,
        public TemplateMsgStorage<Msg>,
        public IReportable
{
    Q_OBJECT
    Q_INTERFACES(IReportable)
public:
    MsgStorage(QObject *parent = Q_NULLPTR) : QObject(parent){}

    virtual void appendMsg(const Msg &msgToAppend)
    {
        TemplateMsgStorage<Msg>::appendMsg(msgToAppend);
        emit sgnl_ReportInfo(
                QString("Message added to MsgStorage: %1")
                    .arg(static_cast<QString>(msgToAppend))
                );
    }

    void clear()
    {
        TemplateMsgStorage<Msg>::clear();
        emit sgnl_ReportInfo(
                QString("MsgStorage cleared")
                );
    }

    void accept(FileParser *visitor)
    {
        visitor->visit(this);
    }
signals:
    virtual void sgnl_MsgAdded(const Msg &addedMsg, const int index);
    virtual void sgnl_StoreCleared();

public slots:
    virtual void slt_addMsg(const IMsg &newMsg)
    {
        Msg tempMsg;

        tempMsg.setMsgID(newMsg.getMsgID());
        tempMsg.setMsgCode(newMsg.getMsgCode());
        tempMsg.setMsgData(newMsg.getMsgData());

        appendMsg(tempMsg);
    }

signals:
    void sgnl_ReportError(const QString &errorString);
    void sgnl_ReportWarning(const QString &warningString);
    void sgnl_ReportInfo(const QString &infoString);
};

class TimestampedMsgStorage :
    public QObject,
    public TemplateMsgStorage<TimestampedMsg>,
    public IReportable
{
    Q_OBJECT
    Q_INTERFACES(IReportable)
public:
    TimestampedMsgStorage(QObject *parent = Q_NULLPTR) : QObject(parent){}

    virtual void appendMsg(const TimestampedMsg &msgToAppend)
    {
        TemplateMsgStorage<TimestampedMsg>::appendMsg(msgToAppend);
        emit sgnl_ReportInfo(
                QString("Message added to MsgStorage: %1")
                    .arg(static_cast<QString>(msgToAppend))
                );
    }

    void clear()
    {
        TemplateMsgStorage<TimestampedMsg>::clear();
        emit sgnl_ReportInfo(
                QString("MsgStorage cleared")
                );
    }


    void accept(FileParser *visitor)
    {
        visitor->visit(this);
    }

signals:
    virtual void sgnl_MsgAdded(const TimestampedMsg &addedMsg, const int index);
    virtual void sgnl_StoreCleared();

public slots:
    virtual void slt_addMsg(const ITimestampedMsg &newMsg)
    {
        TimestampedMsg tempMsg;

        tempMsg.setMsgID(newMsg.getMsgID());
        tempMsg.setMsgCode(newMsg.getMsgCode());
        tempMsg.setMsgData(newMsg.getMsgData());
        tempMsg.setTimestamp(newMsg.getTimestamp());

        appendMsg(tempMsg);
    }

    // IReportable interface
signals:
    void sgnl_ReportError(const QString &errorString);
    void sgnl_ReportWarning(const QString &warningString);
    void sgnl_ReportInfo(const QString &infoString);
};

/**
 * @}
 */

#endif // MSGSTORAGE_H
