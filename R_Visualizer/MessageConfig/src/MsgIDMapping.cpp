#include "MsgIDMapping.h"
#include "IMsgIDMappingStore.h"

MsgIDMapping::MsgIDMapping(IMsgIDMappingStore *msgIDMappingStore) :
    msgIDMappingStore(msgIDMappingStore)
{
}

MsgIDMapping::~MsgIDMapping()
{
}

MsgIDType MsgIDMapping::getMsgIDToAlias(const QString &alias) const
{
    return msgIDMappingStore->getMsgIDToAlias(alias);
}

QString MsgIDMapping::getAliasToMsgID(const MsgIDType &msgID) const
{
    return msgIDMappingStore->getAliasToMsgID(msgID);
}

QColor MsgIDMapping::getColorToMsgID(const MsgIDType &msgID) const
{
    return msgIDMappingStore->getColorToMsgID(msgID);
}

QColor MsgIDMapping::getColorToAlias(const QString &alias) const
{
    return msgIDMappingStore->getColorToAlias(alias);
}

void MsgIDMapping::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    const MsgIDType &msgID = msgToPrettify.getMsgID();

    msgToPrettify.setMsgIDPlainTextAlias(
            msgIDMappingStore->getAliasToMsgID(msgID)
            );
    msgToPrettify.setMsgIDColorRepresentation(
            msgIDMappingStore->getColorToMsgID(msgID)
            );
}

void MsgIDMapping::accept(FileParser *visitor)
{
    msgIDMappingStore->accept(visitor);
}
