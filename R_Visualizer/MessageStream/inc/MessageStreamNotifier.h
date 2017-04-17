#ifndef MESSAGESTREAMNOTIFIER_H
#define MESSAGESTREAMNOTIFIER_H

#include <QObject>

class IMessageStream;
class ITimestampedMsg;

class MessageStreamNotifier : public QObject
{
    Q_OBJECT
public:
    MessageStreamNotifier(
            IMessageStream *msgStream,
            QObject *parent = Q_NULLPTR
            );

    virtual ~MessageStreamNotifier();

    void emitSgnlMessageAdded(
        const ITimestampedMsg &addedMsg
        );

    void emitSgnlStreamCleared();

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
    IMessageStream *msgStream;

};

#endif /* MESSAGESTREAMNOTIFIER_H */
