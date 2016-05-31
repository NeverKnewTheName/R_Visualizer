/**
 * @file	devicedriver.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include <hidapi.h>
#include "usb_driver_global.h"
#include "can_packet.h"
#include <QList>

/** \defgroup Group_usb_driver USB-Driver Library
 *
 *  \brief Library that manages the usb communication with the CAN-Analyser Embedded System
 *
 *  This library provides classes and functions that manages the communication with the CAN-Analyser Embedded System
 *  and provides classes that can hold the transfered data.
 *  For the usb communication the library uses an external library called HID API.
 *  This library allows an application to interface with USB and Bluetooth HID-Class devices on Windows, Linux, and Mac OS X.
 *  HIDAPI provides a clean and consistent interface for each platform, making it easier to develop applications which communicate
 *  with USB HID devices without having to know the details of the HID libraries and interfaces on each platform.
 *
 *  For further informations about HID API please refere to http://www.signal11.us/oss/hidapi/ .
 *  A documentation for the library can be found here: http://www.signal11.us/oss/hidapi/hidapi/doxygen/html/group__API.html
 */

/**
 * @ingroup Group_usb_driver
 * @brief Structur which holds informations to a available HID Device
 */
struct USB_DRIVER_EXPORT HID_Device
{
    QString path; /**< Path of the USB Device in the operation system */
    quint16 vendorID; /**< Vendor ID of the USB Device */
    quint16 productID; /**< Product ID of the USB Device */
    QString serialNumber; /**< Serialnumber out of the Serialnumber String Descriptor */
    quint16 releaseNumber; /**< Releasenumber of the USB Device */
    QString manufacturer; /**< Manufacturer string out of the String Descriptors */
    QString product; /**< Product string out of the String Descriptors */
    int interface_number; /**< current interface number of the Device */
};

/**
 * @ingroup Group_usb_driver
 * @brief Typedefine for a QList of HID_Device objects.
 */
typedef QList<HID_Device> HID_DevicesList;

/**
 * @ingroup Group_usb_driver
 * @brief The DeviceDriver performs the low-level usb functions to comunicate with the CAN-Analyser Embedded System.
 */
class USB_DRIVER_EXPORT DeviceDriver
{
    public:
        /**
         * @brief Enum of the States from the statemachine of the Embedded System.
         */
        enum DeviceStates
        {
            STATE_Init              = 0,
            STATE_Standby			= 1,
            STATE_USBCaptureInit	= 2,
            STATE_CaptureViaUSB     = 3,
            STATE_FileCaptureInit	= 4,
            STATE_CaptureViaFile	= 5,
            STATE_Configure         = 6,
            STATE_Error             = 7,
        };
        /**
         * @brief Constructs a DeviceDriver object.
         */
        DeviceDriver();
        /**
         * @brief Destroys the DeviceDriver.
         */
        ~DeviceDriver();

        /**
         * @brief Trys to enumerate the CAN-Analyser Embedded Systems with the specific Vendor and Product ID.
         *
         * @return bool returns true if the enumeration was successfull and at least one device is connected, else false.
         */
        bool enumerate();
        /**
         * @brief Returns a list of all enumerated CAN-Analyser Embedded Systems.
         *
         * @return HID_DevicesList Returns a list of all enumerated CAN-Analyser Embedded Systems.
         */
        HID_DevicesList getDevices() const { return m_devices; }
        /**
         * @brief Returns true if an error occured.
         *
         * @return bool Returns true if an error occured, else false.
         */
        bool error() const { return m_error; }
        /**
         * @brief Returns a string that describes the recent error that occured and removes the error flag.
         *
         * @return QString Returns a string that describes the recent error.
         */
        QString getErrorString();

        /**
         * @brief This function claims the given device an creates a connection to it.
         *
         * @param device The device informations to connect to.
         * @return bool Returns true if a connection was successfull, else false (e.g. if a other application uses the device already)
         */
        bool connectToDevice(HID_Device& device);
        /**
         * @brief Disconnet the last claimed device and clears all pending transfers to it.
         *
         * @return bool Returns true if successfull, else false.
         */
        bool disconnectDevice();

        /**
         * @brief Sends a command to the connected device to start the capuring of CAN Messages.
         *
         * @return bool Returns true if successfull, else false.
         */
        bool sendStartCommand();
        /**
         * @brief Sends a command to the connected device to stop the capuring of CAN Messages.
         *
         * @return bool Returns true if successfull, else false.
         */
        bool sendStopCommand();
        /**
         * @brief Asks the connected device of the current state of his statemachine.
         *
         * @return DeviceStates The current state of the device statemachine.
         */
        DeviceStates getCurrentDeviceState();

        /**
         * @brief Transfers the given time to the connected device to update his Real Time Clock Module.
         *
         * @param time Date and Time to transfer.
         * @return bool  Returns true if successfull, else false.
         */
        bool setDateTime(const QDateTime &time);
        /**
         * @brief Transfers the given filter value to the connected device to set a new FilterId for the CAN Messages.
         *
         * @param filter Filter value to transfer
         * @return bool Returns true if successfull, else false.
         */
        bool setIDFilter(const quint32 filter);
        /**
         * @brief Transfers the given mask value to the connected device to set a new filter mask for the CAN Messages.
         *
         * @param mask Mask value to transfer
         * @return bool Returns true if successfull, else false.
         */
        bool setIDFilterMask(const quint32 mask);
        /**
         * @brief Transfers the given timing_index to the connected device to chose a new can timing from the impelemtet timing list.
         *
         * @param timing_index Index which represents the list index of the implemented timing list.
         * @return bool Returns true if successfull, else false.
         */
        bool changeCANTiming(const int timing_index);

        /**
         * @brief This function trys to receive a new CAN_PacketPtr.
         * The recieved packet can be ether a Data_PacketPtr or a Error_PacketPtr.
         * @param msg Parameter which should be a empty CAN_PacketPtr and after a successful read it contains the new CAN_Packet object.
         * @return bool Returns true if successfull, else false.
         */
        bool readCANMessage(CAN_PacketPtr &msg);
        /**
         * @brief This function transfers the given CAN_PacketPtr to the connected device to send it over the CAN bus.
         *
         * @param msg Message to transfer to.
         * @return bool Returns true if successfull, else false.
         */
        bool writeCANMessage(CAN_PacketPtr msg);

    private:
        /**
         * @brief Enum of the HID Report IDs
         */
        enum ReportId
        {
            CAN_DATA_FRAME_REPORT	= 1,
            CAN_ERROR_FRAME_REPORT	= 2,
            CONFIGURATION_REPORT	= 3,
            DEVICE_STATE_REPORT		= 4,
        };
        /**
         * @brief Enum for the command values
         */
        enum Command
        {
            NONE 					= 0x80,
            CONFIGURE_CLOCK			= 0x81,
            CONFIGURE_CAN_ID		= 0x82,
            CONFIGURE_CAN_MASK		= 0x84,
            CONFIGURE_CAN_TIMING    = 0x85,
        };

        hid_device* m_handle; /**< Handle the claimed device */
        HID_DevicesList m_devices; /**< Holds informations to all enumerated CAN-Analyser Embedded Systems */
        bool m_error; /**< Error Flag */

        /**
         * @brief Private function for debug purpose to print a enumerated device.
         *
         * @param device Device to print.
         */
        void printDevice(hid_device_info *device) const;
};

#endif // DEVICEDRIVER_H
/** @} */
