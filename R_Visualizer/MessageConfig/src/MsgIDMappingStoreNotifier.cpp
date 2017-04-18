#include "MsgIDMappingStoreNotifier.h"

#include "IMsgIDMappingStore.h"

MsgIDMappingStoreNotifier::MsgIDMappingStoreNotifier(
        IMsgIDMappingStore *msgIDMappingStore,
        QObject *parent
        ) :
    QObject(parent),
    msgIDMappingStore(msgIDMappingStore)
{
}

MsgIDMappingStoreNotifier::~MsgIDMappingStoreNotifier()
{
}
