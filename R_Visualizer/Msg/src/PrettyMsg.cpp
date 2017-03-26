#include "PrettyMsg.h"


PrettyMsg::PrettyMsg()
{
}

PrettyMsg::PrettyMsg(const Msg &originalMsg) :
    PrettyMsgCloneable<PrettyMsg,Msg>(originalMsg),
    msgDataFormatterUniqPtr(Q_NULLPTR),
    msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
    msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
    msgIDColorRepresentation(Qt::white),
    msgCodeColorRepresentation(Qt::white)
{
}

PrettyMsg::PrettyMsg(const PrettyMsg &other) :
    PrettyMsgCloneable<PrettyMsg,Msg>(originalMsg),
    msgDataFormatterUniqPtr(other.msgDataFormatterUniqPtr->clone()),
    msgIDPlainTextAlias(other.msgIDPlainTextAlias),
    msgCodePlainTextAlias(other.msgCodePlainTextAlias),
    msgIDColorRepresentation(other.msgIDColorRepresentation),
    msgCodeColorRepresentation(other.msgCodeColorRepresentation)
{
}


virtual PrettyMsg::~PrettyMsg()
{
}


QString PrettyMsg::getMsgIDPlainTextAlias() const
{
    return msgIDPlainTextAlias;
}

void PrettyMsg::setMsgIDPlainTextAlias(const QString &msgIDAlias)
{
    this->msgIDPlainTextAlias = msgIDAlias;
}

QColor PrettyMsg::getMsgIDColorRepresentation() const
{
    return msgIDColorRepresentation;
}

void PrettyMsg::setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation)
{
    this->msgIDColorRepresentation = msgIDColorRepresentation;
}


QString PrettyMsg::getMsgCodePlainTextAlias() const
{
    return msgCodePlainTextAlias;
}

void PrettyMsg::setMsgCodePlainTextAlias(const QString &msgCodeAlias)
{
    this->msgCodePlainTextAlias = msgCodePlainTextAlias;
}

QColor PrettyMsg::getMsgCodeColorRepresentation() const
{
    return msgCodeColorRepresentation;
}

void PrettyMsg::setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation)
{
    this->msgCodeColorRepresentation = msgCodeColorRepresentation;
}


QString PrettyMsg::getParsedMsgDataString() const
{
    return msgDataFormatterUniqPtr->parseMsgDataToString(*this);
}

QColor PrettyMsg::getParsedMsgDataColor() const
{
    return msgDataFormatterUniqPtr->parseMsgDataToColor(*this);
}

void PrettyMsg::setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter)
{
    this->msgDataFormatterUniqPtr = msgDataFormatter.clone();
}


