#include "MsgCodeMappingManager.h"

#include "IMsgCodeMappingStore.h"

#include "IPrettyMsg.h"

MsgCodeMappingManager::MsgCodeMappingManager(
        IMsgCodeMappingStore *msgCodeMappingStore
        ) :
    msgCodeMappingStore(msgCodeMappingStore)
{
}

MsgCodeMappingManager::~MsgCodeMappingManager()
{
}

MsgCodeType MsgCodeMappingManager::getMsgCodeToAlias(
        const QString &alias
        ) const
{
    return msgCodeMappingStore->getMsgCodeToAlias(alias);
}

QString MsgCodeMappingManager::getAliasToMsgCode(
        const MsgCodeType &msgCode
        ) const
{
    return msgCodeMappingStore->getAliasToMsgCode(msgCode);
}

QColor MsgCodeMappingManager::getColorToMsgCode(
        const MsgCodeType &msgCode
        ) const
{
    return msgCodeMappingStore->getColorToMsgCode(msgCode);
}

QColor MsgCodeMappingManager::getColorToAlias(
        const QString &alias
        ) const
{
    return msgCodeMappingStore->getColorToAlias(alias);
}

void MsgCodeMappingManager::prettifyMsg(
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

void MsgCodeMappingManager::accept(FileParser *visitor)
{
    msgCodeMappingStore->accept(visitor);
}


void MsgCodeMappingManager::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    //ToDO
}
