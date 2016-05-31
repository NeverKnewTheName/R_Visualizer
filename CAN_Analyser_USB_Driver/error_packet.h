/**
 * @file	error_packet.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef ERROR_PACKET_H
#define ERROR_PACKET_H

#include "can_packet.h"
#include <QBitArray>

/** \addtogroup Group_usb_driver
 * @{
 */

/**
 * @brief The Error_Packet represents an received CAN Errorframe
 *
 */
class USB_DRIVER_EXPORT Error_Packet : public CAN_Packet
{
    public:
        /**
         * @brief Enum for the bits of m_Status_Register.
         */
        enum RegisterBits
        {
            WAKINT = 0,
            ERRINT,
            BOFFINT,
            RX,
            FLTCONF1,
            FLTCONF2,
            TX,
            IDLE,
            RXWRN,
            TXWRN,
            STFERR,
            FRMERR,
            CRCERR,
            ACKERR,
            BIT0ERR,
            BIT1ERR,
            RWRNINT,
            TWRNINT,
            SYNCH
        };
        Q_ENUMS(RegisterBits)
        /**
         * @brief Default constructor that creates a empty Error_Packet.
         *
         */
        Error_Packet();
        /**
         * @brief Constructs a Error_Packet with the arrived data by byteArray, which will be deserialized.
         *
         * @param byteArray Arrived data.
         */
        Error_Packet(const QByteArray byteArray) : CAN_Packet(byteArray) { this->deserialize(); }
        /**
         * @brief Default destructor.
         */
        virtual ~Error_Packet() {}

        /**
         * @brief Getter function for rx error counter.
         *
         * @return quint8 Returns the rx error counter.
         */
        quint8 RX_Error_Counter() const;
        /**
         * @brief Getter function for tx error counter.
         *
         * @return quint8 Returns the tx error counter.
         */
        quint8 TX_Error_Counter() const;
        /**
         * @brief Getter function for the status register data.
         *
         * @return QBitArray Returns the status register which could contain more information to the arrived Errorframe.
         */
        QBitArray Status_Register() const;
        /**
         * @brief Returns a string of the informations in the status register.
         *
         * @return QString String that describes the errorframe a bit more precise.
         */
        QString Status_Register_String() const;

        static const QByteArray s_packetHeaderByteArray; /**< Definition of the packet header of a Data_Packet */

    // CAN_Packet interface
    public:
        /**
         * Reimplemented from CAN_Packet::type() .
         * @return CAN_Packet::Type Returns CAN_Packet::Error_Frame
         */
        virtual CAN_Packet::Type type() const { return CAN_Packet::Error_Frame; }
        /**
         * Reimplemented from CAN_Packet::serializeToUSB() .
         * @return QByteArray Returns an empty QByteArray, because an errorframe cant be sended.
         */
        virtual QByteArray serializeToUSB() const { return QByteArray(); }
        /**
         * Reimplemented from CAN_Packet::serializeToFile() .
         * @return QByteArray Returns the converted data, that can be written to a file.
         */
        virtual QByteArray serializeToFile() const;
        /**
         * Reimplemented from CAN_Packet::rawBytesTillTimestamp() .
         * @return uint Returns the byte offset of the timestamp field in the raw binary data.
         */
        virtual uint rawBytesTillTimestamp() const;
        /**
         * Reimplemented from CAN_Packet::packetHeader() .
         * @return const QByteArray Returns the packet Header s_packetHeaderByteArray.
         */
        virtual const QByteArray& packetHeader() const { return s_packetHeaderByteArray; }
        /**
         * Reimplemented from CAN_Packet::printPacket() .
         */
        virtual void printPacket() const;

    protected:
        /**
         * @brief This function decodes the data of CAN_Packet::m_byteArray to the attributes of this class.
         * Reimplemented from CAN_Packet::deserialize() .
         */
        void deserialize();

    private:
        quint8 m_RX_Error_Counter; /**< Holds the RX Error Counter Value */
        quint8 m_TX_Error_Counter; /**< Holds the TX Error Counter Value */
        QBitArray m_Status_Register; /**< Holds the Status Register Value */
};

#endif // ERROR_PACKET_H

/** @} */
