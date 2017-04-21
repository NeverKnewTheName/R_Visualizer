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
#include "IMsgIDRep.h"

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
     * @brief Returns the #MsgIDType from the contained #IMsgIDRep that is
     * related  to the specified plain-text alias
     */
    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    /**
     * @brief Returns the plain-text alias from the contained #IMsgIDRep that is
     * related to the specified #MsgIDType
     */
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgIDRep that is related
     * to the specified #MsgIDType
     */
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    /**
     * @brief Returns the QColor from the contained #IMsgIDRep that is related
     * to the specified plain-text alias
     */
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /**
     * @brief Returns the #IMsgIDRep that is related to the specified #MsgIDType
     */
    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID) = 0;

    /**
     * @brief Evaluates whether an #IMsgIDRep related to the provided
     * #MsgIDType is contained in the store
     */
    virtual bool contains(const MsgIDType &msgID) const = 0;
    /**
     * @brief Evaluates whether the specified #IMsgIDRep is contained in the
     * store
     */
    virtual bool contains(const IMsgIDRep &msgIDRep) const = 0;

    /**
     * @brief Adds the given #IMsgIDRep to the store
     * 
     * @note must emit #sgnl_MappingAboutToBeAdded and #sgnl_MappingAdded
     */
    virtual IMsgIDRep &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDRep &msgIDRepToAppend
            ) = 0;
    /**
     * @brief Removes the #IMsgIDRep that is related to relatedMsgID from the
     * store
     * 
     * @note must emit #sgnl_MappingAboutToBeRemoved and #sgnl_MappingRemoved
     */
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID) = 0;

    /**
     * @brief Clears the messages store removed all contained #IMsgIDRep
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal must be emitted before a new #IMsgIDRep is added to the
     * store
     */
    void sgnl_MappingAboutToBeAdded(const MsgIDType &relatedID);
    /**
     * @brief Signal must be emitted after a new #IMsgIDRep has been added to
     * the store
     */
    void sgnl_MsgIDRepAdded(const MsgIDType &relatedID);

    /**
     * @brief Signal must be emitted before an existing #IMsgIDRep is removed
     * from the store
     */
    void sgnl_MsgIDRepAboutToBeRemoved(const MsgIDType &relatedID);
    /**
     * @brief Signal must be emitted after an existing #IMsgIDRep has been
     * removed from the store
     */
    void sgnl_MsgIDRepRemoved(const MsgIDType &relatedID);

public slots:
    /**
     * @brief Slot that adds the specified #IMsgIDRep to the store
     * 
     * @note calls #addMsgIDMapping
     */
    virtual void slt_AddMsgIDRep(const IMsgIDRep &msgIDRepToAdd)
    {
        addMsgIDMapping(msgIDRepToAdd.getID(),msgIDRepToAdd);
    }

    /**
     * @brief Slot that removes the specified #IMsgIDRep from the store
     * 
     * @note calls #removeMsgIDMapping
     */
    virtual void slt_RemoveMsgIDRep(const IMsgIDRep &msgIDRepToAdd)
    {
        removeMsgIDMapping(msgIDRepToAdd.getID(),msgIDRepToAdd);
    }

};

#endif /* IMSGIDMAPPINGSTORE_H */
