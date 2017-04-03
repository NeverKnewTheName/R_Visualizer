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
    return MsgIDMappingStore->getColorToAlias(alias);
}

IPrettyMsgUniqPtr<IMsg> MsgIDMapping::prettifyMsg(
        IPrettyMsgUniqPtr<IMsg> msgToPrettify
        ) const
{
    const MsgIDType &msgID = msgToPrettify->getMsgID();
    msgToPrettify->setMsgIDPlainTextAlias(
            msgIDMappingStore->getAliasToMsgID(msgID)
            );
    msgToPrettify->setMsgIDColorRepresentation(
            msgIDMappingStore->getColorToMsgID(msgID)
            );
    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MsgIDMapping::prettifyMsg(
        IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
        ) const
{
    const MsgIDType &msgID = ITimestampedMsgToPrettify->getMsgID();
    msgToPrettify->setMsgIDPlainTextAlias(
            msgIDMappingStore->getAliasToMsgID(msgID)
            );
    msgToPrettify->setMsgIDColorRepresentation(
            msgIDMappingStore->getColorToMsgID(msgID)
            );
    return std::move(msgToPrettify);
}

/* QCompleter *MsgIDMapping::createIDAliasCompleter(QObject *parent) */
/* { */
/*     return msgIDMappingStore->createIDAliasCompleter(parent); */
/* } */

void MsgIDMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
