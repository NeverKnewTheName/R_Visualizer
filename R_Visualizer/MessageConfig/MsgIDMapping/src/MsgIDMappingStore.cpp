#include "MsgIDMappingStore.h"

MsgIDMappingStore::MsgIDMappingStore(QObject *parent) :
    IMsgIDMappingStore(parent)
{
    connect(
            this,
            &IMsgIDMappingStore::sgnl_Cleared,
            this,
            &IMsgIDMappingStore::sgnl_MappingHasChanged
            );
    connect(
            this,
            &IMsgIDMappingStore::sgnl_MsgIDMappingAdded,
            this,
            &IMsgIDMappingStore::sgnl_MappingHasChanged
            );
    connect(
            this,
            &IMsgIDMappingStore::sgnl_MsgIDMappingRemoved,
            this,
            &IMsgIDMappingStore::sgnl_MappingHasChanged
            );
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
    emit sgnl_MsgIDMappingAboutToBeAdded(msgID);

    msgIDMappingStore.insert(
            msgID,
            dynamic_cast<const MsgIDMapping &>(msgIDMappingToAdd)
            );

    emit sgnl_MsgIDMappingAdded(msgID);

    return msgIDMappingStore[msgID];
}

void MsgIDMappingStore::removeMsgIDMapping(const MsgIDType &relatedMsgID)
{
    emit sgnl_MsgIDMappingAboutToBeRemoved(relatedMsgID);
    msgIDMappingStore.remove(relatedMsgID);
    emit sgnl_MsgIDMappingRemoved(relatedMsgID);
}

void MsgIDMappingStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgIDMappingStore.clear();
    emit sgnl_Cleared();
}

void MsgIDMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}


QVector<MsgIDType> MsgIDMappingStore::getContainedMsgIDs() const
{
    return msgIDMappingStore.keys().toVector();
}
