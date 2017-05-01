#include "CANAnalyserInterfaceHandler.h"

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QMutexLocker>

#include "IMsg.h"
#include "ITimestampedMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

#include "TimestampedMsg.h"

CANAnalyserInterfaceHandler::CANAnalyserInterfaceHandler(
        QObject *parent
        ) :
    IInterfaceHandler(parent),
    canAnalyserDeviceDriver(),
    startReceiverTimer(new QTimer()),
    stopReceiverTimer(new QTimer()),
    receiverWorker(
            new CANAlyserReceiveWorker(
                driverAccessMutex,
                canAnalyserDeviceDriver
                )
            ),
    connected(false),
    sessionInProgress(false)
{
    startReceiverTimer->setSingleShot(true);
    stopReceiverTimer->setSingleShot(true);

    receiverWorker->moveToThread(&receiverThread);
    startReceiverTimer->moveToThread(&receiverThread);
    stopReceiverTimer->moveToThread(&receiverThread);

    connect(
            startReceiverTimer,
            &QTimer::timeout,
            receiverWorker,
            &CANAlyserReceiveWorker::slt_Start
           );

    connect(
            stopReceiverTimer,
            &QTimer::timeout,
            receiverWorker,
            &CANAlyserReceiveWorker::slt_Stop
           );

    connect(
            receiverWorker,
            &CANAlyserReceiveWorker::sgnl_MessageReceived,
            this,
            &IInterfaceHandler::sgnl_MessageReceived,
            Qt::QueuedConnection
           );

    connect(
            receiverWorker,
            &CANAlyserReceiveWorker::sgnl_ErrorReceived,
            this,
            &IInterfaceHandler::sgnl_ErrorReceived,
            Qt::QueuedConnection
           );

    connect(
            receiverWorker,
            &CANAlyserReceiveWorker::sgnl_DriverError,
            this,
            &CANAnalyserInterfaceHandler::slt_DriverError,
            Qt::QueuedConnection
           );

    /* connect( */
    /*         &timer, */
    /*         &QTimer::timeout, */
    /*         this, */
    /*         &CANAnalyserInterfaceHandler::slt_ScanForInterface */
    /*         ); */

    /* timer.setInterval(1000); */
    /* timer.start(); */
}

CANAnalyserInterfaceHandler::~CANAnalyserInterfaceHandler()
{
}


bool CANAnalyserInterfaceHandler::connectToInterface()
{
    if(connected)
    {
        if(!disconnectFromInterface())
        {
            return false;
        }
    }

    QMutexLocker mutexLocker(&driverAccessMutex);

    if(canAnalyserDeviceDriver.enumerate())
    {
        HID_DevicesList deviceList = canAnalyserDeviceDriver.getDevices();
        if(deviceList.isEmpty())
        {
            //error no device connected
            emit sgnl_Error(QString("No connected CAN-Analyser found!"));
            return false;
        }

        HID_Device &foundDevice = deviceList.first();
        connected = canAnalyserDeviceDriver.connectToDevice(foundDevice);

        if(!connected)
        {
            emit sgnl_Error(
                    QString(
                        "Could not connect to CAN-Analyser: %1"
                        ).arg(foundDevice.product)
                    );
            return false;
        }

    }
    else
    {
        if(canAnalyserDeviceDriver.error())
        {
        emit sgnl_Error(canAnalyserDeviceDriver.getErrorString());
        }

        return false;
    }


    const bool setTimesampSuccess =
        canAnalyserDeviceDriver.setDateTime(QDateTime::currentDateTime());

    mutexLocker.unlock();

    if(!setTimesampSuccess)
    {
        emit sgnl_Error(QString("Could not set timestamp for CAN-Analyser!"));
        disconnectFromInterface();
        return false;
    }

    emit sgnl_Connected();
    return true;
}

