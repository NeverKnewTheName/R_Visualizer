#include "MsgIDFilterNotifier.h"

#include "MsgIDFilter.h"

MsgIDFilterNotifier::MsgIDFilterNotifier(
        MsgIDFilter *msgIDFilter,
        QObject *parent
        ) :
    QObject(parent),
    msgIDfilter(msgIDFilter)
{
}

MsgIDFilterNotifier::~MsgIDFilterNotifier()
{
}
