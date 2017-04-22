/**
 * @file MsgCodeMappingManager.h
 * @author Christian Neuberger
 * @date 2017-04-22
 * 
 * @brief The manager for #IMsgCodeMapping
 */
#ifndef MSGCODEMAPPINGMANAGER_H
#define MSGCODEMAPPINGMANAGER_H

#include "IMsgCodeMappingManager.h"

class FileParser;
class IMsgCodeMappingStore;

/**
 * @brief THe MsgCodeMappingManager
 */
class MsgCodeMappingManager : public IMsgCodeMappingManager
{
public:
    MsgCodeMappingManager(IMsgCodeMappingStore *msgCodeMappingStore);
    virtual ~MsgCodeMappingManager();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void accept(FileParser *visitor);

private:
    IMsgCodeMappingStore *msgCodeMappingStore;


    // IUserRoleManageable interface
public:
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);
};

#endif /* MSGCODEMAPPINGMANAGER_H */
