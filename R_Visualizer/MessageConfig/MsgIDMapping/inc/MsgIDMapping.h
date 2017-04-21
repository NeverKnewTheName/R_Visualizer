#ifndef MSGIDMAPPING_H
#define MSGIDMAPPING_H

#include "IMsgIDMapping.h"

#include "IPrettyMsg.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

class IMsgIDMappingStore;

class MsgIDMapping : public IMsgIDMapping
{
public:
    MsgIDMapping(IMsgIDMappingStore *msgIDMappingStore);
    virtual ~MsgIDMapping();

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

#endif /* MSGIDMAPPING_H */
