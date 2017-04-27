/**
 * @file IMsgCodeMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for message code mapping stores
 */
#ifndef IMSGCODEMAPPINGSTORE_H
#define IMSGCODEMAPPINGSTORE_H

#include <QObject>
#include <QString>
#include <QColor>

#include "MsgCodeType.h"
#include "IMsgCodeMapping.h"

#include "IFileParsable.h"

/**
 * @addtogroup MsgCodeMappingGroup
 * 
 * @{
 */

/**
 * @brief The IMsgCodeMappingStore interface
 */
class IMsgCodeMappingStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
    IMsgCodeMappingStore(QObject *parent = Q_NULLPTR) :
        QObject(parent){}
    virtual ~IMsgCodeMappingStore(){}

    /**
     * @brief Returns the #MsgCodeType from the contained #IMsgCodeMapping that
     * is related to the specific plain-text alias
     */
    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const = 0;
    /**
     * @brief Returns the plain-text alias from the contained #IMsgCodeMapping
     * that is related to the specific #MsgCodeType
     */
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgCodeMapping that is
     * related to the specific plain-text alias
     */
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgCodeMapping that is
     * related to the specified plain-text alias
     */
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /**
     * @brief Returns the #IMsgCodeMapping that is related to the specified
     * #MsgCodeType contained in the store
     */
    virtual IMsgCodeMapping &getMsgCodeMappingToMsgCode(
            const MsgCodeType &msgCode
            ) = 0;

    /**
     * @brief Evaluates whether an #IMsgCodeMapping related to the specified
     * #MsgCodeType is contained in the store
     */
    virtual bool contains(const MsgCodeType &msgCode) const = 0;
    /**
     * @brief Evaluates whether the specified #IMsgCodeMapping is contained in
     * the store
     */
    virtual bool contains(const IMsgCodeMapping &msgCodeMapping) const = 0;

    /**
     * @brief Adds the given #IMsgCodeMapping to the store
     * 
     * @note must emit #sgnl_MappingAboutToBeAdded and #sgnl_MappingAdd
     */
    virtual IMsgCodeMapping &addMsgCodeMapping(
            const MsgCodeType &msgCode,
            const IMsgCodeMapping &msgCodeMappingToAdd
            ) = 0;

    /**
     * @brief Removes the #IMsgCodeMapping that is related to the specified
     * #MsgCodeType from the store
     * 
     * @note must emit #sgnl_MappingAboutToBeRemoved and #sgnl_MappingRemoved
     */
    virtual void removeMsgCodeMapping(const MsgCodeType &relatedMsgCode) = 0;

    /**
     * @brief Clears the message store removing all contained #IMsgCodeMapping
     * 
     * @note must emit #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal must be emitted before a new #IMsgCodeMapping is added to the
     * store
     */
    void sgnl_MsgCodeMappingAboutToBeAdded(const MsgCodeType &relatedCode);
    /**
     * @brief Signal must be emitted after a new #IMsgCodeMapping has been added to
     * the store
     */
    void sgnl_MsgCodeMappingAdded(const MsgCodeType &relatedCode);

    /**
     * @brief Signal must be emitted before an existing #IMsgCodeMapping is removed
     * from the store
     */
    void sgnl_MsgCodeMappingAboutToBeRemoved(const MsgCodeType &relatedCode);
    /**
     * @brief Signal must be emitted after an existing #IMsgCodeMapping has been
     * removed from the store
     */
    void sgnl_MsgCodeMappingRemoved(const MsgCodeType &relatedCode);

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
    void sgnl_MappingHasChanged(const MsgCodeType &relatedMsgCode);

public slots:
    /**
     * @brief Slot that adds the specified #IMsgCodeMapping to the store
     * 
     * @note calls #addMsgCodeMapping
     */
    virtual void slt_AddMsgCodeMapping(
            const MsgCodeType &msgCode,
            const IMsgCodeMapping &msgCodeMappingToAdd
            )
    {
        addMsgCodeMapping(msgCode,msgCodeMappingToAdd);
    }

    /**
     * @brief Slot that removes the specified #IMsgCodeMapping from the store
     * 
     * @note calls #removeMsgCodeMapping
     */
    virtual void slt_RemoveMsgCodeMapping(
            const MsgCodeType &msgCode
            )
    {
        removeMsgCodeMapping(msgCode);
    }

    /**
     * @brief Slot that clears the store by removed all contained
     * #IMsgCodeMapping from the store
     */
    virtual void slt_ClearStore()
    {
        clear();
    }

};

/**
 * @}
 */

#endif /* IMSGCODEMAPPINGSTORE_H */
