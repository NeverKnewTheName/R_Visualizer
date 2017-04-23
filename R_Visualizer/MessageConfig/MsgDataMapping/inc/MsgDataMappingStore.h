/**
 * @file MsgDataMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default MsgData Mapping store
 */
#ifndef MSGDATAMAPPINGSTORE_H
#define MSGDATAMAPPINGSTORE_H

#include "IMsgDataMappingStore.h"

#include <QHash>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "IMsgDataMapping.h"
#include "MsgDataMapping.h"

class FileParser;


/**
 * @brief The MsgDataMappingStore
 */
class MsgDataMappingStore : public IMsgDataMappingStore
{
public:
    MsgDataMappingStore(
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingStore();

    /**
     * @brief Returns the #IMsgDataFormatter from the contained
     * #IMsgDataMapping that is related to the specified #MsgIDType and
     * #MsgCodeType
     */
    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MessageTypeIdentifier &msgType
            ) const;

    /**
     * @brief Returns the #IMsgDataMapping realted to the specified #MsgIDType
     * and #MsgCodeType contained in the store
     */
    virtual IMsgDataMapping &getMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual IMsgDataMapping &getMsgDataMapping(
            const MessageTypeIdentifier &msgType
            );

    /**
     * @brief Evaluates whether an #IMsgDataMapping related to the provided
     * #MsgIDType and #MsgCodeType is contained in the store
     */
    virtual bool contains(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual bool contains(
            const MessageTypeIdentifier &msgType
            ) const;

    /**
     * @brief Evaluates whether the specified #IMsgDataMapping is contained in
     * the store
     */
    virtual bool contains(
            const IMsgDataMapping &msgDataMapping
            ) const;

    /**
     * @brief Adds the given #IMsgDataMapping to the store
     * 
     * @note must emit #sgnl_MsgDataMappingAboutToBeAdded and
     * #sgnl_MsgDataMappingAdded
     */
    virtual IMsgDataMapping &addMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &msgDataMappingToAdd = MsgDataMapping()
            );

    virtual IMsgDataMapping &addMsgDataMapping(
            const MessageTypeIdentifier &msgType,
            const IMsgDataMapping &msgDataMappingToAdd
            );

    /**
     * @brief Removes the #IMsgDataMapping that is related to relatedMsgID from
     * the store
     * 
     * @note must emit #sgnl_MsgDataMappingAboutToBeRemoved and
     * #sgnl_MsgDataMappingRemoved
     */
    virtual void removeMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual void removeMsgDataMapping(
            const MessageTypeIdentifier &msgType
            );

    /**
     * @brief Clears the store removing all contained #IMsgDataMapping
     * 
     * @note must emit #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    virtual void clear();

    void accept(FileParser *visitor);

private:
    QHash<MessageTypeIdentifier, MsgDataMapping> msgDataMappingStore;
};

#endif /* MSGDATAMAPPINGSTORE_H */
