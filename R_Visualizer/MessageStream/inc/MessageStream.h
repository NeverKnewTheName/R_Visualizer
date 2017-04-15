/**
 * @file MessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The MessageStream module
 */
#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QObject>

#include "IMessageStream.h"
#include "IMsgStreamStore.h"

/**
 * @brief The MessageStream
 */
class MessageStream : public QObject, public IMessageStream
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the #MessageStream
     * 
     * @param [in] msgStreamStore   The #IMsgStreamStore that holds the
     * messages for the #MessageStream
     * @param [in] msgConfig        The #IMessageConfig that is used to
     * customize incoming messages
     * @param [in] msgFilter        The #IMessageFilter that is used to filter
     * incoming messages
     * @param [in] msgStorage       The #TimestampedMsgStorage that contains
     * the messages to be displayed in the #MessageStream
     * @param [in] parent           The QObject that is the parent to this
     * #MessageStream
     */
    explicit MessageStream(
            IMessageConfig *msgConfig,
            IMessageFilter *msgFilter,
            IMsgStreamStore *msgStreamStore,
            TimestampedMsgStorage &msgStorage,
            QObject *parent = Q_NULLPTR
            );

    virtual ~MessageStream();

    /**
     * @brief Appends the specified message to the stream
     */
    virtual bool appendMsg(const ITimestampedMsg &msgToAppend);

    /**
     * @brief Prepends the specified messages to the stream
     */
    virtual bool prependMsg(const ITimestampedMsg &msgToPrepend);

    /**
     * @brief Clears the stream
     */
    virtual void clear();

signals:

    /**
     * @brief Signal that is emitted when a new message was added to the
     * message stream
     */
    void sgnl_messageAdded(const ITimestampedMsg &addedMsg);

    /**
     * @brief Singal that is emitted when the stream was cleared
     */
    void sgnl_streamCleared();

public slots:

    /**
     * @brief Slots that appends the specified message to the stream
     */
    void slt_appendMessage(const ITimestampedMsg &msgToAppend);

    /**
     * @brief Slots that prepends the specified messages to the stream
     */
    void slt_prependMessage(const ITimestampedMsg &msgToPrepend);

    /**
     * @brief Slot that clears the message stream
     */
    void slt_clearStream();

private:
    void connectMsgConfig();
    void connectMsgFilter();
    void connectMsgStorage();
    void connectMsgStreamStore();

private:
    IMessageConfig *msgConfig;
    IMessageFilter *msgFilter;
    IMsgStreamStore *msgStreamStore;
    /**
     * @brief Reference to the #TimestampedMsgStorage that receives all
     * incoming messages to be displayed in the #MessageStream
     */
    TimestampedMsgStorage &msgStorage;
};

#endif // MESSAGESTREAM_H
