#include "MsgDataMapping.h"

#include "MsgDataFormatter.h"

MsgDataMapping::MsgDataMapping() :
    msgID(),
    msgCode(),
    msgDataFormatter(new MsgDataFormatter()),
    msgDataFormatString(),
    msgDataDefaultColor()
{
}

MsgDataMapping::MsgDataMapping(const MsgDataMapping &other) :
    msgID(other.msgID),
    msgCode(other.msgCode),
    msgDataFormatter(other.msgDataFormatter->cloneFormatter()),
    msgDataFormatString(other.msgDataFormatString),
    msgDataDefaultColor(other.msgDataDefaultColor)
{
}

MsgDataMapping::MsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const IMsgDataFormatter &msgDataFormatter
        ) :
    msgID(msgID),
    msgCode(msgCode),
    msgDataFormatter(msgDataFormatter.cloneFormatter()),
    msgDataFormatString(msgDataFormatter.getFormatString()),
    msgDataDefaultColor(msgDataFormatter.getDefaultColor())
{
}

MsgDataMapping::~MsgDataMapping()
{
}

MsgIDType MsgDataMapping::getMsgID() const
{
    return msgID;
}

void MsgDataMapping::setMsgID(const MsgIDType &msgID)
{
    this->msgID = msgID;
}

MsgCodeType MsgDataMapping::getMsgCode() const
{
    return msgCode;
}

void MsgDataMapping::setMsgCode(const MsgCodeType &msgCode)
{
    this->msgCode = msgCode;
}

QSharedPointer<IMsgDataFormatter> MsgDataMapping::getMsgDataFormatter() const
{
    return msgDataFormatter;
}

void MsgDataMapping::setMsgDataFormatter(
        const IMsgDataFormatter &msgDataFormatter
        )
{
    this->msgDataFormatter.reset(msgDataFormatter.cloneFormatter());
    this->msgDataFormatter->setFormatString(msgDataFormatString);
    this->msgDataFormatter->setDefaultColor(msgDataDefaultColor);
}

QString MsgDataMapping::getMsgDataFormatString() const
{
    return msgDataFormatString;
}

void MsgDataMapping::setMsgDataFormatString(
        const QString &msgDataFormatString
        )
{
    msgDataFormatter->setFormatString(msgDataFormatString);
    this->msgDataFormatString = msgDataFormatString;
}

QColor MsgDataMapping::getMsgDataDefaultColor() const
{
    return msgDataDefaultColor;
}

void MsgDataMapping::setMsgDataDefaultColor(
        const QColor &msgDataDefaultColor
        )
{
    msgDataFormatter->setDefaultColor(msgDataDefaultColor);
    this->msgDataDefaultColor = msgDataDefaultColor;
}

QString MsgDataMapping::parseMsgData(const IMsg &msg) const
{
    /**
     * msgDataFormatter could be NULL
     */
    if(msgDataFormatter == Q_NULLPTR)
    {
        return QString("");
    }
    return msgDataFormatter->parseMsgDataToString(msg);
}

MsgDataMapping &MsgDataMapping::operator =(const MsgDataMapping &other)
{
    this->msgID = other.getMsgID();
    this->msgCode = other.getMsgCode();
    this->msgDataFormatString = other.getMsgDataFormatString();
    this->msgDataDefaultColor = other.getMsgDataDefaultColor();
    this->msgDataFormatter = other.getMsgDataFormatter();

    return *this;
}

IMsgDataMapping &MsgDataMapping::operator =(const IMsgDataMapping &other)
{
    this->msgID = other.getMsgID();
    this->msgCode = other.getMsgCode();
    this->msgDataFormatString = other.getMsgDataFormatString();
    this->msgDataDefaultColor = other.getMsgDataDefaultColor();
    this->msgDataFormatter = other.getMsgDataFormatter();

    return *this;
}

bool MsgDataMapping::operator ==(const MsgDataMapping &other) const
{
    return ((this->msgID == other.msgID) && (this->msgCode == other.msgCode));
}

bool MsgDataMapping::operator ==(const IMsgDataMapping &other) const
{
    return (
            (this->msgID == other.getMsgID())
            &&
            (this->msgCode == other.getMsgCode())
            );
}

void MsgDataMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
