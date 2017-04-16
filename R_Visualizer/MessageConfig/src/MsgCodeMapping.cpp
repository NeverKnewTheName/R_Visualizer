#include "MsgCodeMapping.h"

#include "IMsgCodeMappingStore.h"

MsgCodeMapping::MsgCodeMapping(IMsgCodeMappingStore *msgCodeMappingStore) :
    msgCodeMappingStore(msgCodeMappingStore)
{
}

MsgCodeMapping::~MsgCodeMapping()
{
}

MsgCodeType MsgCodeMapping::getMsgCodeToAlias(const QString &alias) const
{
}

QString MsgCodeMapping::getAliasToMsgCode(const MsgCodeType &msgCode) const
{
}

QColor MsgCodeMapping::getColorToMsgCode(const MsgCodeType &msgCode) const
{
}

QColor MsgCodeMapping::getColorToAlias(const QString &alias) const
{
}


void MsgCodeMapping::prettifyMsg(
       IPrettyMsg &msgToPrettify
       ) const
{
    const MsgCodeType &msgCode = msgToPrettify.getMsgCode();

    msgToPrettify.setMsgCodePlainTextAlias(
            msgCodeMappingStore->getAliasToMsgCode(msgCode)
                );
    msgToPrettify.setMsgCodeColorRepresentation(
            msgCodeMappingStore->getColorToMsgCode(msgCode)
            );
}

void MsgCodeMapping::accept(FileParser *visitor)
{
    msgCodeMappingStore->accept(visitor);
}
