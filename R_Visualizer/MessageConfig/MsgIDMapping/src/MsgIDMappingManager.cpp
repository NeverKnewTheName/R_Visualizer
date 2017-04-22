#include "MsgIDMappingManager.h"

#include "IMsgIDMappingStore.h"

#include "IPrettyMsg.h"

MsgIDMappingManager::MsgIDMappingManager(
        IMsgIDMappingStore *msgIDMappingStore
        ) :
    msgIDMappingStore(msgIDMappingStore)
{
}

MsgIDMappingManager::~MsgIDMappingManager()
{
}

MsgIDType MsgIDMappingManager::getMsgIDToAlias(
        const QString &alias
        ) const
{
    return msgIDMappingStore->getMsgIDToAlias(alias);
}

QString MsgIDMappingManager::getAliasToMsgID(
        const MsgIDType &msgID
        ) const
{
    return msgIDMappingStore->getAliasToMsgID(msgID);
}

QColor MsgIDMappingManager::getColorToMsgID(
        const MsgIDType &msgID
        ) const
{
    return msgIDMappingStore->getColorToMsgID(msgID);
}

QColor MsgIDMappingManager::getColorToAlias(
        const QString &alias
        ) const
{
    return msgIDMappingStore->getColorToAlias(alias);
}

void MsgIDMappingManager::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    const MsgIDType &msgID = msgToPrettify.getMsgID();

    msgToPrettify.setMsgIDPlainTextAlias(
            msgIDMappingStore->getAliasToMsgID(msgID)
            );
    msgToPrettify.setMsgIDColorRepresentation(
            msgIDMappingStore->getColorToMsgID(msgID)
            );
}

void MsgIDMappingManager::accept(FileParser *visitor)
{
    msgIDMappingStore->accept(visitor);
}


void MsgIDMappingManager::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    //ToDo
}
