#include "SendMsgSingle.h"

SendMsgSingle::SendMsgSingle(QObject *parent) :
    ISendMsgSingle(parent)
{
}

SendMsgSingle::~SendMsgSingle()
{
}

IMsgPtr SendMsgSingle::getMsg() const
{
    return IMsgPtr(messageToSend.cloneMsg());
}

void SendMsgSingle::setMsg(const IMsg &msg)
{
    messageToSend = Msg(msg.getMsgID(),msg.getMsgCode(),msg.getMsgData());
    emit sgnl_msgHasChanged(messageToSend);
}

void SendMsgSingle::setMsgID(const MsgIDType &msgID)
{
    messageToSend.setMsgID(msgID);
    emit sgnl_msgHasChanged(messageToSend);
}

void SendMsgSingle::setMsgCode(const MsgCodeType &msgCode)
{
    messageToSend.setMsgCode(msgCode);
    emit sgnl_msgHasChanged(messageToSend);
}

void SendMsgSingle::setMsgData(const MsgDataType &msgData)
{
    messageToSend.setMsgData(msgData);
    emit sgnl_msgHasChanged(messageToSend);
}

void SendMsgSingle::sendMessage()
{
    emit sgnl_sendMessage(messageToSend);
}

void SendMsgSingle::sendMessage(const IMsg &msgToSend)
{
    emit sgnl_sendMessage(msgToSend);
}
