/**
 * @file MessageConfig.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief The basic implementation of the Message Configuration module
 */
#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QObject>

#include "IMessageConfig.h"

#include "IUserRoleManager.h"

class IMsg;
class IPrettyMsg;
class IMsgMappingManager;
class IMsgIDMappingManager;
class IMsgCodeMappingManager;
class IMsgDataMappingManager;

/**
 * @brief The MessageConfig module is a standard implementation of the
 * #IMessageConfig interface
 * 
 * The standard implementation has per default mappings for message ID,
 * message code, and message data fields.
 */
class MessageConfig :
    public IMessageConfig
{
    Q_OBJECT
public:
    MessageConfig(
            IMsgIDMappingManager *msgIDMappingManager,
            IMsgCodeMappingManager *msgCodeMappingManager,
            IMsgDataMappingManager *msgDataMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MessageConfig();

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void prettifyMsgByMappingManager(
            IPrettyMsg &msgToPrettify,
            const IMsgMappingManager &mappingToApply
            ) const;

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);


private:
    IMsgIDMappingManager *msgIDMappingManager;
    IMsgCodeMappingManager *msgCodeMappingManager;
    IMsgDataMappingManager *msgDataMappingManager;
};

#endif /* MESSAGECONFIG_H */
