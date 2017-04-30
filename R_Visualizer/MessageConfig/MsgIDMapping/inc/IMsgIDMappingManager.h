/**
 * @file IMsgIDMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief General interface for #IMsgIDMapping managers
 */
#ifndef IMSGIDMAPPINGMANAGER_H
#define IMSGIDMAPPINGMANAGER_H

#include "IMsgMappingManager.h"
#include "MsgIDType.h"

class IMsgIDMapping;
class IMsgIDMappingStore;

/**
 * @defgroup MsgIDMappingGroup Message ID Mapping
 * @ingroup MsgMappingGroup
 * 
 * Every class that is related to the Message ID Mapping
 * 
 * @{
 */

/**
 * @brief The IMsgIDMappingManager interface
 */
class IMsgIDMappingManager : public IMsgMappingManager
{
    Q_OBJECT
public:
    IMsgIDMappingManager(
            QObject *parent = Q_NULLPTR
            ) :
        IMsgMappingManager(parent)
        {}
    virtual ~IMsgIDMappingManager(){}

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    virtual void addMsgIDMapping(
            const IMsgIDMapping &msgIDMapping
            ) = 0;

    virtual void removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            ) = 0;

    virtual IMsgIDMappingStore *getStore() const = 0;
signals:
    void sgnl_MsgIDMappingManagerChanged(
            const IMsgIDMappingManager &mapping
            );

public slots:
    /**
     * @brief Slot adds the specified #IMsgIDMapping to the
     * #IMsgIDMappingManager
     * 
     * @note Calls #addMsgIDMapping
     */
    virtual void slt_addMsgIDMapping(const IMsgIDMapping &msgMapping)
    {
        addMsgIDMapping(msgMapping);
    }

    /**
     * @brief Slot removes the #IMsgIDMapping related to the specified
     * #MsgIDType from the #IMsgIDMappingManager
     * 
     * @note Calls #removeMsgIDMapping
     */
    virtual void slt_removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            )
    {
        removeMsgIDMapping(relatedMsgID);
    }

};

/**
 * @}
 */

#endif /* IMSGIDMAPPINGMANAGER_H */
