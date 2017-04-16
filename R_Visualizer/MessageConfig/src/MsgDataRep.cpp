#include "MsgDataRep.h"

MsgDataRep::MsgDataRep() :
    msgID(),
    msgCode(),
    msgDataFormatter(Q_NULLPTR)
{
}

MsgDataRep::MsgDataRep(const MsgDataRep &other) :
    msgID(other.msgID),
    msgCode(other.msgCode),
    msgDataFormatter(other.msgDataFormatter)
{
}

MsgDataRep::MsgDataRep(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        IMsgDataFormatter *msgDataFormatter
        ) :
    msgID(msgID),
    msgCode(msgCode),
    msgDataFormatter(msgDataFormatter)
{
}

MsgDataRep::~MsgDataRep()
{
}

MsgIDType MsgDataRep::getMsgID() const
{
    return msgID;
}

void MsgDataRep::setMsgID(const MsgIDType &msgID)
{
    this->msgID = msgID;
}

MsgCodeType MsgDataRep::getMsgCode() const
{
    return msgCode;
}

void MsgDataRep::setMsgCode(const MsgCodeType &msgCode)
{
    this->msgCode = msgCode;
}

void MsgDataRep::setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter)
{
    this->msgDataFormatter = msgDataFormatter;
}

QString MsgDataRep::parseMsgData(const IMsg &msg) const
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

IMsgDataRep &MsgDataRep::operator =(const IMsgDataRep &other)
{
    this->msgID = other.getMsgID();
    this->msgCode = other.getMsgCode();
    this->msgDataFormatter = other.getMsgDataFormatter();

    return *this;
}

bool MsgDataRep::operator ==(const MsgDataRep &other) const
{
    return ((this->msgID == other.msgID) && (this->msgCode == other.msgCode));
}

bool MsgDataRep::operator ==(const IMsgDataRep &other) const
{
    return (
            (this->msgID == other.getMsgID())
            &&
            (this->msgCode == other.getMsgCode())
            );
}

void MsgDataRep::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
