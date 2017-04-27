#ifndef CANANALYSERINTERFACEHANDLER_H
#define CANANALYSERINTERFACEHANDLER_H

#include <QTimer>
#include <QMutex>

#include "IInterfaceHandler.h"

#include "devicedriver.h"

/**
 * @addtogroup InterfaceHandlerGroup
 * 
 * @{
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
