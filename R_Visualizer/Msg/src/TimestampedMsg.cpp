#include "TimestampedMsg.h"

#include "fileparser.h"

TimestampedMsg::TimestampedMsg() :
    originalMsg(),
    msgTimestamp()
{
}

TimestampedMsg::TimestampedMsg(
        const IMsg &originalMsg,
        const QDateTime &timestamp
        ) :
    originalMsg(
            Msg(
                originalMsg.getMsgID(),
                originalMsg.getMsgCode(),
                originalMsg.getMsgData()
                )
            ),
    msgTimestamp(timestamp)
{
}

TimestampedMsg::TimestampedMsg(
        const Msg &originalMsg,
        const QDateTime &timestamp
        ) :
    originalMsg(originalMsg),
    msgTimestamp(timestamp)
{
}

TimestampedMsg::TimestampedMsg(const TimestampedMsg &other) :
    originalMsg(other.originalMsg),
    msgTimestamp(other.msgTimestamp)
{
}

TimestampedMsg::~TimestampedMsg()
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


IMsg *TimestampedMsg::cloneMsg() const
{
    return new TimestampedMsg(*this);
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

void TimestampedMsg::setOriginalMsg(const Msg &originalMsg)
{
    this->originalMsg = originalMsg;
}


TimestampedMsg::operator QString() const
{
    return QString("Timestamp: %1 - %2")
        .arg(msgTimestamp.toString("dd.MM.yyyy - hh:mm:ss.zzz"))
        .arg(static_cast<QString>(originalMsg));
}

void TimestampedMsg::accept(FileParser *visitor)
{
    visitor->visit(this);
}
