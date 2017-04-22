/**
 * \file IMsgIDMappingStore.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for message id mapping stores
 */
#ifndef IMSGIDMAPPINGSTORE_H
#define IMSGIDMAPPINGSTORE_H

#include <QString>
#include <QColor>

#include "MsgIDType.h"
#include "IMsgIDMapping.h"

#include "IFileParsable.h"

/**
 * \brief The IMsgIDMappingStore interface
 */
class IMsgIDMappingStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
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
     * @brief Returns the #IMsgIDMapping that is related to the specified #MsgIDType
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
     * @note must emit #sgnl_MappingAboutToBeAdded and #sgnl_MappingAdded
     */
    virtual IMsgIDMapping &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDMapping &msgIDMappingToAppend
            ) = 0;
    /**
     * @brief Removes the #IMsgIDMapping that is related to relatedMsgID from the
     * store
     * 
     * @note must emit #sgnl_MappingAboutToBeRemoved and #sgnl_MappingRemoved
     */
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID) = 0;

    /**
     * @brief Clears the messages store removed all contained #IMsgIDMapping
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal must be emitted before a new #IMsgIDMapping is added to the
     * store
     */
    void sgnl_MappingAboutToBeAdded(const MsgIDType &relatedID);
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

public slots:
    /**
     * @brief Slot that adds the specified #IMsgIDMapping to the store
     * 
     * @note calls #addMsgIDMapping
     */
    virtual void slt_AddMsgIDMapping(const IMsgIDMapping &msgIDMappingToAdd)
    {
        addMsgIDMapping(msgIDMappingToAdd.getID(),msgIDMappingToAdd);
    }

    /**
     * @brief Slot that removes the specified #IMsgIDMapping from the store
     * 
     * @note calls #removeMsgIDMapping
     */
    virtual void slt_RemoveMsgIDMapping(const IMsgIDMapping &msgIDMappingToAdd)
    {
        //removeMsgIDMapping(msgIDMappingToAdd.getID(),msgIDMappingToAdd);
        removeMsgIDMapping(msgIDMappingToAdd.getID());
    }

};

#endif /* IMSGIDMAPPINGSTORE_H */
