#include "MsgDataMappingStoreNotifier.h"

MsgDataMappingStoreNotifier::MsgDataMappingStoreNotifier(
        IMsgDataMappingStore *msgDataMappingStore,
        QObject *parent
        ) :
    QObject(parent),
    msgDataMappingStore(msgDataMappingStore)
{
}

MsgDataMappingStoreNotifier::~MsgDataMappingStoreNotifier()
{
}
