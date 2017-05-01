/**
 * @file CANAnalyserInterfaceHandler.h
 * @author Christian Neuberger
 * @date date
 *
 * @brief CAN-Analyser USB-Interface Handler
 */
#ifndef CANANALYSERINTERFACEHANDLER_H
#define CANANALYSERINTERFACEHANDLER_H

#include <QTimer>
#include <QMutex>
#include <QThread>

#include "IInterfaceHandler.h"

#include "devicedriver.h"

/**
 * @addtogroup InterfaceHandlerGroup
 * 
 * @{
 */

class CANAlyserReceiveWorker : public QObject
{
    Q_OBJECT
public:
    CANAlyserReceiveWorker(
            QMutex &driverAccessMutex,
            DeviceDriver &deviceDriver
            );

signals:
    void sgnl_MessageReceived(const ITimestampedMsg &receivedMsg);
    void sgnl_ErrorReceived(const QString &errorMessage);
    void sgnl_DriverError(const QString &errorMessage);

public slots:
    void slt_Stop();

private:
    void listenForMessage();

private:
    QMutex stopMutex;
    QMutex &driverAcccessMutex;
    DeviceDriver &deviceDriver;
    bool stopReceiver;
};

/**
 * @brief The CANAnalyserInterfaceHandler
 */
class CANAnalyserInterfaceHandler : public IInterfaceHandler
{
    Q_OBJECT
public:
    CANAnalyserInterfaceHandler(QObject *parent = Q_NULLPTR);
    virtual ~CANAnalyserInterfaceHandler();

    /**
     * @brief Connects to the first connected CAN-Analyser USB Interface
     */
    bool connectToInterface();
    bool disconnectFromInterface();
    bool startSession();
    bool stopSession();
    bool sendMessage(const IMsg &msgToSend);

    bool isConnected() const;
    bool isSessionInProgress() const;

private:
    bool sendCANFrame(CAN_PacketPtr packet);
    virtual CAN_PacketPtr convertMsgToCANFrame(const IMsg &msgToConvert) const;

private slots:
    /* void slt_ScanForInterface(); */

private:
    DeviceDriver canAnalyserDeviceDriver;
    /* QTimer timer; */
    QMutex driverAccessMutex;

    bool connected;
    bool sessionInProgress;
};

/**
 * @}
 */

#endif /* CANANALYSERINTERFACEHANDLER_H */
