#include "InterfaceHandler.h"

InterfaceHandler::InterfaceHandler(QObject *parent) :
    IInterfaceHandler(parent)
{
}

InterfaceHandler::~InterfaceHandler()
{
}


bool InterfaceHandler::connectToInterface()
{
}

bool InterfaceHandler::disconnectFromInterface()
{
}

bool InterfaceHandler::startSession()
{
}

bool InterfaceHandler::stopSession()
{
}

void InterfaceHandler::sendMessage(const IMsg &msgToSend)
{
}