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
class IMsgMapping;
class IMsgIDMapping;
class IMsgCodeMapping;
class IMsgDataMapping;

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
            IMsgIDMapping *msgIDMapping,
            IMsgCodeMapping *msgCodeMapping,
            IMsgDataMapping *msgDataMapping,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MessageConfig();

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void prettifyMsgByMapping(
            IPrettyMsg &msgToPrettify,
            const IMsgMapping &mappingToApply
            ) const;

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);


private:
    IMsgIDMapping *msgIDMapping;
    IMsgCodeMapping *msgCodeMapping;
    IMsgDataMapping *msgDataMapping;
};

#endif /* MESSAGECONFIG_H */
