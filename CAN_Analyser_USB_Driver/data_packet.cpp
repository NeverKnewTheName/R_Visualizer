#include "data_packet.h"
#include <QDebug>

#define SRR_BYTE_ARRAY_INDEX 1
#define SRR_MASK 0x40
#define SRR_SHIFT 6

#define IDE_BYTE_ARRAY_INDEX 1
#define IDE_MASK 0x20
#define IDE_SHIFT 5

#define RTR_BYTE_ARRAY_INDEX 1
#define RTR_MASK 0x10
#define RTR_SHIFT 4

#define DLC_BYTE_ARRAY_INDEX 1
#define DLC_MASK 0x0F
#define DLC_SHIFT 0

#define TIMESTAMP_BYTE_ARRAY_INDEX_1 2
#define TIMESTAMP_MASK_1 0xFF

#define TIMESTAMP_BYTE_ARRAY_INDEX_2 3
#define TIMESTAMP_MASK_2 0xFF
#define TIMESTAMP_SHIFT 0

#define ID_STD_BYTE_ARRAY_INDEX_1 4
#define ID_STD_MASK_1 0x1F

#define ID_STD_BYTE_ARRAY_INDEX_2 5
#define ID_STD_MASK_2 0xFC
#define ID_STD_SHIFT 2

#define ID_EXT_BYTE_ARRAY_INDEX_1 5
#define ID_EXT_MASK_1 0x03

#define ID_EXT_BYTE_ARRAY_INDEX_2 6
#define ID_EXT_MASK_2 0xFF

#define ID_EXT_BYTE_ARRAY_INDEX_3 7
#define ID_EXT_MASK_3 0xFF
#define ID_EXT_SHIFT 0

#define DATA_BYTE_ARRAY_INDEX 8

#define DATETIME_BYTE_ARRAY_INDEX_1 (DATA_BYTE_ARRAY_INDEX + NR_OF_DATA_BYTES)
#define DATETIME_BYTE_ARRAY_INDEX_2 (DATETIME_BYTE_ARRAY_INDEX_1 + 1)
#define DATETIME_BYTE_ARRAY_INDEX_3 (DATETIME_BYTE_ARRAY_INDEX_2 + 1)
#define DATETIME_BYTE_ARRAY_INDEX_4 (DATETIME_BYTE_ARRAY_INDEX_3 + 1)

const QByteArray Data_Packet::s_packetHeaderByteArray = "DAT_FR";

Data_Packet::Data_Packet()
{
    m_frame.SRR = 0;
    m_frame.IDE = 0;
    m_frame.RTR = 0;
    m_frame.EDL = 0;
    m_frame.BRS = 0;
    m_frame.ESI = 0;
    m_frame.DLC = 0;
    m_frame.TIME_STAMP = 0;
    m_frame.ID_Standard = 0;
    m_frame.ID_Extended = 0;
}

Data_Packet::Frame Data_Packet::frame() const
{
    return m_frame;
}

void Data_Packet::setFrame(const Frame &frame)
{
    m_frame = frame;
}

QByteArray Data_Packet::serializeToUSB() const
{
    int buffersize = DATA_BYTE_ARRAY_INDEX + NR_OF_DATA_BYTES;
    unsigned char buffer[buffersize];
    memset(buffer, 0, buffersize);

    buffer[SRR_BYTE_ARRAY_INDEX]         = (m_frame.SRR << SRR_SHIFT) & SRR_MASK;
    buffer[IDE_BYTE_ARRAY_INDEX]        |= (m_frame.IDE << IDE_SHIFT) & IDE_MASK;
    buffer[RTR_BYTE_ARRAY_INDEX]        |= (m_frame.RTR << RTR_SHIFT) & RTR_MASK;
    buffer[DLC_BYTE_ARRAY_INDEX]        |= (m_frame.DLC << DLC_SHIFT) & DLC_MASK;
    buffer[ID_STD_BYTE_ARRAY_INDEX_1]    = ((m_frame.ID_Standard << ID_STD_SHIFT) & (ID_STD_MASK_1 << 8)) >> 8;
    buffer[ID_STD_BYTE_ARRAY_INDEX_2]    = ((m_frame.ID_Standard << ID_STD_SHIFT) &  ID_STD_MASK_2);
    buffer[ID_EXT_BYTE_ARRAY_INDEX_1]   |= (m_frame.ID_Extended & (ID_EXT_MASK_1 << 16)) >> 16;
    buffer[ID_EXT_BYTE_ARRAY_INDEX_2]    = (m_frame.ID_Extended & (ID_EXT_MASK_2 << 8)) >> 8;
    buffer[ID_EXT_BYTE_ARRAY_INDEX_3]    = (m_frame.ID_Extended &  ID_EXT_MASK_3);

    for (int i = 0; i<m_frame.data.size(); ++i)
    {
        buffer[i+DATA_BYTE_ARRAY_INDEX] = m_frame.data.at(i);
    }

    QByteArray byteArray((char *)buffer, buffersize);
    return byteArray;
}

