#include "MsgDataMappingManager.h"

#include "IPrettyMsg.h"
#include "IMsgDataFormatter.h"
#include "IMsgDataMapping.h"

#include <QSharedPointer>
#include <QString>
#include <QDebug>

MsgDataMappingManager::MsgDataMappingManager(
        IMsgDataMappingStore *msgDataMappingStore,
        QObject *parent
        ) :
    IMsgDataMappingManager(parent),
    msgDataMappingStore(msgDataMappingStore)
{
    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MappingHasChanged,
            [=](){
                emit sgnl_MsgDataMappingManagerChanged(*this);
                emit sgnl_MappingManagerChanged(*this);
                }
            );
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

QString MsgDataMappingManager::parseMsgDataToString(const IMsg &msg) const
{
    const MsgIDType &msgID = msg.getMsgID();
    const MsgCodeType &msgCode = msg.getMsgCode();
    const MsgDataType &msgData = msg.getMsgData();

    QSharedPointer<IMsgDataFormatter> msgDataFormatter =
            getMsgDataFormatter(msgID,msgCode);

    if(msgDataFormatter != Q_NULLPTR)
    {
        return msgDataFormatter->parseMsgDataToString(msg);
    }
    else
    {
        QString msgDataAsString;

        for(const MsgDataByteType msgDataByte : msgData)
        {
            msgDataAsString.append(static_cast<QString>(msgDataByte) + " ");
        }

        return msgDataAsString.trimmed();
    }
}

QColor MsgDataMappingManager::parseMsgDataToColor(const IMsg &msg) const
{
    const MsgIDType &msgID = msg.getMsgID();
    const MsgCodeType &msgCode = msg.getMsgCode();
    const MsgDataType &msgData = msg.getMsgData();

    QSharedPointer<IMsgDataFormatter> msgDataFormatter =
            getMsgDataFormatter(msgID,msgCode);

    if(msgDataFormatter != Q_NULLPTR)
    {
        return msgDataFormatter->parseMsgDataToColor(msg);
    }
    else
    {
        return QColor(Qt::white);
    }
}

QSharedPointer<IMsgDataFormatter> MsgDataMappingManager::getMsgDataFormatter(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    if(msgDataMappingStore->contains(msgID,msgCode))
    {
        return msgDataMappingStore->getMsgDataFormatter(msgID,msgCode);
    }

    return QSharedPointer<IMsgDataFormatter>(Q_NULLPTR);
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
