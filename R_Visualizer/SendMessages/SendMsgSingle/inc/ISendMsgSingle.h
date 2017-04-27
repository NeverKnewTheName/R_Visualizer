/**
 * @file ISendMsgSingle.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for sending single messages
 */
#ifndef ISENDMSGSINGLE_H
#define ISENDMSGSINGLE_H

#include "IMsg.h"

/**
 * @defgroup SendMessagesSingleGroup Send Single Messages
 * @ingroup SendMessagesGroup
 * 
 * @{
 */

/**
 * @brief The ISendMsgSingle interface
 */
class ISendMsgSingle
{
public:
    virtual ~ISendMsgSingle();

    virtual void setMsg(const IMsg &msg) = 0;
    virtual void setMsgID(const MsgIDType &msgID) = 0;
    virtual void setMsgCode(const MsgCodeType &msgCode) = 0;
    virtual void setMsgData(const MsgDataType &msgData) = 0;

    virtual void sendMessage(const IMsg &msgToSend) = 0;

signals:
    virtual void sgnl_sendMessage(const IMsg &msgToSend) = 0;

public slots:
    virtual void slt_setMsg(const IMsg &msg) = 0;
    virtual void slt_setMsgID(const MsgIDType &msgID) = 0;
    virtual void slt_setMsgCode(const MsgCodeType &msgCode) = 0;
    virtual void slt_setMsgData(const MsgDataType &msgData) = 0;

};

/**
 * @}
 */
#endif /* ISENDMSGSINGLE_H */
