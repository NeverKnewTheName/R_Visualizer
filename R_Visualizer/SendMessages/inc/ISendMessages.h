/**
 * @file ISendMessages.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the SendMessages module
 */
#ifndef ISENDMESSAGES_H
#define ISENDMESSAGES_H

#include <QObject>

#include "IUserRoleManager.h"

class ISendMsgSingle;
class ISendMsgPackage;

/**
 * @defgroup SendMessagesGroup Send Messages
 * 
 * @{
 */

/**
 * @brief The ISendMessages interface
 */
class ISendMessages : public QObject
{
    Q_OBJECT
public:
    ISendMessages(
            QObject *parent = Q_NULLPTR
            ) :
        QObject(parent)
    {}
    virtual ~ISendMessages(){}

    virtual void addSendMsgSingle(
            ISendMsgSingle *sendMsgSingleToAdd
            ) = 0;
    virtual void removeSendMsgSingle(
            ISendMsgSingle *sendMsgSingleToAdd
            ) = 0;

    virtual void addSendMsgPackage(
            ISendMsgPackage *sendMsgPackageToAdd
            ) = 0;
    virtual void removeSendMsgPackage(
            ISendMsgPackage *sendMsgPackageToAdd
            ) = 0;

    virtual void applyUserRole(
            const UserRoleManagement::UserRole roleToApply
            ) = 0;

public slots:
    virtual void slt_applyUserRole(
            const UserRoleManagement::UserRole roleToApply
            )
    {
        applyUserRole(roleToApply);
    }
};

/**
 * @}
 */
#endif /* ISENDMESSAGES_H */
