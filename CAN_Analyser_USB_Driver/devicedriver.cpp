#include "devicedriver.h"

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#include <QString>
#include <QDebug>

#define VENDOR_ID 0xA215
#define PRODUCT_ID 0x0FA5
#define TIMEOUT 1000

DeviceDriver::DeviceDriver() :
    m_handle(NULL),
    m_error(false)
{
    hid_init();
}

DeviceDriver::~DeviceDriver()
{
    hid_exit();
}

bool DeviceDriver::enumerate()
{
    struct hid_device_info *device = NULL;
    device = hid_enumerate(VENDOR_ID, PRODUCT_ID);

    m_devices.clear();
    if (!device) return false;

    m_devices.clear();
    while (device) {
#ifdef DEBUG
        printDevice(device);
#endif
        HID_Device dev;
        dev.path = QString(device->path);
        dev.vendorID = device->vendor_id;
        dev.productID = device->product_id;
        if (device->serial_number)
            dev.serialNumber = QString::fromStdWString(device->serial_number);
        dev.releaseNumber = device->release_number;
        if (device->manufacturer_string)
            dev.manufacturer = QString::fromStdWString(device->manufacturer_string);
        if (device->product_string)
            dev.product = QString::fromStdWString(device->product_string);
        m_devices.append(dev);
        device = device->next;
    }
    hid_free_enumeration(device);
    return true;
}

QString DeviceDriver::getErrorString()
{
    m_error = false;
    if (m_handle)
        return QString::fromWCharArray(hid_error(m_handle));
    else
        return QString("Not connected to a device");
}

bool DeviceDriver::connectToDevice(HID_Device &device)
{
    wchar_t serialNumber[device.serialNumber.size()+1];
    int len = device.serialNumber.toWCharArray(serialNumber);
    serialNumber[len] = L'\0';
    m_handle = hid_open(device.vendorID, device.productID, serialNumber);
    if (m_handle) {
        hid_set_nonblocking(m_handle, 1);
        return true;
    }
    m_error = true;
    return false;
}

bool DeviceDriver::disconnectDevice()
{
    if (!m_handle) return false;

    hid_close(m_handle);
    m_handle = NULL;
    return true;
}

#define FEATURE_START_SIZE 2
bool DeviceDriver::sendStartCommand()
{
    if (!m_handle) return false;

    unsigned char buffer[FEATURE_START_SIZE];
    buffer[0] = DEVICE_STATE_REPORT;
    buffer[1] = STATE_CaptureViaUSB;
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_START_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at sendStartCommand(res==%d): %ls\n", res, hid_error(m_handle));
        return false;
    }
    return true;
}

#define FEATURE_STOP_SIZE 2
bool DeviceDriver::sendStopCommand()
{
    if (!m_handle) return false;

    unsigned char buffer[FEATURE_STOP_SIZE];
    buffer[0] = DEVICE_STATE_REPORT;
    buffer[1] = STATE_Standby;
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_STOP_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at sendStartCommand(res==%d): %ls\n", res, hid_error(m_handle));
        return false;
    }
    return true;
}

#define FEATURE_STATE_SIZE 2
DeviceDriver::DeviceStates DeviceDriver::getCurrentDeviceState()
{
    if (!m_handle) return STATE_Init;

    unsigned char buffer[FEATURE_STATE_SIZE];
    buffer[0] = DEVICE_STATE_REPORT;
    int res = hid_get_feature_report(m_handle, buffer, FEATURE_STATE_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at getReadyCommand (res==%d): %ls\n", res, hid_error(m_handle));
        return STATE_Init;
    }
    return (DeviceDriver::DeviceStates)buffer[1];
}

#define FEATURE_DATE_SIZE 6
bool DeviceDriver::setDateTime(const QDateTime &time)
{
    if (!m_handle) return false;

    quint32 data = (quint32) time.toTime_t();
    unsigned char buffer[FEATURE_DATE_SIZE];
    buffer[0] = CONFIGURATION_REPORT;
    buffer[1] = CONFIGURE_CLOCK;
    buffer[2] = (data & 0xFF000000) >> 24;
    buffer[3] = (data & 0xFF0000) >> 16;
    buffer[4] = (data & 0xFF00) >> 8;
    buffer[5] = (data & 0xFF);
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_DATE_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at setDateTime: %ls\n", hid_error(m_handle));
        return false;
    }
    return true;
}

