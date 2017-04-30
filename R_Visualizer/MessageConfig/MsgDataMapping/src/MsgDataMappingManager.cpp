#include "MsgDataMappingManager.h"

#include "IPrettyMsg.h"
#include "IMsgDataFormatter.h"
#include "IMsgDataMapping.h"

#include <QString>
#include <QDebug>

MsgDataMappingManager::MsgDataMappingManager(
        IMsgDataMappingStore *msgDataMappingStore,
        QObject *parent
        ) :
    IMsgDataMappingManager(parent),
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

IMsgDataFormatter *MsgDataMappingManager::getMsgDataFormatter(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    if(msgDataMappingStore->contains(msgID,msgCode))
    {
        return msgDataMappingStore->getMsgDataFormatter(msgID,msgCode);
    }

    return Q_NULLPTR;
}

QString MsgDataMappingManager::getMsgDataFormatString(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    if(msgDataMappingStore->contains(msgID,msgCode))
    {
        return msgDataMappingStore->
            getMsgDataFormatter(msgID,msgCode)->
            getFormatString();
    }

    return QString();
}

void MsgDataMappingManager::addMsgDataMapping(
        const IMsgDataMapping &msgDataMapping
        )
{
    const MsgIDType &msgID = msgDataMapping.getMsgID();
    const MsgCodeType &msgCode = msgDataMapping.getMsgCode();

    if(!msgDataMappingStore->contains(msgID,msgCode))
    {
        msgDataMappingStore->addMsgDataMapping(
                msgID,
                msgCode,
                msgDataMapping
                );
    }
}

void MsgDataMappingManager::removeMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    if(msgDataMappingStore->contains(msgID,msgCode))
    {
        msgDataMappingStore->removeMsgDataMapping(
                msgID,
                msgCode
                );
    }
}

IMsgDataMappingStore *MsgDataMappingManager::getStore() const
{
    return msgDataMappingStore;
}


void MsgDataMappingManager::accept(FileParser *visitor)
{
    msgDataMappingStore->accept(visitor);
}


void MsgDataMappingManager::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
}
