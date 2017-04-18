#include "MsgIDMappingNotifier.h"

MsgIDMappingNotifier::MsgIDMappingNotifier(
        IMsgIDMapping *msgIDMapping,
        QObject *parent
        ) :
    QObject(parent),
    msgIDMapping(msgIDMapping)
{
}

MsgIDMappingNotifier::~MsgIDMappingNotifier()
{
}
