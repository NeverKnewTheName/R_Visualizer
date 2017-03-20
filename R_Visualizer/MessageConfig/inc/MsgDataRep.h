#ifndef MSGDATAREP_H
#define MSGDATAREP_H

#include "IMsgDataRep.h"
#include "IFileParsable.h"

class MsgDataRep : public IMsgDataRep, public IFileParsable
{
public:
    MsgDataRep();

    MsgDataRep(const MsgDataRep &other);

    MsgDataRep(
            const MsgIDType msgID,
            const MsgCodeType msgCode,
            const QString &formatString
            );
    virtual ~MsgDataRep();

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType msgID);

    MsgCodeType getMsgCode() const;
    void setMsgCode(const MsgCodeType msgCode);

    QString getFormatString() const;
    void setFormatString(const QString &formatString);

    QString parseMsgData(const MsgData &msgData) const;

private:
    MsgIDType msgID;

    MsgCodeType msgCode;

    QString formatString;
};

#endif /* MSGDATAREP_H */
