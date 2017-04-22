#include "MsgIDMappingNotifier.h"

MsgIDMappingNotifier::MsgIDMappingNotifier(
        IMsgIDMappingManager *msgIDMappingManager,
        QObject *parent
        ) :
    QObject(parent),
    msgIDMappingManager(msgIDMappingManager)
{
}

MsgIDMappingNotifier::~MsgIDMappingNotifier()
{
}
