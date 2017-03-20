#ifndef IMSGDATAREP_H
#define IMSGDATAREP_H

#include <QString>

#include "msg.h"

class IMsgDataRep
{
public:
    virtual ~IMsgDataRep(){}

    virtual MsgIDType getMsgID() const = 0;
    virtual void setMsgID(const MsgIDType id) = 0;

    virtual MsgCodeType getMsgCode() const = 0;
    virtual void setMsgCode(const MsgCodeType code) = 0;

    virtual QString getFormatString() const = 0;
    virtual void setFormatString(const QString &formatString) = 0;

    virtual QString parseMsgData(const MsgData &msgData) const = 0;
};

#endif /* IMSGDATAREP_H */
