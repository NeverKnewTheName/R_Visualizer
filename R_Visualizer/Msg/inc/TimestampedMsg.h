/**
 * @file TimestampedMsg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief Simple implementation of a message with a timestamp
 */
#ifndef TIMESTAMPEDMSG_H
#define TIMESTAMPEDMSG_H

#include <QMetaType>
#include <QDateTime>

#include "ITimestampedMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "Msg.h"

class FileParser;

/**
 * @addtogroup MessageGroup
 * 
 * @{
 */

/**
 * @brief The TimestampedMsg
 * 
 * \note Additional facade for #Msg
 */
class TimestampedMsg : public ITimestampedMsg
{
public:
    TimestampedMsg();
    TimestampedMsg(
            const Msg &originalMsg,
            const QDateTime &timestamp = QDateTime()
            );
    TimestampedMsg(const TimestampedMsg &other);

    virtual ~TimestampedMsg();

    void setTimestamp(const QDateTime &newTimestamp);
    const QDateTime getTimestamp() const;

    IMsg *cloneMsg() const;

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

    const Msg getOriginalMsg() const;
    void setOriginalMsg(const Msg &originalMsg);

    void accept(FileParser *visitor);

private:
    Msg originalMsg;
    QDateTime msgTimestamp;
};

Q_DECLARE_METATYPE(TimestampedMsg);

/**
 * @}
 */
#endif /* TIMESTAMPEDMSG_H */
