/**
 * @file TimestampedMsg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief Simple implementation of a message with a timestamp
 */
#ifndef TIMESTAMPEDMSG_H
#define TIMESTAMPEDMSG_H

#include "ITimestampedMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

/**
 * @brief The TimestampedMsg
 * 
 * \note Additional facade for #Msg
 */
class TimestampedMsg : public ITimestampedMsgCRTPHelper<TimestampedMsg>
{
public:
    TimestampedMsg();
    TimestampedMsg(const Msg &originalMsg, QDateTime timestamp = QDateTime());
    TimestampedMsg(const TimestampedMsg &other);

    virtual ~TimestampedMsg();

    void setTimestamp(const QDateTime &newTimestamp);
    const QDateTime getTimestamp() const;

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

    const Msg getOriginalMsg() const;

private:
    Msg originalMsg;
    QDateTime msgTimestamp;
};

#endif /* TIMESTAMPEDMSG_H */
