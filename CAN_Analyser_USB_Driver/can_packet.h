/**
 * @file	can_packet.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef CAN_PACKET_H
#define CAN_PACKET_H

#include <QSharedPointer>
#include <QByteArray>
#include <QDateTime>
#include <QDataStream>
#include "usb_driver_global.h"

#ifndef CAN_FD
#define NR_OF_DATA_BYTES 8
#else
#define NR_OF_DATA_BYTES 64
#endif

class CAN_Packet;
class Data_Packet;
class Error_Packet;

/** \addtogroup Group_usb_driver
 * @{
 */

/**
 * @brief Typedefine for a QSharedPointer to a CAN_Packet
 */
typedef QSharedPointer<CAN_Packet> CAN_PacketPtr;
/**
 * @brief Typedefine for a QSharedPointer to a Data_Packet
 */
typedef QSharedPointer<Data_Packet> Data_PacketPtr;
/**
 * @brief Typedefine for a QSharedPointer to a Error_Packet
 */
typedef QSharedPointer<Error_Packet> Error_PacketPtr;

Q_DECLARE_METATYPE(CAN_PacketPtr)
Q_DECLARE_METATYPE(Data_PacketPtr)
Q_DECLARE_METATYPE(Error_PacketPtr)

/**
 * @brief Interface Class for the CAN Packets.
 * This class defines functions which must implement all CAN Packets that are received
 * by the USB interface.
 */
class USB_DRIVER_EXPORT CAN_Packet
{
    public:
        /**
         * @brief Enum for the two Typs which inherits this interface.
         */
        enum Type {
            Data_Frame,
            Error_Frame
        };
        Q_ENUMS(Type)

        /**
         * @brief Default constructor for a CAN_Packet.
         * This constructor does nothing.
         * @note This constructor can only be called from a constructor of a class which implements this
         * interface.
         */
        CAN_Packet() {}
        /**
         * @brief Constructor for a CAN_Packet.
         *
         * @param byteArray The data for this CAN_Packet Type.
         *
         * This constructor sets the current system time as timestamp and the given byteArray as data.
         *
         * @note This constructor can only be called from a constructor of a class which implements this
         * interface.
         */
        CAN_Packet(QByteArray byteArray);
        /**
         * @brief Default destructor.
         */
        virtual ~CAN_Packet() {}
        /**
         * @brief Abstract function which must be implemented by child classes, to define the type of the class.
         *
         * @return CAN_Packet::Type represents the Type of
         */
        virtual CAN_Packet::Type type() const = 0;
        /**
         * @brief Abstract function that should prepare the data of this CAN_Packet to send it over USB.
         * This function must convert the data into a QByteArray in the datastructure which is required by the USB interface.
         * @return QByteArray ByteArray of the converted data, which can be send by usb.
         */
        virtual QByteArray serializeToUSB() const = 0;
        /**
         * @brief Abstract function that should prepare the data of this CAN_Packet to write it to a file.
         * This function must convert the data into a QByteArray in a datastructure which can be written to a file.
         * @return QByteArray ByteArray of the converted data, which can be writen to a file.
         */
        virtual QByteArray serializeToFile() const = 0;
        /**
         * @brief Abstract function that should return the bytes of the timestamp field in the raw binary data.
         *
         * @return uint timestamp offset
         */
        virtual uint rawBytesTillTimestamp() const = 0;
        /**
         * @brief Abstract function that should return the packet header for the implemented CAN_Packet type.
         *
         * @return const QByteArray Packet header as a QByteArray.
         */
        virtual const QByteArray& packetHeader() const = 0;
        /**
         * @brief Abstract function to print the CAN_Packet type to the debug channel.
         */
        virtual void printPacket() const = 0;

        /**
         * @brief Getter function for the timestamp of the CAN_Packet type.
         *
         * @return QDateTime Returns the timestamp when the packet arrived.
         */
        QDateTime timestamp() const;
        /**
         * @brief Sets a new timestamp for the CAN_Packet.
         *
         * @param timestamp Value of the new timestamp
         */
        void setTimestamp(const QDateTime &timestamp);

        /**
         * @brief Getter function for the received raw binary of this object.
         *
         * @return QByteArray
         */
        QByteArray byteArray() const;
        /**
         * @brief
         *
         * @param byteArray
         */
        void setByteArray(const QByteArray &byteArray);

    protected:
        /**
         * @brief Abstract function that should decode the received raw binary data into the data of
         * the class which implements this interface.
         */
        virtual void deserialize() = 0;
        QDateTime m_timestamp; /**< Holds the date and time when this packet was received. */
        QByteArray m_byteArray; /**< Holds the received raw binary data of this packet. */
};

/**
 * @brief Writes a CAN_Packet object to the stream.
 * This is an overloaded function.
 * @param stream Stream object where the CAN_Packet is written to.
 * @param CAN_PacketPtr Pointer to the CAN_Packet which will be written.
 * @return QDataStream& Returns the stream object.
 */
USB_DRIVER_EXPORT QDataStream& operator<< (QDataStream &, const CAN_PacketPtr &);
/**
 * @brief Reads a CAN_Packet object out of a QDataStream.
 * This is an overloaded function.
 * @param QDataStream where the CAN_Packet is read from.
 * @param CAN_PacketPtr which is written by the stream.
 * @return QDataStream& Returns the stream object.
 */
USB_DRIVER_EXPORT QDataStream& operator>> (QDataStream &, CAN_PacketPtr &);

#include "data_packet.h"
#include "error_packet.h"

#endif // CAN_PACKET_H

/** @} */
