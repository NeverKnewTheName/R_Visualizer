#include "SendMessages.h"

#include "ISendMsgSingle.h"
#include "ISendMsgPackage.h"

SendMessages::SendMessages(QObject *parent) : 
    QObject(parent)
{
}

SendMessages::~SendMessages()
{
}

void SendMessages::addSendMsgSingle(ISendMsgSingle *sendMsgSingle)
{
    sendMsgSingleInstances.append(sendMsgSingle);
}

void SendMessages::removeSendMsgSingle(ISendMsgSingle *sendMsgSingle)
{
    sendMsgSingleInstances.removeAll(sendMsgSingle);
}

void SendMessages::addSendMsgPackage(ISendMsgPackage *sendMsgPackage)
{
    sendMsgPackageInstances.append(sendMsgPackage);
}

void SendMessages::removeSendMsgPackage(ISendMsgPackage *sendMsgPackage)
{
    sendMsgPackageInstances.removeAll(sendMsgPackage);
}

void SendMessages::slt_applyUserRole(const UserRoleMngr::UserRole roleToApply)
{
    currentUserRole = roleToApply;
}
