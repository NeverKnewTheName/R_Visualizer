#include "MsgCodeFilterNotifier.h"

#include "IMsgCodeFilter.h"

MsgCodeFilterNotifier::MsgCodeFilterNotifier(
        IMsgCodeFilter *msgCodeFilter,
        QObject *parent
        ) :
    QObject(parent),
    msgCodeFilter(msgCodeFilter)
{
}

MsgCodeFilterNotifier::~MsgCodeFilterNotifier()
{
}
