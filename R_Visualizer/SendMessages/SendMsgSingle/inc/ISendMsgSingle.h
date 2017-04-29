/**
 * @file ISendMsgSingle.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for sending single messages
 */
#ifndef ISENDMSGSINGLE_H
#define ISENDMSGSINGLE_H

#include <QObject>

#include "IMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"


/**
 * @defgroup SendMessagesSingleGroup Send Single Messages
 * @ingroup SendMessagesGroup
 * 
 * @{
 */

/**
 * @brief The ISendMsgSingle interface
 */
class ISendMsgSingle : public QObject
{
    Q_OBJECT
public:
    ISendMsgSingle(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~ISendMsgSingle(){}

    virtual void setMsg(const IMsg &msg) = 0;
    virtual void setMsgID(const MsgIDType &msgID) = 0;
    virtual void setMsgCode(const MsgCodeType &msgCode) = 0;
    virtual void setMsgData(const MsgDataType &msgData) = 0;

    virtual void sendMessage() = 0;
    virtual void sendMessage(const IMsg &msgToSend) = 0;

signals:
    void sgnl_sendMessage(const IMsg &msgToSend);

public slots:
    virtual void slt_setMsg(const IMsg &msg)
    {
        setMsg(msg);
    }
    virtual void slt_setMsgID(const MsgIDType &msgID)
    {
        setMsgID(msgID);
    }
    virtual void slt_setMsgCode(const MsgCodeType &msgCode)
    {
        setMsgCode(msgCode);
    }
    virtual void slt_setMsgData(const MsgDataType &msgData)
    {
        setMsgData(msgData);
    }

};

/**
 * @}
 */
#endif /* ISENDMSGSINGLE_H */
