/**
 * @file MsgIDMappingManager.h
 * @author Christian Neuberger
 * @date 2017-04-22
 * 
 * @brief Mapping manager for #IMsgIDMapping
 */
#ifndef MSGIDMAPPINGMANAGER_H
#define MSGIDMAPPINGMANAGER_H

#include "IMsgIDMappingManager.h"

#include "MsgIDType.h"

class IMsgIDMappingStore;

/**
 * @addtogroup MsgIDMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDMappingManager
 */
class MsgIDMappingManager : public IMsgIDMappingManager
{
public:
    MsgIDMappingManager(
            IMsgIDMappingStore *msgIDMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDMappingManager();

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual void addMsgIDMapping(
            const IMsgIDMapping &msgIDMapping
            );

    virtual void removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            /* const IMsgIDMapping &msgIDMapping */
            );

    virtual IMsgIDMappingStore *getStore() const;

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void accept(FileParser *visitor);

    // IUserRoleManageable interface
public:
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    IMsgIDMappingStore *msgIDMappingStore;
};

/**
 * @}
 */

#endif /* MSGIDMAPPINGMANAGER_H */
