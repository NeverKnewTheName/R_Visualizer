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

#include <QObject>

class IMsg;
class ITimestampedMsg;

/**
 * @defgroup InterfaceHandlerGroup Interface Handler
 * 
 * @{
 */

/**
 * \brief The IInterfaceHandler interface
 */
class IInterfaceHandler : public QObject
{
    Q_OBJECT
public:
    IInterfaceHandler(
            QObject *parent = Q_NULLPTR
            ) :
        QObject(parent)
    {}
    virtual ~IInterfaceHandler(){}

    /**
     * @brief Connect to the connected interface
     * 
     * Connect the #IInterfaceHandler to the interface to configure the
     * connected interface or start a monitoring session.
     * 
     * Additionally connecting to the connected interface might
     * configure the connected interface. This could be handled individually
     * by the respective #IInterfaceHandler derivate. Therefore see the
     * derivate's documenation.
     * 
     * @pre The connected interface must not be connected already
     * @post The connected interface is connected to the #IInterfaceHandler
     */
    virtual bool connectToInterface() = 0;

    /**
     * @brief Disconnect from the connected interface
     * 
     * Disconnects the #IInterfaceHandler from the interface.
     * 
     * Additionally disconnecting from the connected interface might
     * configure the connected interface. This could be handled individually
     * by the respective #IInterfaceHandler derivate. Therefore see the
     * derivate's documenation.
     * 
     * @pre A connection must have been established prior to calling this method
     * @post The connection to the interface is disconnected
     */
    virtual bool disconnectFromInterface() = 0;

    /**
     * @brief Start a monitoring session
     * 
     * Starting a monitoring session prompts the #IInterfaceHandler to
     * propagate messages received by the connected interface via the
     * #sgnl_MessageReceived signal.
     * 
     * Additionally starting a session might configure the connected interface.
     * This could be handled individually by the respective #IInterfaceHandler
     * derivate. Therefore see the derivate's documentation.
     * 
     * @pre #connectToInterface must have been called successfully prior to
     * calling this function
     * 
     * @post A monitoring session is started
     * 
     * @warning This method must not be called when a session is already in
     * progress
     */
    virtual bool startSession() = 0;

    /**
     * @brief Stop a monitoring session
     * 
     * Stopping a monitoring session prompts the #IInterfaceHandler to stop
     * propagating messages received by the connected interface.
     * 
     * Additionally stopping a session might configure the connected interface.
     * This could be handled individually by the respective #IInterfaceHandler
     * derivate. Therefore see the derivate's documentation.
     * 
     * @pre A session must be in progress
     * @post A monitoring session is stopped, but the connection is still held
     */
    virtual bool stopSession() = 0;

    /**
     * @brief Send an #IMsg via the connected interface
     * 
     * @pre The #IInterfaceHandler must been connected to the connected
     * interface a monitoring session must be in progress
     */
    virtual bool sendMessage(const IMsg &msgToSend) = 0;

    /**
     * @brief Returns whether the #IInterfaceHandler is connected to a
     * connected interface
     * 
     * @returns Connections status of the #IInterfaceHandler
     * @retval true #IInterfaceHandler is connected to a connected interface
     * @retval false #IInterfaceHandler is not connected to a connected
     * interface
     */
    virtual bool isConnected() const = 0;

    /**
     * @brief Returns whether a monitoring session is currently in progress
     * 
     * @returns Session status of the #IInterfaceHandler
     * @retval true A monitoring session is currently in progress
     * @retval false No monitoring session is currently in progress
     */
    virtual bool isSessionInProgress() const = 0;

signals:
    /**
     * @brief Signal is emitted during an active monitoring session when a
     * messages is received from the connected interface
     */
    void sgnl_MessageReceived(const ITimestampedMsg &receivedMsg);

    /**
     * @brief Signal is emitted during an active monitoring session when an
     * error was received from the connected interface
     */
    void sgnl_ErrorReceived(const QString &receivedError);

    /**
     * @brief Signal is emitted when an error is detected by the
     * #IInterfaceHandler
     */
    void sgnl_Error(const QString &errorDescription);

    void sgnl_Connected();
    void sgnl_Disconnected();
    void sgnl_SessionStarted();
    void sgnl_SessionStopped();

public slots:
    /**
     * @brief Slot to connect to the interface
     * 
     * @note Calls #connectToInterface
     */
    virtual void slt_Connect()
    {
        connectToInterface();
    }

    /**
     * @brief Slot to disconnect from the interface
     * 
     * @note Calls #disconnectFromInterface
     */
    virtual void slt_Disconnect()
    {
        disconnectFromInterface();
    }

    /**
     * @brief Slot to send a message via the interface
     * 
     * @note Calls #sendMessage
     */
    virtual void slt_SendMessage(const IMsg &msgToSend)
    {
        sendMessage(msgToSend);
    }

    /**
     * @brief Slot to start a monitoring session
     * 
     * Upon starting a monitoring session, the #IInterfaceHandler will
     * distribute messages that are received from the connected interface
     * 
     * @note Calls #startSession
     */
    virtual void slt_StartSession()
    {
        startSession();
    }

    /**
     * @brief Slot to stop a monitoring session
     * 
     * Stopping a monitoring session stops the #IInterfaceHandler from
     * distributing received messages from the connected interface
     * 
     * @note Calls #stopSession
     */
    virtual void slt_StopSession()
    {
        stopSession();
    }

};

/**
 * @}
 */

#endif /* IINTERFACEHANDLER_H */
