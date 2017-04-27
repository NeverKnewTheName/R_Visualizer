#include "InterfaceHandler.h"

#include <QDebug>

InterfaceHandler::InterfaceHandler(QObject *parent) :
    IInterfaceHandler(parent)
{
}

InterfaceHandler::~InterfaceHandler()
{
}


bool InterfaceHandler::connectToInterface()
{
    qDebug() << "Connect to device";
}

bool InterfaceHandler::disconnectFromInterface()
{
    qDebug() << "Disconnect from device";
}

bool InterfaceHandler::startSession()
{
    qDebug() << "Start a monitoring session";
}

bool InterfaceHandler::stopSession()
{
    qDebug() << "Stop a monitoring session";
}

bool InterfaceHandler::sendMessage(const IMsg &msgToSend)
{
    qDebug() << "Send a message";
}

bool InterfaceHandler::isConnected() const
{
}

bool InterfaceHandler::isSessionInProgress() const
{
}
