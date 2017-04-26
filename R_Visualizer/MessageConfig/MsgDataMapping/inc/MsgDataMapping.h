/**
 * \file MsgDataMapping.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Mappingresentation of message data
 */
#ifndef MSGDATAMAPPING_H
#define MSGDATAMAPPING_H

#include "IMsgDataMapping.h"
#include "IMsgDataFormatter.h"

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */

/**
 * \brief The MsgDataMapping
 */
class MsgDataMapping : public MsgDataMappingCRTPHelper<MsgDataMapping>
{
public:
    MsgDataMapping();

    MsgDataMapping(const MsgDataMapping &other);

    MsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            IMsgDataFormatter *msgDataFormatter
            );
    virtual ~MsgDataMapping();

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType &msgID);

    MsgCodeType getMsgCode() const;
    void setMsgCode(const MsgCodeType &msgCode);

    IMsgDataFormatter *getMsgDataFormatter() const;
    void setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter);

    QString parseMsgData(const IMsg &msg) const;

    IMsgDataMapping &operator =(const IMsgDataMapping &other);
    bool operator ==(const MsgDataMapping &other) const;
    bool operator ==(const IMsgDataMapping &other) const;

    /**
     * @brief qHash implementation to use #MsgDataMapping as a QHash key
     */
    friend uint qHash(const MsgDataMapping &key, uint seed)
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

/**
 * @}
 */

#endif /* MSGDATAMAPPING_H */
