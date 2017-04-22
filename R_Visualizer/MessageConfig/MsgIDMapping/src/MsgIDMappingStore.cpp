#include "MsgIDMappingStore.h"

MsgIDMappingStore::MsgIDMappingStore()
{
}

MsgIDMappingStore::~MsgIDMappingStore()
{
}

MsgIDType MsgIDMappingStore::getMsgIDToAlias(const QString &alias) const
{
    for(auto &msgIDMapping : msgIDMappingStore )
    {
        if(!alias.compare(msgIDMapping.getPlainTextAlias(), Qt::CaseInsensitive))
        {
            return msgIDMappingStore.key(msgIDMapping);
        }
    }
    return MsgIDType();
}

QString MsgIDMappingStore::getAliasToMsgID(const MsgIDType &msgID) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgIDMappingStore[msgID].getPlainTextAlias();
}

QColor MsgIDMappingStore::getColorToMsgID(const MsgIDType &msgID) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgIDMappingStore[msgID].getColorRepresentation();
}

QColor MsgIDMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgIDType &tempMsgID = getMsgIDToAlias(alias);

    return getColorToMsgID(tempMsgID);
}

/* IMsgIDMapping &MsgIDMappingStore::getMsgIDMappingToMsgID( */
/*         const MsgIDType &msgID */
/*         ) const */
/* { */
/*     if(contains(msgID)) */
/*     { */
/*         return msgIDMappingStore.value(msgID); */
/*     } */
/* } */

IMsgIDMapping &MsgIDMappingStore::getMsgIDMappingToMsgID(const MsgIDType &msgID)
{
    /**
     * returns default constructed value anyway
     */
    return msgIDMappingStore[msgID];
}

bool MsgIDMappingStore::contains(const MsgIDType &msgID) const
{
    return msgIDMappingStore.contains(msgID);
}

bool MsgIDMappingStore::contains(const IMsgIDMapping &msgIDMapping) const
{
    return contains(msgIDMapping.getID());
}

IMsgIDMapping &MsgIDMappingStore::addMsgIDMapping(
        const MsgIDType &msgID,
        const IMsgIDMapping &msgIDMappingToAdd
        )
{
    msgIDMappingStore.insert(
            msgID,
            dynamic_cast<const MsgIDMapping &>(msgIDMappingToAdd)
            );

    return msgIDMappingStore[msgID];
}

void MsgIDMappingStore::removeMsgIDMapping(const MsgIDType &relatedMsgID)
{
    msgIDMappingStore.remove(relatedMsgID);
}

void MsgIDMappingStore::clear()
{
    msgIDMappingStore.clear();
}

void MsgIDMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