QByteArray Data_Packet::serializeToFile() const
{
    int buffersize = DATETIME_BYTE_ARRAY_INDEX_4+1;
    char buffer[buffersize];
    memset(buffer, 0, buffersize);

    buffer[SRR_BYTE_ARRAY_INDEX]         = (m_frame.SRR << SRR_SHIFT) & SRR_MASK;
    buffer[IDE_BYTE_ARRAY_INDEX]        |= (m_frame.IDE << IDE_SHIFT) & IDE_MASK;
    buffer[RTR_BYTE_ARRAY_INDEX]        |= (m_frame.RTR << RTR_SHIFT) & RTR_MASK;
    buffer[DLC_BYTE_ARRAY_INDEX]        |= (m_frame.DLC << DLC_SHIFT) & DLC_MASK;
    buffer[ID_STD_BYTE_ARRAY_INDEX_1]    = ((m_frame.ID_Standard << ID_STD_SHIFT) & (ID_STD_MASK_1 << 8)) >> 8;
    buffer[ID_STD_BYTE_ARRAY_INDEX_2]    = ((m_frame.ID_Standard << ID_STD_SHIFT) &  ID_STD_MASK_2);
    buffer[ID_EXT_BYTE_ARRAY_INDEX_1]   |= (m_frame.ID_Standard & (ID_EXT_MASK_1 << 16)) >> 16;
    buffer[ID_EXT_BYTE_ARRAY_INDEX_2]    = (m_frame.ID_Standard & (ID_EXT_MASK_2 << 8)) >> 8;
    buffer[ID_EXT_BYTE_ARRAY_INDEX_3]    = (m_frame.ID_Standard &  ID_EXT_MASK_3);

    for (int i = 0; i < m_frame.data.size(); ++i)
    {
        buffer[DATA_BYTE_ARRAY_INDEX+i] = m_frame.data.at(i);
    }

    quint32 secsSinceEpoch = (quint32)m_timestamp.toTime_t();
    buffer[DATETIME_BYTE_ARRAY_INDEX_1] = (secsSinceEpoch & 0xFF000000) >> 24;
    buffer[DATETIME_BYTE_ARRAY_INDEX_2] = (secsSinceEpoch & 0xFF0000) >> 16;
    buffer[DATETIME_BYTE_ARRAY_INDEX_3] = (secsSinceEpoch & 0xFF00) >> 8;
    buffer[DATETIME_BYTE_ARRAY_INDEX_4] = (secsSinceEpoch & 0xFF);

    QByteArray byteArray(buffer, buffersize);
    return byteArray;
}

uint Data_Packet::rawBytesTillTimestamp() const
{
    return DATETIME_BYTE_ARRAY_INDEX_1;
}

void Data_Packet::printPacket() const
{
    qDebug() << "ID: " << QString::number(this->m_frame.ID_Standard, 16).rightJustified(3, '0').toUpper().prepend("0x");
    if (this->m_frame.IDE != 0)
        qDebug() << "IDE: " << QString::number(this->m_frame.ID_Extended, 16).toUpper().prepend("0x");

    qDebug() << "DLC: " << QString::number(this->m_frame.DLC, 16).rightJustified(2, '0').toUpper().prepend("0x");

    QString str;
    QByteArray bytes = this->m_frame.data;
    for (int i = 0; i < bytes.size(); i++)
    {
        str.append(QString::number(bytes[i], 16).rightJustified(2, '0').toUpper().append(" "));
    }
    for (int i = bytes.size(); i < 8; i++)
        str.append("00 ");

    qDebug() << "DATA: " << str;
}

void Data_Packet::deserialize()
{
    m_frame.EDL = 0;
    m_frame.BRS = 0;
    m_frame.ESI = 0;
    m_frame.SRR = (m_byteArray.at(SRR_BYTE_ARRAY_INDEX) & SRR_MASK) >> SRR_SHIFT;
    m_frame.IDE = (m_byteArray.at(IDE_BYTE_ARRAY_INDEX) & IDE_MASK) >> IDE_SHIFT;
    m_frame.RTR = (m_byteArray.at(RTR_BYTE_ARRAY_INDEX) & RTR_MASK) >> RTR_SHIFT;
    m_frame.DLC = (m_byteArray.at(DLC_BYTE_ARRAY_INDEX) & DLC_MASK) >> DLC_SHIFT;

    m_frame.TIME_STAMP = (((m_byteArray.at(TIMESTAMP_BYTE_ARRAY_INDEX_1) & TIMESTAMP_MASK_1) << 8) |
                           (m_byteArray.at(TIMESTAMP_BYTE_ARRAY_INDEX_2) & TIMESTAMP_MASK_2)) >> TIMESTAMP_SHIFT;

    m_frame.ID_Standard = (((m_byteArray.at(ID_STD_BYTE_ARRAY_INDEX_1) & ID_STD_MASK_1) << 8) |
                            (m_byteArray.at(ID_STD_BYTE_ARRAY_INDEX_2) & ID_STD_MASK_2)) >> ID_STD_SHIFT;

    m_frame.ID_Extended = (((m_byteArray.at(ID_EXT_BYTE_ARRAY_INDEX_1) & ID_EXT_MASK_1) << 16) |
                           ((m_byteArray.at(ID_EXT_BYTE_ARRAY_INDEX_2) & ID_EXT_MASK_2) << 8) |
                            (m_byteArray.at(ID_EXT_BYTE_ARRAY_INDEX_3) & ID_EXT_MASK_3)) >> ID_EXT_SHIFT;


    m_frame.data = m_byteArray.mid(DATA_BYTE_ARRAY_INDEX, m_frame.DLC);
}
