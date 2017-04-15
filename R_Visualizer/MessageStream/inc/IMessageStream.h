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

    virtual ~IMessageStream(){}

    /**
     * @brief Appends the specified message to the stream
     */
    virtual bool appendMsg(const ITimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Prepends the specified messages to the stream
     */
    virtual bool prependMsg(const ITimestampedMsg &msgToPrepend) = 0;

    /**
     * @brief Clears the stream
     */
    virtual void clear() = 0;

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
     * @brief Slot that clears the message stream
     */
    virtual void slt_clearStream() = 0;
};

#endif /* IMESSAGESTREAM_H */
