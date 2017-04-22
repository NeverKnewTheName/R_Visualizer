#include "MsgDataMappingManager.h"

#include "IPrettyMsg.h"

MsgDataMappingManager::MsgDataMappingManager(IMsgDataMappingStore *msgDataMappingStore) :
    msgDataMappingStore(msgDataMappingStore)
{
}

MsgDataMappingManager::~MsgDataMappingManager()
{
}

void MsgDataMappingManager::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    //ToDO
    const MsgIDType &msgID = msgToPrettify.getMsgID();
    const MsgCodeType &msgCode = msgToPrettify.getMsgCode();
    const MsgDataType &msgData = msgToPrettify.getMsgData();

    /* msgDataMappingStore-> */
}

void MsgDataMappingManager::accept(FileParser *visitor)
{
    msgDataMappingStore->accept(visitor);
}


void MsgDataMappingManager::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}
