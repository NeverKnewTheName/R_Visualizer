#include "MsgCodeMappingStore.h"

MsgCodeMappingStore::MsgCodeMappingStore(QObject *parent) :
    IMsgCodeMappingStore(parent)
{
}

MsgCodeMappingStore::~MsgCodeMappingStore()
{
}

MsgCodeType MsgCodeMappingStore::getMsgCodeToAlias(const QString &alias) const
{
    for(auto &msgCodeMapping : msgCodeMappingStore )
    {
        if(!alias.compare(msgCodeMapping.getPlainTextAlias(), Qt::CaseInsensitive))
        {
            return msgCodeMappingStore.key(msgCodeMapping);
        }
    }
    return MsgCodeType();
}

QString MsgCodeMappingStore::getAliasToMsgCode(const MsgCodeType &msgCode) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgCodeMappingStore[msgCode].getPlainTextAlias();
}

QColor MsgCodeMappingStore::getColorToMsgCode(const MsgCodeType &msgCode) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgCodeMappingStore[msgCode].getColorRepresentation();
}

QColor MsgCodeMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgCodeType &tempMsgCode = getMsgCodeToAlias(alias);

    return getColorToMsgCode(tempMsgCode);
}

IMsgCodeMapping &MsgCodeMappingStore::getMsgCodeMappingToMsgCode(
        const MsgCodeType &msgCode
        )
{
    /**
     * returns default constructed value anyway
     */
    return msgCodeMappingStore[msgCode];
}


bool MsgCodeMappingStore::contains(const MsgCodeType &msgCode) const
{
    return msgCodeMappingStore.contains(msgCode);
}

bool MsgCodeMappingStore::contains(const IMsgCodeMapping &msgCodeMapping) const
{
    return contains(msgCodeMapping.getCode());
}


IMsgCodeMapping &MsgCodeMappingStore::addMsgCodeMapping(
        const MsgCodeType &msgCode,
        const IMsgCodeMapping &msgCodeMappingToAdd
        )
{
    emit sgnl_MsgCodeMappingAboutToBeAdded(msgCode);

    msgCodeMappingStore.insert(
            msgCode,
            dynamic_cast<const MsgCodeMapping &>(msgCodeMappingToAdd)
            );

    emit sgnl_MsgCodeMappingAdded(msgCode);

    return msgCodeMappingStore[msgCode];
}

void MsgCodeMappingStore::removeMsgCodeMapping(
        const MsgCodeType &relatedCode
        )
{
    emit sgnl_MsgCodeMappingAboutToBeRemoved(relatedCode);
    msgCodeMappingStore.remove(relatedCode);
    emit sgnl_MsgCodeMappingRemoved(relatedCode);
}


void MsgCodeMappingStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgCodeMappingStore.clear();
    emit sgnl_Cleared();
}


void MsgCodeMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

QVector<MsgCodeType> MsgCodeMappingStore::getContainedMsgCodes() const
{
    return msgCodeMappingStore.keys().toVector();
}
