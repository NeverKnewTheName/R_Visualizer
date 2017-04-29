/**
 * @file SendMsgSingle.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation of #ISendMsgSingle
 */
#ifndef SENDMSGSINGLE_H
#define SENDMSGSINGLE_H

#include "ISendMsgSingle.h"
#include "Msg.h"


/**
 * @addtogroup SendMessagesSingleGroup
 * 
 * @{
 */

/**
 * @brief The SendMsgSingle
 */
class SendMsgSingle : public ISendMsgSingle
{
    Q_OBJECT
public:
    SendMsgSingle(QObject *parent = Q_NULLPTR);
    virtual ~SendMsgSingle();

    virtual void setMsg(const IMsg &msg);
    virtual void setMsgID(const MsgIDType &msgID);
    virtual void setMsgCode(const MsgCodeType &msgCode);
    virtual void setMsgData(const MsgDataType &msgData);

    virtual void sendMessage();
    virtual void sendMessage(const IMsg &msgToSend);

private:
    Msg messageToSend;
};

/**
 * @}
 */
#endif /* SENDMSGSINGLE_H */
