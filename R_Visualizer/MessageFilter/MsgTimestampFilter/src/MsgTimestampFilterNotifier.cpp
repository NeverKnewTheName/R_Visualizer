#include "MsgTimestampFilterNotifier.h"

MsgTimestampFilterNotifier::MsgTimestampFilterNotifier(
        IMsgTimestampFilter *msgTimestampFilter,
        QObject *parent
        ) :
    QObject(parent),
    msgTimestampFilter(msgTimestampFilter)
{
}

MsgTimestampFilterNotifier::~MsgTimestampFilterNotifier()
{
}
