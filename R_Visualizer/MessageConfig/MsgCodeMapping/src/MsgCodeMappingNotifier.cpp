#include "MsgCodeMappingNotifier.h"

MsgCodeMappingNotifier::MsgCodeMappingNotifier(
        IMsgCodeMapping *msgCodeMapping,
        QObject *parent
        ) :
    QObject(parent),
    msgCodeMapping(msgCodeMapping)
{
}

MsgCodeMappingNotifier::~MsgCodeMappingNotifier()
{
}