bool CANAnalyserInterfaceHandler::disconnectFromInterface()
{
    if(connected)
    {
        if(sessionInProgress)
        {
            stopSession();
        }

        QMutexLocker mutexLocker(&driverAccessMutex);

        const bool disconnectSuccessfull =
            canAnalyserDeviceDriver.disconnectDevice();

        if(disconnectSuccessfull)
        {
            connected = false;

            emit sgnl_Disconnected();
            return true;
        }
        else
        {
            sgnl_Error(QString("Could not disconnect from CAN-Analyser!"));
            return false;
        }
    }

    emit sgnl_Disconnected();
    return true;
}

bool CANAnalyserInterfaceHandler::startSession()
{
    if(!connected)
    {
        emit sgnl_Error(QString("Cannot start session when not connected!"));
        return false;
    }

    if(sessionInProgress)
    {
        emit sgnl_Error(QString("A session is already in progress!"));
        return false;
    }

    QMutexLocker driverLock(&driverAccessMutex);
    DeviceDriver::DeviceStates state =
        canAnalyserDeviceDriver.getCurrentDeviceState();

    if(!(
            state == DeviceDriver::STATE_USBCaptureInit ||
            state == DeviceDriver::STATE_CaptureViaUSB
      ))
    {
        emit sgnl_Error(QString("Device State Mismatch!"));
        return false;
    }

    if(!canAnalyserDeviceDriver.sendStartCommand())
    {
        emit sgnl_Error(QString("Error starting Session!"));
        return false;
    }

    driverLock.unlock();

    receiverThread.start();
    startReceiverTimer->start(0);

    sessionInProgress = true;

    emit sgnl_SessionStarted();
    return true;
}

bool CANAnalyserInterfaceHandler::stopSession()
{
    if(!connected)
    {
        emit sgnl_Error(QString("Cannot stop session when not connected!"));
        return false;
    }

    QMutexLocker driverLock(&driverAccessMutex);

    DeviceDriver::DeviceStates state =
        canAnalyserDeviceDriver.getCurrentDeviceState();

    if( state != DeviceDriver::STATE_CaptureViaUSB )
    {
        emit sgnl_Error(QString("Device State Mismatch"));
        return false;
    }

    if(!canAnalyserDeviceDriver.sendStopCommand())
    {
        emit sgnl_Error(QString("Error stopping Session"));
        return false;
    }

    stopReceiverTimer->start(0);

    sessionInProgress = false;

    emit sgnl_SessionStopped();
    return true;
}

bool CANAnalyserInterfaceHandler::sendMessage(const IMsg &msgToSend)
{
    /////////DEBUG//////////
    
    emit sgnl_MessageReceived(
            TimestampedMsg(
                msgToSend,
                QDateTime::currentDateTime()
                )
            );
    
    /////////DEBUG//////////

    if(!connected)
    {
        emit sgnl_Error(
                QString(
                    "Cannot send messages when no CAN-Analyser is connected!"
                    )
                );
        return false;
    }

    CAN_PacketPtr canFrameToSend = convertMsgToCANFrame(msgToSend);

    return sendCANFrame(canFrameToSend);
}

bool CANAnalyserInterfaceHandler::isConnected() const
{
    return connected;
}

bool CANAnalyserInterfaceHandler::isSessionInProgress() const
{
    return sessionInProgress;
}

bool CANAnalyserInterfaceHandler::sendCANFrame(CAN_PacketPtr packet)
{
    QMutexLocker mutexLocker(&driverAccessMutex);

    const bool frameSent = canAnalyserDeviceDriver.writeCANMessage(packet);

    if(!frameSent)
    {
        if(canAnalyserDeviceDriver.error())
        {
            emit sgnl_Error(
                    QString("Error while sending CAN Frame: %1")
                        .arg(canAnalyserDeviceDriver.getErrorString())
                    );
        }
        else
        {
            emit sgnl_Error(QString("Could not send CAN Frame!"));
        }
    }

    return frameSent;
}

