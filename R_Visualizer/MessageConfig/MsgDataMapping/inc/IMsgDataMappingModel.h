/**
 * \file IMsgDataMappingModel.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for models storing message data mappings
 */
#ifndef IMSGDATAMAPPINGMODEL_H
#define IMSGDATAMAPPINGMODEL_H

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

#include "MessageTypeIdentifier.h"

class IMsgDataMapping;

/**
 * \brief The IMsgDataMappingModel interface
 */
class IMsgDataMappingModel
{
public:
    virtual ~IMsgDataMappingModel(){}

    virtual IMsgDataMapping &getMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) = 0;

    virtual IMsgDataMapping &getMsgDataMapping(
            const MessageTypeIdentifier &msgType
            ) = 0;

    /**
     * @brief Evaluates whether an #IMsgDataMapping related to the provided
     * #MsgIDType and #MsgCodeType is contained in the store
     */
    virtual bool contains(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const = 0;

    virtual bool contains(
            const MessageTypeIdentifier &msgType
            ) const = 0;

    virtual bool contains(
            const IMsgDataMapping &msgDataMapping
            ) const = 0;

    virtual void appendMsgDataMapping(
            const IMsgDataMapping &msgDataMappingToAppend
            ) = 0;

    virtual void removeMsgDataMapping(
            const MsgIDType &relatedMsgID,
            const MsgCodeType &relatedMsgCode
            ) = 0;

    virtual void removeMsgDataMapping(
            const MessageTypeIdentifier &msgType
            ) = 0;

    virtual void clear() = 0;
};

#endif /* IMSGDATAMAPPINGMODEL_H */
