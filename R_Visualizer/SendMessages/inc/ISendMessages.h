/**
 * @file ISendMessages.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the SendMessages module
 */
#ifndef ISENDMESSAGES_H
#define ISENDMESSAGES_H

class ISendMsgSingle;
class ISendMsgPackage;

#include "IUserRoleManager.h"

/**
 * @brief The ISendMessages interface
 */
class ISendMessages
{
public:
    virtual ~ISendMessages(){}

    virtual void addSendMsgSingle(ISendMsgSingle *sendMsgSingleToAdd) = 0;
    virtual void addSendMsgPackage(ISendMsgPackage *sendMsgPackageToAdd) = 0;

    virtual void sendSingleMsg(ISendMsgSingle *sendMsgSingle) = 0;
    virtual void sendPackageMsg(ISendMsgPackage *sendMsgPackage) = 0;

public slots:
    void slt_applyUserRole(const UserRoleManagement::UserRole roleToApply);
};

#endif /* ISENDMESSAGES_H */
