#include "can_packet.h"
#include <QDebug>

CAN_Packet::CAN_Packet(QByteArray byteArray)
{
    m_byteArray = byteArray;
    setTimestamp(QDateTime::currentDateTime());
}

QDateTime CAN_Packet::timestamp() const
{
    return m_timestamp;
}

void CAN_Packet::setTimestamp(const QDateTime &timestamp)
{
    m_timestamp = timestamp;
}

QByteArray CAN_Packet::byteArray() const
{
    return m_byteArray;
}

void CAN_Packet::setByteArray(const QByteArray& byteArray)
{
    m_byteArray = byteArray;
    deserialize();
}

QDataStream& operator<< (QDataStream &stream, const CAN_PacketPtr &packet)
{
    const QByteArray header = packet->packetHeader();
    stream.writeRawData(header.data(), header.size());

    QByteArray buffer = packet->serializeToFile();
    stream.writeRawData(buffer.data(), buffer.size());
    return stream;
}

QDataStream& operator>> (QDataStream &stream, CAN_PacketPtr &packet)
{
    QByteArray header(Data_Packet::s_packetHeaderByteArray.size(), '\0');
    stream.readRawData(header.data(), Data_Packet::s_packetHeaderByteArray.size());
    if (header == Data_Packet::s_packetHeaderByteArray)
    {
        packet.reset(new Data_Packet());
    }
    else if (header == Error_Packet::s_packetHeaderByteArray)
    {
        packet.reset(new Error_Packet());
    }
    else
    {
        return stream;
    }

    QByteArray buffer(packet->rawBytesTillTimestamp(), '\0');
    stream.readRawData(buffer.data(), packet->rawBytesTillTimestamp());
    packet->setByteArray(buffer);

    quint32 secsSinceEpoch = 0;
    stream >> secsSinceEpoch;
    packet->setTimestamp(QDateTime::fromTime_t(secsSinceEpoch));
    return stream;
}
