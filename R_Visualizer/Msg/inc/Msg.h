/**
 * @file Msg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief A regular message
 */
#ifndef MSG_H
#define MSG_H

#include "IMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

/**
 * @brief The Msg
 */
class Msg : IMsgCRTPHelper<Msg>
{
public:
    Msg();
    Msg(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const MsgDataType &msgData = MsgDataType()
        );
    Msg(const Msg &other);
    virtual ~Msg();

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

private:
    MsgIDType msgID;
    MsgCodeType msgCode;
    MsgDataType msgData;
};

#endif /* MSG_H */
