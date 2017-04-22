#include "MsgDataMappingNotifier.h"

MsgDataMappingNotifier::MsgDataMappingNotifier(
        IMsgDataMappingManager *msgDataMappingManager,
        QObject *parent
        ) :
    QObject(parent),
    msgDataMappingManager(msgDataMappingManager)
{
}

MsgDataMappingNotifier::~MsgDataMappingNotifier()
{
}
