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

#include "MsgCodeType.h"

class IMsgCodeMappingStore;

/**
 * @addtogroup MsgCodeMappingGroup
 * 
 * @{
 */

/**
 * @brief THe MsgCodeMappingManager
 */
class MsgCodeMappingManager : public IMsgCodeMappingManager
{
public:
    MsgCodeMappingManager(
            IMsgCodeMappingStore *msgCodeMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeMappingManager();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual void addMsgCodeMapping(
            const IMsgCodeMapping &msgCodeMapping
            );

    virtual void removeMsgCodeMapping(
            const MsgCodeType &relatedMsgCode
            /* const IMsgCodeMapping &msgCodeMapping */
            );

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual IMsgCodeMappingStore *getStore() const;

    virtual void accept(FileParser *visitor);

    // IUserRoleManageable interface
public:
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    IMsgCodeMappingStore *msgCodeMappingStore;
};

/**
 * @}
 */

#endif /* MSGCODEMAPPINGMANAGER_H */