CAN_PacketPtr CANAnalyserInterfaceHandler::convertMsgToCANFrame(
        const IMsg &msgToConvert
        ) const
{
    Data_Packet::Frame canFrame;

    canFrame.ID_Standard = static_cast<MsgIDType::type>(msgToConvert.getMsgID());
    canFrame.IDE = 0;
    canFrame.SRR = 0;
    canFrame.ID_Extended = 0;
    canFrame.RTR = 0;

    const MsgDataType &msgData = msgToConvert.getMsgData();

    canFrame.DLC = msgData.size() + 1; // +1 for the message code

    canFrame.data.clear();
    canFrame.data.append(
            static_cast<MsgCodeType::type>(msgToConvert.getMsgCode())
            );

    for(const MsgDataByteType &dataByte : msgData)
    {
        canFrame.data.append(
                static_cast<MsgDataByteType::type>(dataByte)
                );
    }

    CAN_PacketPtr packet = CAN_PacketPtr(new Data_Packet());
    qSharedPointerDynamicCast<Data_Packet>(packet)->setFrame(canFrame);
    
    return packet;
}

void CANAnalyserInterfaceHandler::slt_DriverError(
        const QString &errorDescription
        )
{
    emit sgnl_Error(QString("DriverError: %1").arg(errorDescription));
    disconnectFromInterface();
}

/* void CANAnalyserInterfaceHandler::slt_ScanForInterface() */
/* { */
/*     qDebug() << "Scanning!"; */
/* } */

CANAlyserReceiveWorker::CANAlyserReceiveWorker(
        QMutex &driverAccessMutex,
        DeviceDriver &deviceDriver
        ) :
    driverAccessMutex(driverAccessMutex),
    deviceDriver(deviceDriver),
    stopReceiver(false)
{

}

void CANAlyserReceiveWorker::slt_Start()
{
    {
        QMutexLocker stopLocker(&stopMutex);
        stopReceiver = false;
    }
    listenForMessage();
}

void CANAlyserReceiveWorker::slt_Stop()
{
    QMutexLocker stopLocker(&stopMutex);
    stopReceiver = true;
}

void CANAlyserReceiveWorker::listenForMessage()
{
    while (1)
    {
        CAN_PacketPtr ptr;
        QMutexLocker locker(&stopMutex);
        if (stopReceiver) return;

        QMutexLocker driverLock(&driverAccessMutex);
        bool readSuccess = deviceDriver.readCANMessage(ptr);

        if ( readSuccess && !ptr.isNull())
        {
            driverLock.unlock();
            QDateTime timestamp = ptr->timestamp();
            switch(ptr->type())
            {
            case CAN_Packet::Data_Frame:
            {
                Data_PacketPtr dataPtr =
                    qSharedPointerDynamicCast<Data_Packet>(ptr);

                MsgDataType msgData;

                QByteArray canData = dataPtr->frame().data;
                MsgCodeType code =
                    static_cast<MsgCodeType>(canData.at(0) & 0xFFu);

                for(int i = 1; i < canData.size(); i++)
                {
                    msgData.append(MsgDataByteType(canData.at(i)));
                }

                Msg msg(
                        MsgIDType(dataPtr->frame().ID_Standard),
                        MsgCodeType(code),
                        msgData
                        );
                TimestampedMsg timestampedMsg(msg,timestamp);
                emit sgnl_MessageReceived(timestampedMsg);
            }
                break;
            case CAN_Packet::Error_Frame:
            {
                Error_PacketPtr errPtr =
                    qSharedPointerDynamicCast<Error_Packet>(ptr);
                QString ErrMsg =
                    QString("TX Coutner: %1\nRX Counter: %2\nDetails:%3")
                        .arg(errPtr->TX_Error_Counter())
                        .arg(errPtr->RX_Error_Counter())
                        .arg(errPtr->Status_Register_String());

                /* ErrorLogEntry *errEntry = new ErrorLogEntry(timestamp,ErrMsg); */
                /* emit sigErrorMsgReceived(errEntry); */
                emit sgnl_ErrorReceived(ErrMsg);
            }
                break;
            }
            //emit sigPacketReceived(ptr);
        }
        else
        {
            if (deviceDriver.error())
            {
                emit sgnl_DriverError(deviceDriver.getErrorString());
                qDebug() << "Driver error: " << deviceDriver.getErrorString();
                stopReceiver = true;
                /* deviceDriver.disconnectDevice(); */
                /* m_connected = false; */
                return;
            }
        }
    }
}
