/**
 * @file SendMsgSingle.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation of #ISendMsgSingle
 */
#ifndef SENDMSGSINGLE_H
#define SENDMSGSINGLE_H

#include <QObject>

#include "ISendMsgSingle.h"
#include "Msg.h"

/**
 * @brief The SendMsgSingle
 */
class SendMsgSingle : public QObject, public ISendMsgSingle
{
    Q_OBJECT
public:
    SendMsgSingle();
    virtual ~SendMsgSingle();

    virtual void setMsg(const IMsg &msg);
    virtual void setMsgID(const MsgIDType &msgID);
    virtual void setMsgCode(const MsgCodeType &msgCode);
    virtual void setMsgData(const MsgDataType &msgData);

    virtual void sendMessage(const IMsg &msgToSend = messageToSend);

signals:
    virtual void sgnl_sendMessage(const IMsg &msgToSend);

public slots:
    virtual void slt_setMsg(const IMsg &msg);
    virtual void slt_setMsgID(const MsgIDType &msgID);
    virtual void slt_setMsgCode(const MsgCodeType &msgCode);
    virtual void slt_setMsgData(const MsgDataType &msgData);

private:
    Msg messageToSend;
};

#endif /* SENDMSGSINGLE_H */
