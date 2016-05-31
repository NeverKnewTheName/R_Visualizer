/**
 * @file	data_packet.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef DATA_PACKET_H
#define DATA_PACKET_H

#include "can_packet.h"

/** \addtogroup Group_usb_driver
 * @{
 */

/**
 * @brief The Data_Packet represents an received CAN Dataframe.
 *
 */
class USB_DRIVER_EXPORT Data_Packet : public CAN_Packet
{
    public:
        /**
         * @brief Structure which holds the decoded data.
         */
        struct Frame{
            quint8 SRR; /**< Substitute Remote Request Field*/
            quint8 IDE; /**< Extended Identifier Field */
            quint8 RTR; /**< Remote Transition Request Field */
            quint8 DLC; /**< Data Length Code Field */
            quint8 EDL; /**< Extended Date Lenght Field */
            quint8 BRS; /**< Bit Rate Switch Field */
            quint8 ESI; /**< Error State Indicator Field */
            quint16 TIME_STAMP; /**< Time Stame */
            quint16 ID_Standard; /**< Standard Identifier Field */
            quint32 ID_Extended; /**< Extended Identifier Field */
            QByteArray data; /**< Transferd data as a QByteArray */
        };
        /**
         * @brief Default constructor, creates a empty Data_Packet
         *
         */
        Data_Packet();
        /**
         * @brief Constructs a Data_Packet with the arrived data by byteArray, which will be deserialized.
         *
         * @param byteArray Arrived data.
         */
        Data_Packet(const QByteArray byteArray) : CAN_Packet(byteArray) { this->deserialize(); }
        /**
         * @brief Default destructor.
         */
        virtual ~Data_Packet() {}

        /**
         * @brief Getter function for the frame data.
         *
         * @return Frame Data of the CAN Dataframe.
         */
        Frame frame() const;
        /**
         * @brief Setter function for the data.
         * This function to spezify a Data_Packet that will be send by USB.
         * @param frame New frame data.
         */
        void setFrame(const Frame &frame);

        static const QByteArray s_packetHeaderByteArray; /**< Definition of the packet header of a Data_Packet */

    // CAN_Packet interface
    public:
        /**
         * Reimplemented from CAN_Packet::type() .
         * @return CAN_Packet::Type Returns CAN_Packet::Data_Frame
         */
        virtual CAN_Packet::Type type() const { return CAN_Packet::Data_Frame; }
        /**
         * Reimplemented from CAN_Packet::serializeToUSB() .
         * @return QByteArray Returns the converted data, that can be send by the USB interface.
         */
        virtual QByteArray serializeToUSB() const;
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
         * @brief This function decodes the data of CAN_Packet::m_byteArray to m_frame .
         * Reimplemented from CAN_Packet::deserialize() .
         */
        void deserialize();

    private:
        friend class CAN_Packet;
        Frame m_frame; /**< Converted data of the CAN dataframe */
};

#endif // DATA_PACKET_H

/** @} */
