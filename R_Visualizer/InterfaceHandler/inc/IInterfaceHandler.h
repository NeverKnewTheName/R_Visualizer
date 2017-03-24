/**
 * \file IInterfaceHandler.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief An interface for interface devices
 * 
 * \note The application expects all interfaces that connect to a system to
 * implement this interface.
 */
#ifndef IINTERFACEHANDLER_H
#define IINTERFACEHANDLER_H

#include "IMsg.h"

/**
 * \brief The IInterfaceHandler interface
 */
class IInterfaceHandler
{
public:
    virtual ~IInterfaceHandler(){}

    virtual bool connectToInterface() = 0;
    virtual bool disconnectFromInterface() = 0;

    virtual bool startSession() = 0;
    virtual bool stopSession() = 0;

    virtual void sendMessage(const IMsg &msgToSend) = 0;

signals:
    virtual void sgnl_MessageReceived(const IMsg &receivedMsg) = 0;
    virtual void sgnl_Error(const QString &errorDescription) = 0;

private slots:
    virtual void slt_SendMessage(const IMsg &msgToSend) = 0;
    virtual void slt_StartSession() = 0;
    virtual void slt_StopSession() = 0;

};

#endif /* IINTERFACEHANDLER_H */
