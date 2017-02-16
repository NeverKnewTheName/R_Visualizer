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
#include "msg.h"
#include "datastorage.h"

#include "fileparsable.h"

/**
 * \brief MsgStorage to store huge numbers of messages
 * 
 */
class MsgStorage : public QObject, public FileParsable
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a MsgStorage object with the given metrics
     *
     */
    MsgStorage(QObject *parent = Q_NULLPTR);

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
    Msg at(const size_t index);

    Msg operator[](const size_t index);

    /**
     * \brief clears the MsgStorage
     * 
     * \warning This does not free the contained elements!
     */
    void clear();

    /**
     * \brief returns the current size of the MsgStorage
     */
    int size() const;
    /**
     * \brief returns whether the MsgStorage is empty
     */
    bool isEmpty() const;

    void appendMsg(const Msg &newMsg);

    /**
     * \brief parses the whole MsgStorage to a JSON document
     */
    QJsonDocument ParseToJson() const;
    /**
     * \brief reads in a MsgStorage from a JSON document
     */
    bool ParseFromJson(const QJsonArray &jsonMsgsArray);

    void accept(FileParser *visitor);

    QString saveMsgStorage(const QString &saveLocation);

signals:
    void sgnl_MsgAdded(const Msg &addedMsg);
    void sgnl_StoreCleared();

private slots:
    void slt_addMsg(const Msg &newMsg);

private:
friend class MainWindow;
    DataStorage<Msg> msgStore;
};

#endif // MSGSTORAGE_H
