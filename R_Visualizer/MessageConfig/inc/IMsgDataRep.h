#ifndef IMSGDATAREP_H
#define IMSGDATAREP_H

#include <QString>

#include "msg.h"

class IMsgDataRep
{
public:
    IMsgDataRep();
    virtual ~IMsgDataRep();

    MsgIDType getMsgID() const = 0;
    void setMsgID(const MsgIDType id) = 0;

    MsgCodeType getMsgCode() const = 0;
    void setMsgCode(const MsgCodeType code) = 0;

    QString getFormatString() const = 0;
    void setFormatString(const QString &formatString) = 0;

    QString parseMsgData(const MsgData &msgData) const = 0;
};

#endif /* IMSGDATAREP_H */
