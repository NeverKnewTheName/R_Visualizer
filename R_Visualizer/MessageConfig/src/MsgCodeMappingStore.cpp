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
        if(!alias.compare(msgCodeRep.getAlias(), Qt::CaseInsensitive))
        {
            return msgCodeRepStore.key(msgCodeRep);
        }
    }
    return 0;
}

QString MsgCodeMappingStore::getAliasToMsgCode(const MsgCodeType &msgCode) const
{
    //ToTHINK maybe discard contains check.. default constructed value anyway
    if(msgCodeRepStore.contains(msgCode))
    {
        return msgCodeRepStore.value(msgCode).getPlainTextAlias();
    }
    return QString();
}

QColor MsgCodeMappingStore::getColorToMsgCode(const MsgCodeType &msgCode) const
{
    //ToTHINK maybe discard contains check.. default constructed value anyway
    if(msgCodeRepStore.contains(msgCode))
    {
        return msgCodeRepStore.at(msgCode).getColorRepresentation();
    }
    return QColor();
}

QColor MsgCodeMappingStore::getColorToAlias(const QString &alias) const
{
    const MsgCodeType &tempMsgCode = getMsgCodeToAlias(alias);
    if(tempMsgCode == 0)
    {
        return QColor();
    }

    return getColorToMsgCode(tempMsgCode);
}


IMsgCodeRep &MsgCodeMappingStore::getMsgCodeRepToMsgCode(
        const MsgCodeType &msgCode
        ) const
{
    if(containsMsgCode(msgCode))
    {
        return msgCodeRepStore.value(msgCode);
    }

    //todo Add standard return...
}


IMsgCodeRep &MsgCodeMappingStore::getMsgCodeRepToMsgCode(
        const MsgCodeType &msgCode
        )
{
    if(containsMsgCode(msgCode))
    {
        return msgCodeRepStore.value(msgCode);
    }

    //todo Add standard return...
}


bool MsgCodeMappingStore::contains(const MsgCodeType &msgCode) const
{
    return msgCodeRepStore.contains(msgCode);
}

bool MsgCodeMappingStore::contains(const IMsgCodeRep &msgCodeRep) const
{
    return msgCodeRepStore.contains(msgCodeRep);
}


void MsgCodeMappingStore::addMsgCodeMapping(const IMsgCodeRep &msgCodeRepToAdd)
{
    msgCodeRepStore.insert(
            msgCodeRepToAdd.getCode(),
            msgCodeRepToAdd.cloneMsgCodeRep()
            );
}

void MsgCodeMappingStore::removeMsgCodeMapping(const MsgCodeType &relatedMsgCode)
{
    msgCodeRepStore.remove(relatedMsgID);
}


void MsgCodeMappingStore::clear()
{
    msgCodeRepStore.clear();
}


void MsgCodeMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

