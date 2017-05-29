#include "SendMsgSingle.h"

SendMsgSingle::SendMsgSingle(QObject *parent) :
    ISendMsgSingle(parent)
{
}

SendMsgSingle::~SendMsgSingle()
{
}

void SendMsgSingle::setMsg(const IMsg &msg)
{
    messageToSend = Msg(msg.getMsgID(),msg.getMsgCode(),msg.getMsgData());
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

void SendMsgSingle::sendMessage()
{
    emit sgnl_sendMessage(messageToSend);
}

void SendMsgSingle::sendMessage(const IMsg &msgToSend)
{
    emit sgnl_sendMessage(msgToSend);
}
