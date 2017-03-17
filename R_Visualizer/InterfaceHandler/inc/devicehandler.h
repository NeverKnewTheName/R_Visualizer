/**
 * @file	devicehandler.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <devicedriver.h>

#include "msg.h"
#include "errorlogentry.h"

/** \addtogroup Group_BasicApplication
 *  @{
 */

/**
 * @brief is manages the interaction with the usb-driver library.
 * The class inherits QThread to facilitate advanced thread management.
 */
class DeviceHandler : public QThread
{
    Q_OBJECT

    public:
        /**
         * @brief Creates a DeviceHandler object.
         */
        DeviceHandler();
        /**
         * @brief Destroyes a DeviceHandler object.
         * This function waits till the created thread is finished execution and
         * ends all the communication with the connected device.
         */
        ~DeviceHandler();
        /**
         * @brief Returns a list all the connected CAN-Analyser Embedded-Systems.
         *
         * @return HID_DevicesList is a list of HID_Device objects.
         */
        HID_DevicesList devices() const { return m_devices; }
        /**
         * @brief Tries to create a connection to the HID_Device that is given by device.
         *
         * @param device to connect to.
         * @return bool; returns true if the connection is established, else false.
         */
        bool connectTo(HID_Device &device);
        /**
         * @brief Disconnect a connected device.
         */
        void disconnect();

    // QThread interface
    protected:
        /**
         * @brief The starting point for the thread.
         * Reimplemented from QThread to facilitate advanced thread management.
         * After calling start(), the newly created thread calls this function. Returning from this method will end the execution of the thread.
         * The thread checks if new CAN_Packet objects were received and emits the signal \ref sigPacketReceived to give the objects to further.
         */
        void run() Q_DECL_OVERRIDE;

    signals:
        /**
         * @brief Signal that notifies the application that a new CAN_Packet was received.
         *
         * @param CAN_PacketPtr Pointer that holds the new CAN_Packet.
         */
        void sigPacketReceived(CAN_PacketPtr);

        void sigMsgReceived(const Msg &msg);
        void sigErrorMsgReceived(ErrorLogEntry *errEntry);
        /**
         * @brief Signal that notifies the application of an error in the usb communication.
         *
         * @param QString that describes the error.
         */
        void sigError(QString);

    public slots:
        /**
         * @brief Slot that checks periodicly if new HID_Device are connected and tries to enummerate them.
         */
        void sltScan();
        /**
         * @brief Slot tells the device to start caputring CAN Data.
         * The function asks for the device state and if its ready it will send a command to start capturing CAN Data.
         * The function starts the thread and the function \ref run is processed.
         */
        void sltStartCapture();
        /**
         * @brief Slot tells the device to stop caputring CAN Data.
         * The function also stops the thead, polling for new data.
         */
        void sltStopCapture();
        /**
         * @brief Slot to send a CAN_Packet object to the Embedded-System, to transfer it by the CAN bus.
         *
         * @param packet that will be transfered.
         */
        void sltSendPacket(CAN_PacketPtr packet);
        void sltSendMsg(const Msg &msgToSend);
        /**
         * @brief Transfers a new filter ID to the Embedded-System
         *
         * @param filterID
         */
        void sltSetFilterID(const quint32 filterID);
        /**
         * @brief Transfers a new filter mask to the Embedded-System
         *
         * @param filterMask
         */
        void sltSetFilterMask(const quint32 filterMask);
        /**
         * @brief This slot changes the CAN timing of the Embedded-System.
         *
         * @param index of the implemented timing table in the device.
         */
        void sltChangeCANTiming(const int index);
        /**
         * @brief Function for debug purpose.
         */
        void SLT_DEV_CREATE_PACKET();

    private:
        QTimer m_timer; /**< Timer for periodicly scanning for new connected devices. */
        DeviceDriver m_driver; /**< Driver object */
        QMutex m_mutex; /**< Mutex to establish threadsavety of the usb driver library */
        bool m_stop; /**< Flag to stop the thread. */
        bool m_connected; /**< Flag that spezifies if a connection to a device was established or not. */
        HID_DevicesList m_devices; /**< List of all avialable connected Embedded-Systems. */
};

#endif // DEVICEHANDLER_H

/** @} */
