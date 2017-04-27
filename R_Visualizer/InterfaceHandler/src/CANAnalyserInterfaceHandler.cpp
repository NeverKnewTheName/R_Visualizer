#include "CANAnalyserInterfaceHandler.h"

#include <QString>
#include <QDebug>
#include <QDateTime>

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
    connected(false),
    sessionInProgress(false)
{
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
    else if(canAnalyserDeviceDriver.error())
    {
        emit sgnl_Error(canAnalyserDeviceDriver.getErrorString());

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
            return true;
        }
        else
        {
            sgnl_Error(QString("Could not disconnect from CAN-Analyser!"));
            return false;
        }
    }

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

    //ToDO !!!

    sessionInProgress = true;
    return true;
}

bool CANAnalyserInterfaceHandler::stopSession()
{

    //ToDO !!!

    sessionInProgress = false;
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

/* void CANAnalyserInterfaceHandler::slt_ScanForInterface() */
/* { */
/*     qDebug() << "Scanning!"; */
/* } */
