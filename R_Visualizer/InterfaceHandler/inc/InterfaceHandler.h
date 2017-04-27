/**
 * @file InterfaceHandler.h
 * @author Christian Neuberger
 * @date 2017-04-27
 * 
 * @brief Default implementation of the InterfaceHandler
 */
#ifndef INTERFACEHANDLER_H
#define INTERFACEHANDLER_H

#include "IInterfaceHandler.h"

class InterfaceHandler : public IInterfaceHandler
{
public:
    InterfaceHandler(QObject *parent = Q_NULLPTR);
    virtual ~InterfaceHandler();

    virtual bool connectToInterface();
    virtual bool disconnectFromInterface();
    virtual bool startSession();
    virtual bool stopSession();
    virtual void sendMessage(const IMsg &msgToSend);

    virtual bool isConnected() const;
    virtual bool isSessionInProgress() const;
private:

};

#endif /* INTERFACEHANDLER_H */
