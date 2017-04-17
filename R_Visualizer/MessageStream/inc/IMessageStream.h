/**
 * @file IMessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-08
 * 
 * @brief The interface for the Message Stream Module
 */
#ifndef IMESSAGESTREAM_H
#define IMESSAGESTREAM_H

class ITimestampedMsg;
class MessageStreamNotifier;

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

    virtual MessageStreamNotifier *getNotifier() = 0;
};

#endif /* IMESSAGESTREAM_H */
