#include "MsgDataRep.h"

MsgDataRep::MsgDataRep()
{
}

MsgDataRep::MsgDataRep(const MsgDataRep &other) :
    msgID(other.msgID),
    msgCode(other.msgCode),
    formatString(other.formatString)
{
}

MsgDataRep::MsgDataRep(
        const MsgIDType msgID,
        const MsgCodeType msgCode,
        const QString &formatString
        ) :
    msgID(msgID),
    msgCode(msgCode),
    formatString(formatString)
{
}

MsgDataRep::~MsgDataRep()
{
}

MsgIDType MsgDataRep::getMsgID() const
{
    return msgID;
}

void MsgDataRep::setMsgID(const MsgIDType msgID)
{
    this->msgID = msgID;
}

MsgCodeType MsgDataRep::getMsgCode() const
{
    return msgCode;
}

void MsgDataRep::setMsgCode(const MsgCodeType msgCode)
{
    this->msgCode = msgCode;
}

QString MsgDataRep::getFormatString() const
{
    return formatString;
}

void MsgDataRep::setFormatString(const QString &formatString)
{
    this->formatString = formatString;
}

QString MsgDataRep::parseMsgData(const MsgData &msgData) const
{
    return QString("ParsedMsgData: %1").arg(formatString);
}
