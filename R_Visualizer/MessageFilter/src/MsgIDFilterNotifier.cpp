#include "MsgIDFilterNotifier.h"

#include "IMsgIDFilter.h"

MsgIDFilterNotifier::MsgIDFilterNotifier(
        IMsgIDFilter *msgIDFilter,
        QObject *parent
        ) :
    QObject(parent),
    msgIDfilter(msgIDFilter)
{
}

MsgIDFilterNotifier::~MsgIDFilterNotifier()
{
}
