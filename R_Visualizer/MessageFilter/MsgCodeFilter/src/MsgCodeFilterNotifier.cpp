#include "MsgCodeFilterNotifier.h"

#include "MsgCodeFilter.h"

MsgCodeFilterNotifier::MsgCodeFilterNotifier(
        MsgCodeFilter *msgCodeFilter,
        QObject *parent
        ) :
    QObject(parent),
    msgCodeFilter(msgCodeFilter)
{
}

MsgCodeFilterNotifier::~MsgCodeFilterNotifier()
{
}
