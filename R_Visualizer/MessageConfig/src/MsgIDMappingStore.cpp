#include "MsgIDMappingStore.h"

MsgIDMappingStore::MsgIDMappingStore(const IMsgIDRep &defaultValue) :
    defaultValue(defaultValue)
{
}

virtual ~MsgIDMappingStore::MsgIDMappingStore()
{
}

MsgIDType MsgIDMappingStore::getMsgIDToAlias(const QString &alias) const
{
    for(auto &msgIDRep : msgIDRepStore )
    {
        if(!alias.compare(msgIDRep.getAlias(), Qt::CaseInsensitive))
        {
            return msgIDRepStore.key(msgIDRep);
        }
    }
    return 0;
}

QString MsgIDMappingStore::getAliasToMsgID(const MsgIDType &msgID) const
{
    //ToTHINK maybe discard contains check.. default constructed value anyway
    if(msgIDRepStore.contains(msgID))
    {
        return msgIDRepStore.value(msgID).getPlainTextAlias();
    }
    return QString();
}

QColor MsgIDMappingStore::getColorToMsgID(const MsgIDType &msgID) const
{
    //ToTHINK maybe discard contains check.. default constructed value anyway
    if(msgIDRepStore.contains(msgID))
    {
        return msgIDRepStore.at(msgID).getColorRepresentation();
    }
    return QColor();
}

QColor MsgIDMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgIDType &tempMsgID = getMsgIDToAlias(alias);
    if(tempMsgID == 0)
    {
        return QColor();
    }

    return getColorToMsgID(tempMsgID);
}

IMsgIDRep &MsgIDMappingStore::getMsgIDRepToMsgID(const MsgIDType msgID) const
{
    if(containsMsgID(msgID))
    {
        return msgIDRepStore.value(msgID);
    }

    //todo Add standard return...
}

IMsgIDRep &MsgIDMappingStore::getMsgIDRepToMsgID(const MsgIDType msgID)
{
    if(containsMsgID(msgID))
    {
        return msgIDRepStore[msgID];
    }

    //todo Add standard return...
}

bool MsgIDMappingStore::contains(const MsgIDType msgID) const
{
    return msgIDRepStore.contains(msgID);
}

bool MsgIDMappingStore::contains(const IMsgIDRep &msgIDRep) const
{
    return msgIDRepStore.contains(msgIDRep.getID());
}

void MsgIDMappingStore::addMsgIDMapping(const IMsgIDRep &msgIDRepToAdd)
{
    msgIDRepStore.insert(msgIDRepToAdd.getID(), msgIDRepToAdd.cloneMsgIDRep());
}

void MsgIDMappingStore::removeMsgIDMapping(const MsgIDType relatedMsgID)
{
    msgIDRepStore.remove(relatedMsgID);
}

void MsgIDMappingStore::clear()
{
    msgIDRepStore.clear();
}

