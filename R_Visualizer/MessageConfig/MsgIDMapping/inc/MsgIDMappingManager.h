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

#include "IPrettyMsg.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

class IMsgIDMappingStore;

/**
 * @brief The MsgIDMappingManager
 */
class MsgIDMappingManager : public IMsgIDMappingManager
{
public:
    MsgIDMappingManager(IMsgIDMappingStore *msgIDMappingStore);
    virtual ~MsgIDMappingManager();

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToAlias(const QString &alias) const;

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

#endif /* MSGIDMAPPINGMANAGER_H */
