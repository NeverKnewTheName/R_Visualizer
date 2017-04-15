#include "SendMsgSingle.h"

SendMsgSingle::SendMsgSingle()
{
}

SendMsgSingle::~SendMsgSingle()
{
}

void SendMsgSingle::setMsg(const IMsg &msg)
{
    this->messageToSend = msg;
}

void SendMsgSingle::setMsgID(const MsgIDType &msgID)
{
    messageToSend.setMsgID(msgID);
}

void SendMsgSingle::setMsgCode(const MsgCodeType &msgCode)
{
    messageToSend.setMsgCode(msgCode);
}

void SendMsgSingle::setMsgData(const MsgDataType &msgData)
{
    messageToSend.setMsgData(msgData);
}

void SendMsgSingle::sendMessage(const IMsg &msgToSend)
{
    emit sgnl_sendMsg(msgToSend);
}

void SendMsgSingle::slt_setMsg(const IMsg &msg)
{
    setMsg(msg);
}

void SendMsgSingle::slt_setMsgID(const MsgIDType &msgID)
{
    setMsgID(msgID);
}

void SendMsgSingle::slt_setMsgCode(const MsgCodeType &msgCode)
{
    setMsgCode(msgCode);
}

void SendMsgSingle::slt_setMsgData(const MsgDataType &msgData)
{
    setMsgData(msgData);
}
