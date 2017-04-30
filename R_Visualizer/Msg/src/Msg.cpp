#include "Msg.h"

#include "fileparser.h"

Msg::Msg() :
        msgID(),
        msgCode(),
        msgData()
{
}

Msg::Msg(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const MsgDataType &msgData
    ) :
        msgID(msgID),
        msgCode(msgCode),
        msgData(msgData)
{
}

Msg::Msg(const Msg &other) :
        msgID(other.msgID),
        msgCode(other.msgCode),
        msgData(other.msgData)
{
}

Msg::~Msg()
{
}


void Msg::setMsgID(const MsgIDType &msgID)
{
    this->msgID = msgID;
}

const MsgIDType Msg::getMsgID() const
{
    return msgID;
}


void Msg::setMsgCode(const MsgCodeType &msgCode)
{
    this->msgCode = msgCode;
}

const MsgCodeType Msg::getMsgCode() const
{
    return msgCode;
}


void Msg::setMsgData(const MsgDataType &msgData)
{
    this->msgData = msgData;
}

const MsgDataType Msg::getMsgData() const
{
    return msgData;
}

Msg::operator QString() const
{
    QString tempMsgDataString("");

    int msgDataSize = msgData.size();

    while(msgDataSize--)
    {
        tempMsgDataString.prepend(
                static_cast<QString>(msgData.at(msgDataSize)) + " "
                );
    }

    /* switch(msgData.size()) */
    /* { */
    /*     case 7: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(6))); */
    /*     case 6: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(5))); */
    /*     case 5: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(4))); */
    /*     case 4: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(3))); */
    /*     case 3: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(2))); */
    /*     case 2: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(1)); */
    /*     case 1: */
    /*         tempMsgDataString.prepend(static_cast<QString>(msgData.at(0)); */
    /* } */

    return QString("MsgID: %1 - MsgCode: %2 - MsgData %3")
        .arg(static_cast<QString>(msgID))
        .arg(static_cast<QString>(msgCode))
        .arg(tempMsgDataString);
}

void Msg::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
