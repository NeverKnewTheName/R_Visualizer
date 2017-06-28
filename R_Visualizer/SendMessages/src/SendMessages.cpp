#include "SendMessages.h"

#include "ISendMsgSingle.h"
#include "ISendMsgPackage.h"

#include "IInterfaceHandler.h"

#include "Msg.h"

SendMessages::SendMessages(
        IInterfaceHandler *interfaceHandler,
        QObject *parent
        ) :
    ISendMessages(parent),
    interfaceHandler(interfaceHandler),
    currentUserRole(UserRoleManagement::NormalUserRole)
{
}

SendMessages::~SendMessages()
{
}

void SendMessages::addSendMsgSingle(ISendMsgSingle *sendMsgSingle)
{
    sendMsgSingleInstances.append(sendMsgSingle);

    connect(
            sendMsgSingle,
            &ISendMsgSingle::sgnl_sendMessage,
            this,
            &ISendMessages::slt_SendMessage
            );
}

void SendMessages::removeSendMsgSingle(ISendMsgSingle *sendMsgSingle)
{
    sendMsgSingleInstances.removeAll(sendMsgSingle);
}

void SendMessages::addSendMsgPackage(ISendMsgPackage *sendMsgPackage)
{
    sendMsgPackageInstances.append(sendMsgPackage);
    connect(
            sendMsgPackage,
            &ISendMsgPackage::sgnl_sendMsg,
            this,
            &ISendMessages::slt_SendMessage
            );
    connect(
            sendMsgPackage,
            &ISendMsgPackage::sgnl_SendStdMsg,
                [=](const Msg &msg){
                    interfaceHandler->sendMessage(msg);
                }
            );
}

void SendMessages::removeSendMsgPackage(ISendMsgPackage *sendMsgPackage)
{
    sendMsgPackageInstances.removeAll(sendMsgPackage);
}

void SendMessages::sendMessage(const IMsg &msgToSend)
{
    interfaceHandler->sendMessage(msgToSend);
}

void SendMessages::sendMessage(const Msg &msgToSend)
{
    interfaceHandler->sendMessage(msgToSend);
}

void SendMessages::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
    currentUserRole = roleToApply;
}
