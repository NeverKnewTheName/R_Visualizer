#include "MsgCodeMappingNotifier.h"

MsgCodeMappingNotifier::MsgCodeMappingNotifier(
        IMsgCodeMappingManager *msgCodeMappingManager,
        QObject *parent
        ) :
    QObject(parent),
    msgCodeMappingManager(msgCodeMappingManager)
{
}

MsgCodeMappingNotifier::~MsgCodeMappingNotifier()
{
}
