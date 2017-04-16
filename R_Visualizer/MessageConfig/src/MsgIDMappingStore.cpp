#include "MsgIDMappingStore.h"

MsgIDMappingStore::MsgIDMappingStore()
{
}

MsgIDMappingStore::~MsgIDMappingStore()
{
}

MsgIDType MsgIDMappingStore::getMsgIDToAlias(const QString &alias) const
{
    for(auto &msgIDRep : msgIDRepStore )
    {
        if(!alias.compare(msgIDRep.getPlainTextAlias(), Qt::CaseInsensitive))
        {
            return msgIDRepStore.key(msgIDRep);
        }
    }
    return MsgIDType();
}

QString MsgIDMappingStore::getAliasToMsgID(const MsgIDType &msgID) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgIDRepStore[msgID].getPlainTextAlias();
}

QColor MsgIDMappingStore::getColorToMsgID(const MsgIDType &msgID) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgIDRepStore[msgID].getColorRepresentation();
}

QColor MsgIDMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgIDType &tempMsgID = getMsgIDToAlias(alias);

    return getColorToMsgID(tempMsgID);
}

/* IMsgIDRep &MsgIDMappingStore::getMsgIDRepToMsgID( */
/*         const MsgIDType &msgID */
/*         ) const */
/* { */
/*     if(contains(msgID)) */
/*     { */
/*         return msgIDRepStore.value(msgID); */
/*     } */
/* } */

IMsgIDRep &MsgIDMappingStore::getMsgIDRepToMsgID(const MsgIDType &msgID)
{
    /**
     * returns default constructed value anyway
     */
    return msgIDRepStore[msgID];
}

bool MsgIDMappingStore::contains(const MsgIDType &msgID) const
{
    return msgIDRepStore.contains(msgID);
}

bool MsgIDMappingStore::contains(const IMsgIDRep &msgIDRep) const
{
    return contains(msgIDRep.getID());
}

IMsgIDRep &MsgIDMappingStore::addMsgIDMapping(
        const MsgIDType &msgID,
        const IMsgIDRep &msgIDRepToAdd
        )
{
    msgIDRepStore.insert(
            msgID,
            dynamic_cast<const MsgIDRep &>(msgIDRepToAdd)
            );

    return msgIDRepStore[msgID];
}

void MsgIDMappingStore::removeMsgIDMapping(const MsgIDType &relatedMsgID)
{
    msgIDRepStore.remove(relatedMsgID);
}

void MsgIDMappingStore::clear()
{
    msgIDRepStore.clear();
}

void MsgIDMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
