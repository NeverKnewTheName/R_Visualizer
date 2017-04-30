#include "MsgCodeMappingManager.h"

#include "IMsgCodeMappingStore.h"

#include "IPrettyMsg.h"

MsgCodeMappingManager::MsgCodeMappingManager(
        IMsgCodeMappingStore *msgCodeMappingStore,
        QObject *parent
        ) :
    IMsgCodeMappingManager(parent),
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

void MsgCodeMappingManager::addMsgCodeMapping(
        const IMsgCodeMapping &msgCodeMapping
        )
{
    const MsgCodeType &msgCode = msgCodeMapping.getCode();
    if(!msgCodeMappingStore->contains(msgCode))
    {
        msgCodeMappingStore->addMsgCodeMapping(msgCode, msgCodeMapping);
    }
}

void MsgCodeMappingManager::removeMsgCodeMapping(
        const MsgCodeType &relatedMsgCode
        /* const IMsgCodeMapping &msgCodeMapping */
        )
{
    /* const MsgCodeType &msgCode = msgCodeMapping.getCode(); */
    if(msgCodeMappingStore->contains(relatedMsgCode))
    {
        msgCodeMappingStore->removeMsgCodeMapping(relatedMsgCode);
    }
}

void MsgCodeMappingManager::prettifyMsg(
       IPrettyMsg &msgToPrettify
       ) const
{
    const MsgCodeType &msgCode = msgToPrettify.getMsgCode();

    if(msgCodeMappingStore->contains(msgCode))
    {
        msgToPrettify.setMsgCodePlainTextAlias(
                msgCodeMappingStore->getAliasToMsgCode(msgCode)
                );
        msgToPrettify.setMsgCodeColorRepresentation(
                msgCodeMappingStore->getColorToMsgCode(msgCode)
                );
    }
}

IMsgCodeMappingStore *MsgCodeMappingManager::getStore() const
{
    return msgCodeMappingStore;
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
