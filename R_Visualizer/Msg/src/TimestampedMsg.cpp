#include "TimestampedMsg.h"
#include "fileparser.h"

TimestampedMsg::TimestampedMsg() :
    originalMsg(),
    msgTimestamp()
{
}

TimestampedMsg::TimestampedMsg(const Msg &originalMsg, QDateTime timestamp = QDateTime()) :
    originalMsg(originalMsg),
    msgTimestamp(timestamp)
{
}

TimestampedMsg::TimestampedMsg(const TimestampedMsg &other) :
    originalMsg(other.originalMsg),
    msgTimestamp(other.msgTimestamp)
{
}


virtual TimestampedMsg::~TimestampedMsg()
{
}


void TimestampedMsg::setTimestamp(const QDateTime &newTimestamp)
{
    this->msgTimestamp = newTimestamp;
}

const QDateTime TimestampedMsg::getTimestamp() const
{
    return msgTimestamp;
}


void TimestampedMsg::setMsgID(const MsgIDType &msgID)
{
    originalMsg.setMsgID(msgID);
}

const MsgIDType TimestampedMsg::getMsgID() const
{
    return originalMsg.getMsgID();
}


void TimestampedMsg::setMsgCode(const MsgCodeType &msgCode)
{
    originalMsg.setMsgCode(msgCode);
}

const MsgCodeType TimestampedMsg::getMsgCode() const
{
    return originalMsg.getMsgCode();
}


void TimestampedMsg::setMsgData(const MsgDataType &msgData)
{
    originalMsg.setMsgData(msgData);
}

const MsgDataType TimestampedMsg::getMsgData() const
{
    return originalMsg.getMsgData();
}

const Msg TimestampedMsg::getOriginalMsg() const
{
    return originalMsg;
}

void TimestampedMsg::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
