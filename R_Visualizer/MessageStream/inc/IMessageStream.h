/**
 * @file IMessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-08
 * 
 * @brief The interface for the Message Stream Module
 */
#ifndef IMESSAGESTREAM_H
#define IMESSAGESTREAM_H

#include <QObject>

class ITimestampedMsg;

/**
 * @brief The #IMessageStream interface
 */
class IMessageStream : public QObject
{
    Q_OBJECT
public:

    explicit IMessageStream(QObject *parent = Q_NULLPTR) : QObject(parent)
    {

    }
    virtual ~IMessageStream()
    {

    }

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

public slots:
    /**
     * @brief Slot that shall be called to receive messages to add to the
     * #IMessageStream
     * 
     * @param[in] receivedMsg Received #ITimestampedMsg to add to the stream
     *
     * @note This default implementation calls #appendMsg
     */
    virtual void slt_receiveMessage(const ITimestampedMsg &receivedMsg)
    {
        appendMsg(receivedMsg);
    }

};

#endif /* IMESSAGESTREAM_H */
