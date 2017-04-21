#include "MsgDataMappingNotifier.h"

MsgDataMappingNotifier::MsgDataMappingNotifier(
        IMsgDataMapping *msgDataMapping,
        QObject *parent
        ) :
    QObject(parent),
    msgDataMapping(msgDataMapping)
{
}

MsgDataMappingNotifier::~MsgDataMappingNotifier()
{
}
