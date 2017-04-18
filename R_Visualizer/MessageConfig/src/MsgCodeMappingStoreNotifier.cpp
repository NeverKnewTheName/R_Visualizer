#include "MsgCodeMappingStoreNotifier.h"

MsgCodeMappingStoreNotifier::MsgCodeMappingStoreNotifier(
        IMsgCodeMappingStore *msgCodeMappingStore,
        QObject *parent
        ) :
    QObject(parent),
    msgCodeMappingStore(msgCodeMappingStore)
{
}

MsgCodeMappingStoreNotifier::~MsgCodeMappingStoreNotifier()
{
}
