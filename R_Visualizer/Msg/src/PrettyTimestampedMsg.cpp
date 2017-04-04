#include "PrettyTimestampedMsg.h"

#include "TimestampedMsg.h"

PrettyTimestampedMsg::PrettyTimestampedMsg() :
    msgDataFormatterUniqPtr(Q_NULLPTR),
    originalMsg(new TimestampedMsg()),
    msgIDPlainTextAlias("Default"),
    msgCodePlainTextAlias("Default"),
    msgIDColorRepresentation(Qt::white),
    msgCodeColorRepresentation(Qt::white)
{
}

PrettyTimestampedMsg::PrettyTimestampedMsg(const ITimestampedMsg &originalMsg) :
    msgDataFormatterUniqPtr(Q_NULLPTR),
    originalMsg(originalMsg.cloneMsg()),
    msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
    msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
    msgIDColorRepresentation(Qt::white),
    msgCodeColorRepresentation(Qt::white)
{
}

PrettyTimestampedMsg::PrettyTimestampedMsg(const PrettyTimestampedMsg &other) :
    PrettyTimestampedMsgCloneable<PrettyTimestampedMsg,ITimestampedMsg>(other),
    originalMsg(other.originalMsg->cloneMsg()),
    msgDataFormatterUniqPtr(other.msgDataFormatterUniqPtr->cloneFormatter()),
    msgIDPlainTextAlias(other.msgIDPlainTextAlias),
    msgCodePlainTextAlias(other.msgCodePlainTextAlias),
    msgIDColorRepresentation(other.msgIDColorRepresentation),
    msgCodeColorRepresentation(other.msgCodeColorRepresentation)
{
}


PrettyTimestampedMsg::~PrettyTimestampedMsg()
{
}

PrettyTimestampedMsg &PrettyTimestampedMsg::operator =(
        const PrettyTimestampedMsg &other
        )
{
    this->msgDataFormatterUniqPtr =
        other.msgDataFormatterUniqPtr->cloneFormatter();
    this->originalMsg = other.originalMsg->cloneMsg();
    this->msgIDPlainTextAlias = other.msgIDPlainTextAlias;
    this->msgCodePlainTextAlias = other.msgCodePlainTextAlias;
    this->msgIDColorRepresentation = other.msgIDColorRepresentation;
    this->msgCodeColorRepresentation = other.msgCodeColorRepresentation;
}

QString PrettyTimestampedMsg::getMsgIDPlainTextAlias() const
{
    return msgIDPlainTextAlias;
}

void PrettyTimestampedMsg::setMsgIDPlainTextAlias(const QString &msgIDAlias)
{
    this->msgIDPlainTextAlias = msgIDAlias;
}

QColor PrettyTimestampedMsg::getMsgIDColorRepresentation() const
{
    return msgIDColorRepresentation;
}

void PrettyTimestampedMsg::setMsgIDColorRepresentation(
        const QColor &msgIDColorRepresentation
        )
{
    this->msgIDColorRepresentation = msgIDColorRepresentation;
}


QString PrettyTimestampedMsg::getMsgCodePlainTextAlias() const
{
    return msgCodePlainTextAlias;
}

void PrettyTimestampedMsg::setMsgCodePlainTextAlias(const QString &msgCodePlainTextAlias)
{
    this->msgCodePlainTextAlias = msgCodePlainTextAlias;
}

QColor PrettyTimestampedMsg::getMsgCodeColorRepresentation() const
{
    return msgCodeColorRepresentation;
}

void PrettyTimestampedMsg::setMsgCodeColorRepresentation(
        const QColor &msgCodeColorRepresentation
        )
{
    this->msgCodeColorRepresentation = msgCodeColorRepresentation;
}


QString PrettyTimestampedMsg::getParsedMsgDataString() const
{
    return msgDataFormatterUniqPtr->parseMsgDataToString(*this);
}

QColor PrettyTimestampedMsg::getParsedMsgDataColor() const
{
    return msgDataFormatterUniqPtr->parseMsgDataToColor(*this);
}

void PrettyTimestampedMsg::setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter)
{
    this->msgDataFormatterUniqPtr = msgDataFormatter.cloneFormatter();
}

IMsgUniqPtr PrettyTimestampedMsg::cloneMsg() const
{
    return originalMsg->cloneMsg();
}

void PrettyTimestampedMsg::setMsgID(const MsgIDType &msgID)
{
    originalMsg->setMsgID(msgID);
}

const MsgIDType PrettyTimestampedMsg::getMsgID() const
{
    return originalMsg->getMsgID();
}

void PrettyTimestampedMsg::setMsgCode(const MsgCodeType &msgCode)
{
    originalMsg->setMsgCode(msgCode);
}

const MsgCodeType PrettyTimestampedMsg::getMsgCode() const
{
    return originalMsg->getMsgCode();
}

void PrettyTimestampedMsg::setMsgData(const MsgDataType &msgData)
{
    originalMsg->setMsgData(msgData);
}

const MsgDataType PrettyTimestampedMsg::getMsgData() const
{
    return originalMsg->getMsgData();
}

void PrettyTimestampedMsg::setTimestamp(const QDateTime &newTimestamp)
{
    originalMsg->setTimestamp(newTimestamp);
}

const QDateTime PrettyTimestampedMsg::getTimestamp() const
{
    return originalMsg->getTimestamp();
}

void PrettyTimestampedMsg::accept(FileParser *visitor)
{
    originalMsg->accept(visitor);
}


