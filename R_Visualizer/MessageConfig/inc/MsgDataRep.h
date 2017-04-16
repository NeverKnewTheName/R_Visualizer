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
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            IMsgDataFormatter *msgDataFormatter
            );
    virtual ~MsgDataRep();

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType &msgID);

    MsgCodeType getMsgCode() const;
    void setMsgCode(const MsgCodeType &msgCode);

    IMsgDataFormatter *getMsgDataFormatter() const;
    void setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter);

    QString parseMsgData(const IMsg &msg) const;

    IMsgDataRep &operator =(const IMsgDataRep &other);
    bool operator ==(const MsgDataRep &other) const;
    bool operator ==(const IMsgDataRep &other) const;

    /**
     * @brief qHash implementation to use #MsgDataRep as a QHash key
     */
    friend uint qHash(const MsgDataRep &key, uint seed)
    {
        return qHash(
            static_cast<uint>(static_cast<MsgIDType::type>(key.msgID)) || (
            static_cast<uint>(static_cast<MsgCodeType::type>(key.msgCode))
            << ( 8 * sizeof(MsgCodeType::type))),
            seed);
    }

    void accept(FileParser *visitor);
private:
    MsgIDType msgID;
    MsgCodeType msgCode;
    IMsgDataFormatter *msgDataFormatter;
};

#endif /* MSGDATAREP_H */
