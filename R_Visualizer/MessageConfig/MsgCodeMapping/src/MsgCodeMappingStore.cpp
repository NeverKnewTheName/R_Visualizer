#include "MsgCodeMappingStore.h"


MsgCodeMappingStore::MsgCodeMappingStore()
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


/* IMsgCodeMapping &MsgCodeMappingStore::getMsgCodeMappingToMsgCode( */
/*         const MsgCodeType &msgCode */
/*         ) const */
/* { */
/*     if(containsMsgCode(msgCode)) */
/*     { */
/*         return msgCodeMappingStore.value(msgCode); */
/*     } */

/*     //todo Add standard return... */
/* } */


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
    msgCodeMappingStore.insert(
            msgCode,
            dynamic_cast<const MsgCodeMapping &>(msgCodeMappingToAdd)
            );

    return msgCodeMappingStore[msgCode];
}

void MsgCodeMappingStore::removeMsgCodeMapping(
        const MsgCodeType &relatedMsgCode
        )
{
    msgCodeMappingStore.remove(relatedMsgCode);
}


void MsgCodeMappingStore::clear()
{
    msgCodeMappingStore.clear();
}


void MsgCodeMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

