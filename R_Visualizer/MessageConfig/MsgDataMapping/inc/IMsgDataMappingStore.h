/**
 * @file IMsgDataMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for MsgData Mapping stores
 */
#ifndef IMSGDATAMAPPINGSTORE_H
#define IMSGDATAMAPPINGSTORE_H

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */

#include <QObject>

#include "IFileParsable.h"

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "MessageTypeIdentifier.h"

class IMsgDataMapping;
class IMsgDataFormatter;

class IMsgDataMappingStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
    IMsgDataMappingStore(QObject *parent = Q_NULLPTR) :
        QObject(parent){}
    virtual ~IMsgDataMappingStore(){}

    /**
     * @brief Returns the #IMsgDataFormatter from the contained
     * #IMsgDataMapping that is related to the specified #MsgIDType and
     * #MsgCodeType
     * 
     * @returns The #IMsgDataFormatter from the #IMsgDataMapping related to the
     * specified #MsgIDType and #MsgCodeType
     * @retval IMsgDataFormatter* A valid #IMsgDataFormatter
     * @retval Q_NULLPTR No matching #IMsgDataMapping was found in the store
     */
    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const = 0;

    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MessageTypeIdentifier &msgType
            ) const = 0;

    /**
     * @brief Returns the #IMsgDataMapping realted to the specified #MsgIDType
     * and #MsgCodeType contained in the store
     */
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

    /**
     * @brief Evaluates whether the specified #IMsgDataMapping is contained in
     * the store
     */
    virtual bool contains(const IMsgDataMapping &msgDataMapping) const = 0;

    /**
     * @brief Adds the given #IMsgDataMapping to the store
     * 
     * @note must emit #sgnl_MsgDataMappingAboutToBeAdded and
     * #sgnl_MsgDataMappingAdded
     */
    virtual IMsgDataMapping &addMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &msgDataMappingToAdd
            ) = 0;

    virtual IMsgDataMapping &addMsgDataMapping(
            const MessageTypeIdentifier &msgType,
            const IMsgDataMapping &msgDataMappingToAdd
            ) = 0;

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
            ) = 0;

    virtual void removeMsgDataMapping(
            const MessageTypeIdentifier &msgType
            ) = 0;

    /**
     * @brief Clears the store removing all contained #IMsgDataMapping
     * 
     * @note must emit #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal must be emitted before a new #IMsgDataMapping is added to
     * the store
     */
    void sgnl_MsgDataMappingAboutToBeAdded(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    /**
     * @brief Signal must be emitted after a new #IMsgDataMapping has been added
     * to the store
     */
    void sgnl_MsgDataMappingAdded(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    /**
     * @brief Signal must be emitted before an existing #IMsgDataMapping is
     * removed from the store
     */
    void sgnl_MsgDataMappingAboutToBeRemoved(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    /**
     * @brief Signal must be emitted after an existing #IMsgDataMapping has been
     * removed from the store
     */
    void sgnl_MsgDataMappingRemoved(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    /**
     * @brief Signal must be emitted before the store is cleared
     */
    void sgnl_AboutToBeCleared();

    /**
     * @brief Signal must be emitted after the store has been cleared
     */
    void sgnl_Cleared();

    /**
     * @brief Signal must be emitted when a contained mapping is changed
     */
    void sgnl_MappingHasChanged(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

public slots:
    /**
     * @brief Slot that adds the specified #IMsgDataMapping to the store
     * 
     * @note calls #addMsgDataMapping
     */
    virtual void slt_AddMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &msgDataMappingToAdd
            )
    {
        addMsgDataMapping(msgID,msgCode,msgDataMappingToAdd);
    }

    /**
     * @brief Slot that removes the specified #IMsgDataMapping from the store
     * 
     * @note calls #removeMsgDataMapping
     */
    virtual void slt_RemoveMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            )
    {
        removeMsgDataMapping(msgID,msgCode);
    }

    /**
     * @brief Slot that clears the store by removed all contained
     * #IMsgDataMapping from the store
     */
    virtual void slt_ClearStore()
    {
        clear();
    }
};

/**
 * @}
 */

#endif /* IMSGDATAMAPPINGSTORE_H */
