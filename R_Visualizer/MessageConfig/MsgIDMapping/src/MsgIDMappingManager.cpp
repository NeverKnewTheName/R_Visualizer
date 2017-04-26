#include "MsgIDMappingManager.h"

#include "IMsgIDMappingStore.h"

#include "IPrettyMsg.h"

MsgIDMappingManager::MsgIDMappingManager(
        IMsgIDMappingStore *msgIDMappingStore,
        QObject *parent
        ) :
    IMsgIDMappingManager(parent),
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

void MsgIDMappingManager::addMsgIDMapping(
        const IMsgIDMapping &msgIDMapping
        )
{
    const MsgIDType &msgID = msgIDMapping.getID();
    if(!msgIDMappingStore->contains(msgID))
    {
        msgIDMappingStore->addMsgIDMapping(msgID, msgIDMapping);
    }
}

void MsgIDMappingManager::removeMsgIDMapping(
        const MsgIDType &relatedMsgID
        /* const IMsgIDMapping &msgIDMapping */
        )
{
    /* const MsgIDType &msgID = msgIDMapping.getID(); */
    if(msgIDMappingStore->contains(relatedMsgID))
    {
        msgIDMappingStore->removeMsgIDMapping(relatedMsgID);
    }
}


void MsgIDMappingManager::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    const MsgIDType &msgID = msgToPrettify.getMsgID();

    if(msgIDMappingStore->contains(msgID))
    {
        msgToPrettify.setMsgIDPlainTextAlias(
                msgIDMappingStore->getAliasToMsgID(msgID)
                );
        msgToPrettify.setMsgIDColorRepresentation(
                msgIDMappingStore->getColorToMsgID(msgID)
                );
    }
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
