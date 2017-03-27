#include "devicehandler.h"
#define TIMER_INTERVAL 1000

#include "Msg.h"
#include "errorlogentry.h"

#include <QByteArray>
#include <can_packet.h>
#include <QDebug>

DeviceHandler::DeviceHandler()
{
    connect(&m_timer, &QTimer::timeout, this, &DeviceHandler::sltScan);
    //connect(this, &DeviceHandler::started, &m_timer, &QTimer::stop);
    //connect(this, &DeviceHandler::finished, &m_timer, &QTimer::start);
    //    connect(this, SIGNAL(started()),  &m_timer, SLOT(stop()));
    //    connect(this, SIGNAL(finished()), &m_timer, SLOT(start()));
    m_timer.setInterval(TIMER_INTERVAL);
    m_timer.start();
    m_stop = true;
    m_connected = false;
}

DeviceHandler::~DeviceHandler()
{
    QMutexLocker locker(&m_mutex);
    m_stop = true;
    this->wait();
}

bool DeviceHandler::connectTo(HID_Device &device)
{
    if (m_connected) m_driver.disconnectDevice();
    if (!m_driver.connectToDevice(device)) return false;
    if (!m_driver.setDateTime(QDateTime::currentDateTime()))
    {
        disconnect();
        return false;
    }
    m_connected = true;
    return true;
}

void DeviceHandler::disconnect()
{
    if(m_connected)
    {
        QMutexLocker locker(&m_mutex);
        m_stop = true;
        this->wait();
        m_driver.disconnectDevice();
        m_connected = false;
    }
}

void DeviceHandler::run()
{
#ifndef DUMMY_TRANSCEIVE
    while (1)
    {
        CAN_PacketPtr ptr;
        QMutexLocker locker(&m_mutex);
        if (m_stop) return;
        if (m_driver.readCANMessage(ptr) && !ptr.isNull())
        {
            QDateTime timestamp = ptr->timestamp();
            switch(ptr->type())
            {
            case CAN_Packet::Data_Frame:
            {
                Data_PacketPtr dataPtr = qSharedPointerDynamicCast<Data_Packet>(ptr);

                DataByteVect msgData;

                QByteArray canData = dataPtr->frame().data;
                MsgCodeType code = static_cast<MsgCodeType>(canData.at(0) & 0xFFu);

                for(int i = 1; i < canData.size(); i++)
                {
                    msgData.append(static_cast<quint8>(canData.at(i)));
                }

                Msg msg(timestamp, dataPtr->frame().ID_Standard, code, msgData);
                emit sigMsgReceived(msg);
            }
                break;
            case CAN_Packet::Error_Frame:
            {
                Error_PacketPtr errPtr = qSharedPointerDynamicCast<Error_Packet>(ptr);
                QString ErrMsg = QString("TX Coutner: %1\nRX Counter: %2\nDetails:%3")
                        .arg(errPtr->TX_Error_Counter())
                        .arg(errPtr->RX_Error_Counter())
                        .arg(errPtr->Status_Register_String());

                ErrorLogEntry *errEntry = new ErrorLogEntry(timestamp,ErrMsg);
                emit sigErrorMsgReceived(errEntry);
            }
                break;
            }
            emit sigPacketReceived(ptr);
        }
        else if (m_driver.error())
        {
            emit sigError(m_driver.getErrorString());
            qDebug() << "Driver error: " << m_driver.getErrorString();
            m_stop = true;
            m_driver.disconnectDevice();
            m_connected = false;
            return;
        }
    }
#else
    QTimer timer ;
    connect(&timer, &QTimer::timeout, this, &DeviceHandler::SLT_DEV_CREATE_PACKET);
    timer.start(3000);

    exec();
#endif
}

void DeviceHandler::sltScan()
{
    QMutexLocker locker(&m_mutex);
    if (m_driver.enumerate())
    {
        m_devices = m_driver.getDevices();
    }
    else if (m_driver.error())
    {
        emit sigError(m_driver.getErrorString());
    }
}

