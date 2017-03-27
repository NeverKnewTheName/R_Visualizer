/**
 * \file MsgDataRep.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Representation of message data
 */
#ifndef MSGDATAREP_H
#define MSGDATAREP_H

#include "IMsgDataRep.h"
#include "IMsgDataFormatter.h"

/**
 * \brief The MsgDataRep
 */
class MsgDataRep : public MsgDataRepCRTPHelper<MsgDataRep>
{
public:
    MsgDataRep();

    MsgDataRep(const MsgDataRep &other);

    MsgDataRep(
            const MsgIDType msgID,
            const MsgCodeType msgCode,
            IMsgDataFormatter *msgDataFormatter
            );
    virtual ~MsgDataRep();

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType msgID);

    MsgCodeType getMsgCode() const;
    void setMsgCode(const MsgCodeType msgCode);

    void setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter);

    QString parseMsgData(const IMsg &msg) const;

private:
    MsgIDType msgID;
    MsgCodeType msgCode;
    IMsgDataFormatter *msgDataFormatter;
};

#endif /* MSGDATAREP_H */
