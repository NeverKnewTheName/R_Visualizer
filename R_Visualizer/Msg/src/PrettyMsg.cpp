#include "PrettyMsg.h"

#include "Msg.h"

PrettyMsg::PrettyMsg() : 
    msgDataFormatterUniqPtr(Q_NULLPTR),
    originalMsg(Q_NULLPTR),
    msgIDPlainTextAlias("Default"),
    msgCodePlainTextAlias("Default"),
    msgIDColorRepresentation(Qt::white),
    msgCodeColorRepresentation(Qt::white)
{
}

PrettyMsg::PrettyMsg(const IMsg &originalMsg) :
    msgDataFormatterUniqPtr(Q_NULLPTR),
    originalMsg(originalMsg.cloneMsg()),
    msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
    msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
    msgIDColorRepresentation(Qt::white),
    msgCodeColorRepresentation(Qt::white)
{
}

PrettyMsg::PrettyMsg(const PrettyMsg &other) :
    originalMsg(other.originalMsg->cloneMsg()),
    msgDataFormatterUniqPtr(other.msgDataFormatterUniqPtr->cloneFormatter()),
    msgIDPlainTextAlias(other.msgIDPlainTextAlias),
    msgCodePlainTextAlias(other.msgCodePlainTextAlias),
    msgIDColorRepresentation(other.msgIDColorRepresentation),
    msgCodeColorRepresentation(other.msgCodeColorRepresentation)
{
}


PrettyMsg::~PrettyMsg()
{
}

PrettyMsg &PrettyMsg::operator =(
        const PrettyMsg &other
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

void PrettyMsg::setMsgIDColorRepresentation(
        const QColor &msgIDColorRepresentation
        )
{
    this->msgIDColorRepresentation = msgIDColorRepresentation;
}


QString PrettyMsg::getMsgCodePlainTextAlias() const
{
    return msgCodePlainTextAlias;
}

void PrettyMsg::setMsgCodePlainTextAlias(const QString &msgCodePlainTextAlias)
{
    this->msgCodePlainTextAlias = msgCodePlainTextAlias;
}

QColor PrettyMsg::getMsgCodeColorRepresentation() const
{
    return msgCodeColorRepresentation;
}

void PrettyMsg::setMsgCodeColorRepresentation(
        const QColor &msgCodeColorRepresentation
        )
{
    this->msgCodeColorRepresentation = msgCodeColorRepresentation;
}


QString PrettyMsg::getParsedMsgDataString() const
{
    //Check if the MsgDataFormatter is a nullptr
    if(msgDataFormatterUniqPtr.get() == nullptr)
    {
        QString msgDataAsDefaultString;
        MsgDataType msgData = getMsgData();
        for(const MsgDataByteType &dataByte : msgData)
        {
            QString msgDataByteAsString("0x%1 ");
            msgDataByteAsString.arg(static_cast<const QString &>(dataByte));
            msgDataAsDefaultString.prepend(msgDataByteAsString);
        }
        return msgDataAsDefaultString;
    }

    return msgDataFormatterUniqPtr->parseMsgDataToString(*this);
}

QColor PrettyMsg::getParsedMsgDataColor() const
{
    //Check if the MsgDataFormatter is a nullptr
    if(msgDataFormatterUniqPtr.get() == nullptr)
    {
        return QColor(Qt::white);
    }

    return msgDataFormatterUniqPtr->parseMsgDataToColor(*this);
}

void PrettyMsg::setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter)
{
    this->msgDataFormatterUniqPtr = msgDataFormatter.cloneFormatter();
}

IMsgUniqPtr PrettyMsg::cloneMsg() const
{
    return originalMsg->cloneMsg();
}

void PrettyMsg::setMsgID(const MsgIDType &msgID)
{
    originalMsg->setMsgID(msgID);
}

const MsgIDType PrettyMsg::getMsgID() const
{
    return originalMsg->getMsgID();
}

void PrettyMsg::setMsgCode(const MsgCodeType &msgCode)
{
    originalMsg->setMsgCode(msgCode);
}

const MsgCodeType PrettyMsg::getMsgCode() const
{
    return originalMsg->getMsgCode();
}

void PrettyMsg::setMsgData(const MsgDataType &msgData)
{
    originalMsg->setMsgData(msgData);
}

const MsgDataType PrettyMsg::getMsgData() const
{
    return originalMsg->getMsgData();
}

void PrettyMsg::accept(FileParser *visitor)
{
    originalMsg->accept(visitor);
}