void DeviceHandler::sltStartCapture()
{
#ifndef DUMMY_TRANSCEIVE
    DeviceDriver::DeviceStates state = m_driver.getCurrentDeviceState();
    qDebug() << "Start Capture, State: " << state;
    if(m_connected && (state == DeviceDriver::STATE_USBCaptureInit || state == DeviceDriver::STATE_CaptureViaUSB))
    {
        if (m_driver.sendStartCommand())
        {
            QMutexLocker locker(&m_mutex);
            qDebug() << "StartCommand sent";
            m_stop = false;
            start();
        }
    }
#else
    QMutexLocker locker(&m_mutex);
    m_stop = false;
    start();
#endif
}

void DeviceHandler::sltStopCapture()
{
    QMutexLocker locker(&m_mutex);
#ifndef DUMMY_TRANSCEIVE
    if(m_connected && m_driver.getCurrentDeviceState() == DeviceDriver::STATE_CaptureViaUSB)
    {
        m_driver.sendStopCommand();
    }
#endif
    m_stop = true;
}

void DeviceHandler::sltSendPacket(CAN_PacketPtr packet)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!m_connected) return;
#ifndef DUMMY_TRANSCEIVE
    QThread::msleep(1);
    QMutexLocker locker(&m_mutex);
    qDebug() << "Mutex aquired";
    // CHANGED && TO ||
    if (!m_driver.writeCANMessage(packet) || m_driver.error())
    {
        qDebug() << "ERROR SENDING";
        emit sigError(m_driver.getErrorString());
    }
#endif
}

void DeviceHandler::sltSendMsg(const Msg &msgToSend)
{
    Data_Packet::Frame frame;

    frame.ID_Standard = msgToSend.getId();
    //    if (ui->cbIDE->isChecked())
    //    {
    //        frame.IDE = 1;
    //        frame.SRR = 1;
    //        frame.ID_Extended = ui->sbIDExt->value();
    //    }
    //    else
    //    {
    frame.IDE = 0;
    frame.SRR = 0;
    frame.ID_Extended = 0;
    //    }

    frame.RTR = 0;

    const MsgData &dataToSend = msgToSend.getMsgData();

    frame.DLC = dataToSend.DataSizeInBytes + 1; // + 1 for MsgCode

    frame.data.clear();
    frame.data.append(msgToSend.getCode() && 0xFF);
    for(quint8 byte : dataToSend.DataBytes)
    {
        frame.data.append(byte);
    }

    CAN_PacketPtr packet = CAN_PacketPtr(new Data_Packet());
    qSharedPointerDynamicCast<Data_Packet>(packet)->setFrame(frame);
    sltSendPacket(packet);
    //QTimer::singleShot(0,this, &SendMessages::emitSendMsg);
}

void DeviceHandler::sltSetFilterID(const quint32 filterID)
{
    if (!m_connected) return;

    QMutexLocker locker(&m_mutex);
    if (!m_driver.setIDFilter(filterID) && m_driver.error())
    {
        qDebug() << "ERROR SETTING FILTER ID";
        emit sigError(m_driver.getErrorString());
    }
}

void DeviceHandler::sltSetFilterMask(const quint32 filterMask)
{
    if (!m_connected) return;

    QMutexLocker locker(&m_mutex);
    if (!m_driver.setIDFilterMask(filterMask) && m_driver.error())
    {
        qDebug() << "ERROR SETTING FILTER MASK";
        emit sigError(m_driver.getErrorString());
    }
}

void DeviceHandler::sltChangeCANTiming(const int index)
{
    if (!m_connected) return;

    QMutexLocker locker(&m_mutex);
    if (!m_driver.changeCANTiming(index) && m_driver.error())
    {
        qDebug() << "ERROR CHANGING TIMING";
        emit sigError(m_driver.getErrorString());
    }
}

