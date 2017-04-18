/**
 * @file InterfaceHandlerNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The signals and slot handler for the #IInterfaceHandler
 */
#ifndef INTERFACEHANDLERNOTIFIER_H
#define INTERFACEHANDLERNOTIFIER_H

#include <QObject>

class IInterfaceHandler;

/**
 * @brief The IMessageStreamNotifier
 */
class InterfaceHandlerNotifier : public QObject
{
    Q_OBJECT
public:
    InterfaceHandlerNotifier(
            IInterfaceHandler *interfaceHandler
            QObject *parent = Q_NULLPTR
            );
    virtual ~InterfaceHandlerNotifier();

signals:

public slots:

private:
    IInterfaceHandler *interfaceHandler;
};

#endif /* INTERFACEHANDLERNOTIFIER_H */
