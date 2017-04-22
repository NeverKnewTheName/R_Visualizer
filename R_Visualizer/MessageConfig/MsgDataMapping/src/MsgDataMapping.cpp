#include "MsgDataMapping.h"

MsgDataMapping::MsgDataMapping() :
    msgID(),
    msgCode(),
    msgDataFormatter(Q_NULLPTR)
{
}

MsgDataMapping::MsgDataMapping(const MsgDataMapping &other) :
    msgID(other.msgID),
    msgCode(other.msgCode),
    msgDataFormatter(other.msgDataFormatter)
{
}

MsgDataMapping::MsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        IMsgDataFormatter *msgDataFormatter
        ) :
    msgID(msgID),
    msgCode(msgCode),
    msgDataFormatter(msgDataFormatter)
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

IMsgDataFormatter *MsgDataMapping::getMsgDataFormatter() const
{
    return msgDataFormatter;
}

void MsgDataMapping::setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter)
{
    this->msgDataFormatter = msgDataFormatter;
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

IMsgDataMapping &MsgDataMapping::operator =(const IMsgDataMapping &other)
{
    this->msgID = other.getMsgID();
    this->msgCode = other.getMsgCode();
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