#define STD_FRAME 0
#define EXT_FRAME 1
#define FD_STD_FRAME 2
#define FD_EXT_FRAME 3
#define ERROR_FRAME 4
void DeviceHandler::SLT_DEV_CREATE_PACKET()
{
    CAN_PacketPtr ptr;

    switch(qrand() % (0+1))
    {
    case STD_FRAME :
    {
        quint8 dlc = rand() % (8 + 1 + 1) + 1;
        QByteArray byteArray;
        byteArray.fill(0, 17);
        byteArray[1]  = 0x00 | dlc;    //SRR = 0, IDE = 0, RTR = 0, DLC = 1-8
        //TIME STAMP dont care
        byteArray[4]  = 0x10;    //ID = 0x400 - 0x403
        byteArray[5]  = (rand() % (0x03 + 1)) << 2;
        /*
            byteArray[4]  = rand() % (0x1F + 1);    //ID = 0x000 - 0x7FF
            byteArray[5]  = rand() % (0xFC + 1);
            */
        //IDE dont care
        byteArray[8] = rand() % (0x10 +1);
        for (int i = 9; i < 8 + dlc; i++)
            byteArray[i]  = rand() % (0xFF +1); //DATA0-7 = 0x00-0xff
        ptr = CAN_PacketPtr(new Data_Packet(byteArray));
        break;
    }
    case EXT_FRAME :
    {
        quint8 dlc = rand() % (8 + 1 + 1) + 1;
        QByteArray byteArray;
        byteArray.fill(0, 17);
        byteArray[1]  = 0x60 | dlc;    //SRR = 1, IDE = 1, RTR = 0, DLC = 1-8
        //TIME STAMP dont care
        byteArray[4]  = rand() % (0x1F + 1);    //ID = 0x000 - 0x1FFFFFFF
        byteArray[5]  = rand() % (0xFF + 1);
        byteArray[6]  = rand() % (0xFF + 1);
        byteArray[7]  = rand() % (0xFF + 1);
        for (int i = 8; i < 8 + dlc; i++)
            byteArray[i]  = rand() % (0xFF +1); //DATA0-7 = 0x00-0xff

        ptr = CAN_PacketPtr(new Data_Packet(byteArray));
        break;
    }
    case FD_STD_FRAME :
    {
        Data_Packet::Frame frame;
        frame.ID_Standard = rand() % (0x7FF + 1);
        frame.ID_Extended = 0;
        frame.IDE = 0;
        frame.SRR = 0;
        frame.RTR = 0;
        frame.EDL = 1;
        frame.BRS = rand() % (1 + 1);
        frame.ESI = 1;
        frame.DLC = rand() % (64 + 1 + 1) + 1;
        for (int i = 0; i < frame.DLC; i++)
            frame.data[i] = rand() % (0xFF +1);
        Data_Packet *packet = new Data_Packet();
        packet->setFrame(frame);
        ptr.reset(packet);
        ptr->setTimestamp(QDateTime::currentDateTime());
        break;
    }
    case FD_EXT_FRAME :
    {
        Data_Packet::Frame frame;
        frame.ID_Standard = rand() % (0x7FF + 1);
        frame.ID_Extended = rand() % (0x3FFFF + 1);
        frame.IDE = 0;
        frame.SRR = 1;
        frame.RTR = 0;
        frame.EDL = 1;
        frame.BRS = rand() % (1 + 1);
        frame.ESI = 1;
        frame.DLC = rand() % (64 + 1 + 1) + 1;
        for (int i = 0; i < frame.DLC; i++)
            frame.data[i] = rand() % (0xFF +1);
        Data_Packet *packet = new Data_Packet();
        packet->setFrame(frame);
        ptr.reset(packet);
        ptr->setTimestamp(QDateTime::currentDateTime());
        break;
    }
    default :
    {
        QByteArray byteArray;
        byteArray.fill(0, 5);
        byteArray[0] = rand() % (0xFF + 1); //RX Error Counter
        byteArray[1] = rand() % (0xFF + 1); //TX Error Counter
        byteArray[2] = rand() % (0x07 + 1); //status register 0x000000 - 0x07FFFF
        byteArray[3] = rand() % (0xFF + 1);
        byteArray[4] = rand() % (0xFF + 1);
        ptr = CAN_PacketPtr(new Error_Packet(byteArray));
        break;
    }
    }
    if (ptr) emit sigPacketReceived(ptr);

    QMutexLocker locker(&m_mutex);
    if (m_stop) quit();
}
