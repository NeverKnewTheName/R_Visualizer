#include "MsgCodeMappingStore.h"


MsgCodeMappingStore::MsgCodeMappingStore()
{
}

MsgCodeMappingStore::~MsgCodeMappingStore()
{
}


MsgCodeType MsgCodeMappingStore::getMsgCodeToAlias(const QString &alias) const
{
    for(auto &msgCodeRep : msgCodeRepStore )
    {
        if(!alias.compare(msgCodeRep.getPlainTextAlias(), Qt::CaseInsensitive))
        {
            return msgCodeRepStore.key(msgCodeRep);
        }
    }
    return MsgCodeType();
}

QString MsgCodeMappingStore::getAliasToMsgCode(const MsgCodeType &msgCode) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgCodeRepStore[msgCode].getPlainTextAlias();
}

QColor MsgCodeMappingStore::getColorToMsgCode(const MsgCodeType &msgCode) const
{
    /**
     * returns default constructed value anyway if none found
     */
    return msgCodeRepStore[msgCode].getColorRepresentation();
}

QColor MsgCodeMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgCodeType &tempMsgCode = getMsgCodeToAlias(alias);

    return getColorToMsgCode(tempMsgCode);
}


/* IMsgCodeRep &MsgCodeMappingStore::getMsgCodeRepToMsgCode( */
/*         const MsgCodeType &msgCode */
/*         ) const */
/* { */
/*     if(containsMsgCode(msgCode)) */
/*     { */
/*         return msgCodeRepStore.value(msgCode); */
/*     } */

/*     //todo Add standard return... */
/* } */


IMsgCodeRep &MsgCodeMappingStore::getMsgCodeRepToMsgCode(
        const MsgCodeType &msgCode
        )
{
    /**
     * returns default constructed value anyway
     */
    return msgCodeRepStore[msgCode];
}


bool MsgCodeMappingStore::contains(const MsgCodeType &msgCode) const
{
    return msgCodeRepStore.contains(msgCode);
}

bool MsgCodeMappingStore::contains(const IMsgCodeRep &msgCodeRep) const
{
    return contains(msgCodeRep.getCode());
}


IMsgCodeRep &MsgCodeMappingStore::addMsgCodeMapping(
        const MsgCodeType &msgCode,
        const IMsgCodeRep &msgCodeRepToAdd
        )
{
    msgCodeRepStore.insert(
            msgCode,
            dynamic_cast<const MsgCodeRep &>(msgCodeRepToAdd)
            );

    return msgCodeRepStore[msgCode];
}

void MsgCodeMappingStore::removeMsgCodeMapping(
        const MsgCodeType &relatedMsgCode
        )
{
    msgCodeRepStore.remove(relatedMsgCode);
}


void MsgCodeMappingStore::clear()
{
    msgCodeRepStore.clear();
}


void MsgCodeMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

