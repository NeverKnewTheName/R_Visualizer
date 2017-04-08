/**
 * @file IMessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-08
 * 
 * @brief The interface for the Message Stream Module
 */
#ifndef IMESSAGESTREAM_H
#define IMESSAGESTREAM_H

#include "ITimestampedMsg.h"

/**
 * @brief The #IMessageStream interface
 */
class IMessageStream
{
public:
    virtual ~IMessageStream();

signals:
    /**
     * @brief Signal that is emitted when a new message was added to the
     * message stream
     */
    virtual void sgnl_messageAdded(const ITimestampedMsg &addedMsg) = 0;
    /**
     * @brief Singal that is emitted when the stream was cleared
     */
    virtual void sgnl_streamCleared() = 0;

public slots:
    /**
     * @brief Slots that appends the specified message to the stream
     */
    virtual void slt_appendMessage(const ITimestampedMsg &msgToAppend) = 0;
    /**
     * @brief Slots that prepends the specified messages to the stream
     */
    virtual void slt_prependMessage(const ITimestampedMsg &msgToPrepend) = 0;
    /**
     * @brief Slot that removes the most recently added messages that matches
     * the specified messages
     */
    virtual void slt_removeMessage(const ITimestampedMsg &msgToRemove) = 0;

    /**
     * @brief Slot that clears the message stream
     */
    virtual void slt_clearStream() = 0;

private:
    /**
     * @brief Appends the specified message to the stream
     */
    virtual void appendMsg(const ITimestampedMsg &msgToAppend) = 0;
    /**
     * @brief Prepends the specified messages to the stream
     */
    virtual void prependMsg(const ITimestampedMsg &msgToPrepend) = 0;
    /**
     * @brief Removes the most recently added messages that matches the
     * specified messages
     */
    virtual void removeMsg(const ITimestampedMsg &msgToRemove) = 0;
    /**
     * @brief Removes the messages at index
     */
    virtual void removeMsg(const int index) = 0;

    /**
     * @brief Removes all messages that match the specified message
     */
    virtual void removeMsgs(const ITimestampedMsg &msgToRemove) = 0;

    /**
     * @brief Removes count messages starting at index
     */
    virtual void removeMsgs(const int index, const int count) = 0;
};

#endif /* IMESSAGESTREAM_H */
