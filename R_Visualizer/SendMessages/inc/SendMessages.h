/**
 * @file SendMessages.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default implementation of the #ISendMessages interface
 */
#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include <QObject>
#include <QVector>

#include "ISendMessages.h"

class ISendMsgSingle;
class ISendMsgPackage;
class IInterfaceHandler;

/**
 * @addtogroup SendMessagesGroup
 * 
 * @{
 */

/**
 * @brief The SendMessages
 */
class SendMessages : public ISendMessages
{
public:
    SendMessages(
            IInterfaceHandler *interfaceHandler,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMessages();

    virtual void addSendMsgSingle(ISendMsgSingle *sendMsgSingleToAdd);
    virtual void removeSendMsgSingle(ISendMsgSingle *sendMsgSingleToAdd);

    virtual void addSendMsgPackage(ISendMsgPackage *sendMsgPackageToAdd);
    virtual void removeSendMsgPackage(ISendMsgPackage *sendMsgPackageToAdd);

    virtual void sendMessage(const IMsg &msgToSend);

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    QVector<ISendMsgSingle *> sendMsgSingleInstances;
    QVector<ISendMsgPackage *> sendMsgPackageInstances;
    IInterfaceHandler *interfaceHandler;
    UserRoleManagement::UserRole currentUserRole;

};

/**
 * @}
 */
#endif /* SENDMESSAGES_H */
