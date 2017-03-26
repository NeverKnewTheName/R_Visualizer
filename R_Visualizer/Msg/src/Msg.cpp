#include "Msg.h"

Msg::Msg() :
        msgID(),
        msgCode(),
        msgData()
{
}

Msg::Msg(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const MsgDataType &msgData)
    ) :
        msgID(msgID),
        msgCode(msgCode),
        msgData(msgData)
{
}

Msg::Msg(const Msg &other) :
        msgID(other.msgID),
        msgCode(other.msgCode),
        msgData(other.msgData)
{
}

virtual ~Msg::Msg()
{
}


void Msg::setMsgID(const MsgIDType &msgID)
{
    this->msgID = msgID;
}

const MsgIDType Msg::getMsgID() const
{
    return msgID;
}


void Msg::setMsgCode(const MsgCodeType &msgCode)
{
    this->msgCode = msgCode;
}

const MsgCodeType Msg::getMsgCode() const
{
    return msgCode;
}


void Msg::setMsgData(const MsgDataType &msgData)
{
    this->msgData = msgData;
}

const MsgDataType Msg::getMsgData() const
{
    return msgData;
}


