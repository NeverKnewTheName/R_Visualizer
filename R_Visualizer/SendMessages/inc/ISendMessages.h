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
class IMsg;

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

    /**
     * @brief Central method to send a message within the #ISendMessages module
     * 
     * This method helps sub-modules to send their messages. This way there is
     * only one central connection to the interface handler needed.
     */
    virtual void sendMessage(const IMsg &msgToSend) = 0;

    virtual void applyUserRole(
            const UserRoleManagement::UserRole roleToApply
            ) = 0;

public slots:
    /**
     * @brief Slot to send a single #IMsg
     *
     * @note Calls #sendMessage
     */
    virtual void slt_SendMessage(const IMsg &msgToSend)
    {
        sendMessage(msgToSend);
    }


    /**
     * @brief Slot to change the #UserRole for the module
     */
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
