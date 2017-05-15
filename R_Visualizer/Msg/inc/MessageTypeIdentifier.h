/**
 * @file MessageTypeIdentifier.h
 * @author Christian Neuberger
 * @date 2017-04-23
 * 
 * @brief Identifier for messages types based on #MsgIDType and #MsgCodeType
 * 
 * The purpose of this identifier is to create a unique identifier per message
 * type. A Message Type is the combination of ID and Code that clearly define
 * teh purpose of a message and thus its type.
 */
#ifndef MESSAGETYPIDENTIFIER_H
#define MESSAGETYPIDENTIFIER_H

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

#include <QHash>

/**
 * @addtogroup MessageGroup
 * 
 * @{
 */

class MessageTypeIdentifier
{
public:
    MessageTypeIdentifier() :
        msgID(MsgIDType(0)),
        msgCode(MsgCodeType(0))
    {}

    MessageTypeIdentifier(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) :
        msgID(msgID),
        msgCode(msgCode)
    {}

    MessageTypeIdentifier(const MessageTypeIdentifier &other) :
        msgID(other.msgID),
        msgCode(other.msgCode)
    {}

    virtual ~MessageTypeIdentifier(){}

    MessageTypeIdentifier &operator =(const MessageTypeIdentifier &other)
    {
        msgID = other.msgID;
        msgCode = other.msgCode;

        return *this;
    }

    MsgIDType getID() const
    {
        return msgID;
    }

    MsgCodeType getCode() const
    {
        return msgCode;
    }

private:
    MsgIDType msgID;
    MsgCodeType msgCode;
};

inline uint qHash(const MessageTypeIdentifier &key, uint seed = 0)
{
    return qHash(
        (
         (
          (
            static_cast<MsgIDType::type>(key.getID())
            <<
            (8*sizeof(MsgCodeType::type))
          )
          &
          static_cast<MsgCodeType::type>(key.getCode())
         )
        ),
        seed
        );
}

inline bool operator ==(
        const MessageTypeIdentifier &lhs,
        const MessageTypeIdentifier &rhs
        )
{
    return (
            lhs.getID() == rhs.getID()
            &&
            lhs.getCode() == rhs.getCode()
           );
}

inline bool operator !=(
        const MessageTypeIdentifier &lhs,
        const MessageTypeIdentifier &rhs
        )
{
    return !operator ==(lhs,rhs);
}

/**
 * @}
 */

#endif /* MESSAGETYPIDENTIFIER_H */
