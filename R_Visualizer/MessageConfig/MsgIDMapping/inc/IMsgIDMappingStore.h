/**
 * \file IMsgIDMappingStore.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for message id mapping stores
 */
#ifndef IMSGIDMAPPINGSTORE_H
#define IMSGIDMAPPINGSTORE_H

#include <QObject>
#include <QString>
#include <QColor>

#include "MsgIDType.h"
#include "IMsgIDMapping.h"

#include "IFileParsable.h"

/**
 * @addtogroup MsgIDMappingGroup
 * 
 * @{
 */

/**
 * \brief The IMsgIDMappingStore interface
 */
class IMsgIDMappingStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
    IMsgIDMappingStore(QObject *parent = Q_NULLPTR) :
        QObject(parent){}
    virtual ~IMsgIDMappingStore(){}

    /**
     * @brief Returns the #MsgIDType from the contained #IMsgIDMapping that is
     * related  to the specified plain-text alias
     */
    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    /**
     * @brief Returns the plain-text alias from the contained #IMsgIDMapping that is
     * related to the specified #MsgIDType
     */
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgIDMapping that is related
     * to the specified #MsgIDType
     */
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgIDMapping that is related
     * to the specified plain-text alias
     */
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /**
     * @brief Returns the #IMsgIDMapping that is related to the specified
     * #MsgIDType contained in the store
     */
    virtual IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) = 0;

    /**
     * @brief Evaluates whether an #IMsgIDMapping related to the provided
     * #MsgIDType is contained in the store
     */
    virtual bool contains(const MsgIDType &msgID) const = 0;
    /**
     * @brief Evaluates whether the specified #IMsgIDMapping is contained in the
     * store
     */
    virtual bool contains(const IMsgIDMapping &msgIDMapping) const = 0;

    /**
     * @brief Adds the given #IMsgIDMapping to the store
     * 
     * @note must emit #sgnl_MsgIDMappingAboutToBeAdded and
     * #sgnl_MsgIDMappingAdded
     */
    virtual IMsgIDMapping &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDMapping &msgIDMappingToAppend
            ) = 0;
    /**
     * @brief Removes the #IMsgIDMapping that is related to relatedMsgID from
     * the store
     * 
     * @note must emit #sgnl_MsgIDMappingAboutToBeRemoved and
     * #sgnl_MsgIDMappingRemoved
     */
    virtual void removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            ) = 0;

    /**
     * @brief Clears the messages store removing all contained #IMsgIDMapping
     * 
     * @note must emit #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    virtual void clear() = 0;

    virtual QVector<MsgIDType> getContainedMsgIDs() const = 0;

signals:
    /**
     * @brief Signal must be emitted before a new #IMsgIDMapping is added to the
     * store
     */
    void sgnl_MsgIDMappingAboutToBeAdded(const MsgIDType &relatedID);
    /**
     * @brief Signal must be emitted after a new #IMsgIDMapping has been added to
     * the store
     */
    void sgnl_MsgIDMappingAdded(const MsgIDType &relatedID);

    /**
     * @brief Signal must be emitted before an existing #IMsgIDMapping is removed
     * from the store
     */
    void sgnl_MsgIDMappingAboutToBeRemoved(const MsgIDType &relatedID);
    /**
     * @brief Signal must be emitted after an existing #IMsgIDMapping has been
     * removed from the store
     */
    void sgnl_MsgIDMappingRemoved(const MsgIDType &relatedID);

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
    void sgnl_MappingHasChanged(const MsgIDType &relatedMsgID);

public slots:
    /**
     * @brief Slot that adds the specified #IMsgIDMapping to the store
     * 
     * @note calls #addMsgIDMapping
     */
    virtual void slt_AddMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDMapping &msgIDMappingToAdd
            )
    {
        addMsgIDMapping(msgID,msgIDMappingToAdd);
    }

    /**
     * @brief Slot that removes the specified #IMsgIDMapping from the store
     * 
     * @note calls #removeMsgIDMapping
     */
    virtual void slt_RemoveMsgIDMapping(
            const MsgIDType &msgID
            )
    {
        removeMsgIDMapping(msgID);
    }

    /**
     * @brief Slot that clears the store by removed all contained
     * #IMsgIDMapping from the store
     */
    virtual void slt_ClearStore()
    {
        clear();
    }

};

/**
 * @}
 */

#endif /* IMSGIDMAPPINGSTORE_H */
