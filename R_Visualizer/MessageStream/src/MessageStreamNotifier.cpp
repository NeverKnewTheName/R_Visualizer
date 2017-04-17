#include "MessageStreamNotifier.h"

#include "IMessageStream.h"

MessageStreamNotifier::MessageStreamNotifier(
        IMessageStream *msgStream,
        QObject *parent
        ) :
    QObject(parent),
    msgStream(msgStream)
{
}

MessageStreamNotifier::~MessageStreamNotifier()
{
}

void MessageStreamNotifier::emitSgnlMessageAdded(
        const ITimestampedMsg &addedMsg
        )
{
    emit sgnl_messageAdded(addedMsg);
}

void MessageStreamNotifier::emitSgnlStreamCleared()
{
    emit sgnl_streamCleared();
}

void MessageStreamNotifier::slt_appendMessage(
        const ITimestampedMsg &msgToAppend
        )
{
    msgStream->appendMsg(msgToAppend);
}

void MessageStreamNotifier::slt_prependMessage(
        const ITimestampedMsg &msgToPrepend
        )
{
    msgStream->appendMsg(msgToPrepend);
}

void MessageStreamNotifier::slt_clearStream()
{
    msgStream->clear();
}