#define FEATURE_IDFILTER_SIZE 6
bool DeviceDriver::setIDFilter(const quint32 filter)
{
    if (!m_handle) return false;

    unsigned char buffer[FEATURE_IDFILTER_SIZE];
    buffer[0] = CONFIGURATION_REPORT;
    buffer[1] = CONFIGURE_CAN_ID;
    buffer[2] = (filter & 0xFF000000) >> 24;
    buffer[3] = (filter & 0xFF0000) >> 16;
    buffer[4] = (filter & 0xFF00) >> 8;
    buffer[5] = (filter & 0xFF);
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_IDFILTER_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at setIDFilter: %ls\n", hid_error(m_handle));
        return false;
    }
    return true;
}

#define FEATURE_IDMASK_SIZE 6
bool DeviceDriver::setIDFilterMask(const quint32 mask)
{
    if (!m_handle) return false;

    unsigned char buffer[FEATURE_IDMASK_SIZE];
    buffer[0] = CONFIGURATION_REPORT;
    buffer[1] = CONFIGURE_CAN_MASK;
    buffer[2] = (mask & 0xFF000000) >> 24;
    buffer[3] = (mask & 0xFF0000) >> 16;
    buffer[4] = (mask & 0xFF00) >> 8;
    buffer[5] = (mask & 0xFF);
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_IDMASK_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at setIDFilterMask: %ls\n", hid_error(m_handle));
        return false;
    }
    return true;
}

#define FEATURE_CANTIMING_SIZE 6
bool DeviceDriver::changeCANTiming(const int timing_index)
{
    if (!m_handle) return false;

    unsigned char buffer[FEATURE_CANTIMING_SIZE];
    buffer[0] = CONFIGURATION_REPORT;
    buffer[1] = CONFIGURE_CAN_TIMING;
    buffer[2] = (unsigned char)timing_index;
    buffer[3] = 0;
    buffer[4] = 0;
    buffer[5] = 0;
    int res = hid_send_feature_report(m_handle, buffer, FEATURE_CANTIMING_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at changeCANTiming: %ls\n", hid_error(m_handle));
        return false;
    }
    return true;
}

#define IN_DATA_REPORT_SIZE 17
#define IN_ERROR_REPORT_SIZE 6
#if IN_DATA_REPORT_SIZE > IN_ERROR_REPORT_SIZE
    #define MAX_IN_REPORT_SIZE IN_DATA_REPORT_SIZE
#else
    #define MAX_IN_REPORT_SIZE IN_ERROR_REPORT_SIZE
#endif
bool DeviceDriver::readCANMessage(CAN_PacketPtr &msg)
{
    if (!m_handle) return false;

    unsigned char buffer[MAX_IN_REPORT_SIZE];
    memset(buffer, 0, MAX_IN_REPORT_SIZE);

    int res = hid_read(m_handle, buffer, MAX_IN_REPORT_SIZE);
    if (res < 0 ) {
        m_error = true;
        printf("Error at readCANMessage: %ls\n", hid_error(m_handle));
        return false;
    }
    if (res == 0) return false;
    if (buffer[0] == CAN_DATA_FRAME_REPORT)
    {
        QByteArray byteArray((char*)(buffer+1), IN_DATA_REPORT_SIZE-1);
        msg.reset(new Data_Packet(byteArray));
    }
    else if (buffer[0] == CAN_ERROR_FRAME_REPORT)
    {
        QByteArray byteArray((char*)(buffer+1), IN_ERROR_REPORT_SIZE-1);
        msg.reset(new Error_Packet(byteArray));
    }
    else return false;
    return true;
}

#define OUT_REPORT_SIZE 13
bool DeviceDriver::writeCANMessage(CAN_PacketPtr msg)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!m_handle) return false;
    qDebug() << "Handle present";

    QByteArray buffer = msg->serializeToUSB();
    buffer.prepend(CAN_DATA_FRAME_REPORT);
    int res = hid_write(m_handle, (const unsigned char *)buffer.constData(), buffer.size());
    if (res < 0 ) {
        m_error = true;
        qDebug() << QString("Error at writeCANMessage: %1\n").arg(QString::fromWCharArray(hid_error(m_handle)));
        printf("Error at writeCANMessage: %ls\n", hid_error(m_handle));
        return false;
    }
    return true;
}


void DeviceDriver::printDevice(hid_device_info *device) const
{
    if (!device) {printf("no Device found\n"); return;}

    printf("Device Found\n ");
    printf("VendorID: %04hx\n",device->vendor_id);
    printf("ProductID: %04hx\n ",device->product_id);
    printf("Path: %s\n ",device->path);
    printf("Serial_number: %ls\n", device->serial_number);
    printf("Manufacturer: %ls\n", device->manufacturer_string);
    printf("Product: %ls\n", device->product_string);
    printf("Release: %04hx\n", device->release_number);
    printf("Interface: %d\n", device->interface_number);
    printf("UsagePage: %04hx\n", device->usage_page);
    printf("Usage: %02hx\n\n", device->usage);
}
