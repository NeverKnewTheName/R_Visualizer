#include "error_packet.h"
#include <QDebug>

#define NR_OF_REGISTERBITS 17

#define RX_ERROR_COUNTER_BYTE_ARRAY_INDEX       0
#define RX_ERROR_COUNTER_MASK                   0xFF
#define RX_ERROR_COUNTER_SHIFT                  0

#define TX_ERROR_COUNTER_BYTE_ARRAY_INDEX       1
#define TX_ERROR_COUNTER_MASK                   0xFF
#define TX_ERROR_COUNTER_SHIFT                  0

#define WAKINT_BYTE_ARRAY_INDEX         4
#define WAKINT_MASK                     0x1
#define WAKINT_SHIFT                    0

#define ERRINT_BYTE_ARRAY_INDEX         4
#define ERRINT_MASK                     0x2
#define ERRINT_SHIFT                    1

#define BOFFINT_BYTE_ARRAY_INDEX        4
#define BOFFINT_MASK                    0x4
#define BOFFINT_SHIFT                   2

#define RX_BYTE_ARRAY_INDEX             4
#define RX_MASK                         0x8
#define RX_SHIFT                        3

#define FLTCONF_BYTE_ARRAY_INDEX        4
#define FLTCONF1_MASK                   0x10
#define FLTCONF1_SHIFT                  4
#define FLTCONF2_MASK                   0x20
#define FLTCONF2_SHIFT                  5

#define TX_BYTE_ARRAY_INDEX             4
#define TX_MASK                         0x40
#define TX_SHIFT                        6

#define IDLE_BYTE_ARRAY_INDEX           4
#define IDLE_MASK                       0x80
#define IDLE_SHIFT                      7

#define RXWRN_BYTE_ARRAY_INDEX          3
#define RXWRN_MASK                      0x1
#define RXWRN_SHIFT                     0

#define TXWRN_BYTE_ARRAY_INDEX          3
#define TXWRN_MASK                      0x2
#define TXWRN_SHIFT                     1

#define STFERR_BYTE_ARRAY_INDEX         3
#define STFERR_MASK                     0x4
#define STFERR_SHIFT                    2

#define FRMERR_BYTE_ARRAY_INDEX         3
#define FRMERR_MASK                     0x8
#define FRMERR_SHIFT                    3

#define CRCERR_BYTE_ARRAY_INDEX         3
#define CRCERR_MASK                     0x10
#define CRCERR_SHIFT                    4

#define ACKERR_BYTE_ARRAY_INDEX         3
#define ACKERR_MASK                     0x20
#define ACKERR_SHIFT                    5

#define BIT0ERR_BYTE_ARRAY_INDEX        3
#define BIT0ERR_MASK                    0x40
#define BIT0ERR_SHIFT                   6

#define BIT1ERR_BYTE_ARRAY_INDEX        3
#define BIT1ERR_MASK                    0x80
#define BIT1ERR_SHIFT                   7

#define RWRNINT_BYTE_ARRAY_INDEX        2
#define RWRNINT_MASK                    0x1
#define RWRNINT_SHIFT                   0

#define TWRNINT_BYTE_ARRAY_INDEX        2
#define TWRNINT_MASK                    0x2
#define TWRNINT_SHIFT                   1

#define SYNCH_BYTE_ARRAY_INDEX          2
#define SYNCH_MASK                      0x4
#define SYNCH_SHIFT                     3

#define DATETIME_BYTE_ARRAY_INDEX_1 (5)
#define DATETIME_BYTE_ARRAY_INDEX_2 (DATETIME_BYTE_ARRAY_INDEX_1 + 1)
#define DATETIME_BYTE_ARRAY_INDEX_3 (DATETIME_BYTE_ARRAY_INDEX_2 + 1)
#define DATETIME_BYTE_ARRAY_INDEX_4 (DATETIME_BYTE_ARRAY_INDEX_3 + 1)

const QByteArray Error_Packet::s_packetHeaderByteArray = "ERR_FR";

Error_Packet::Error_Packet()
{
    m_RX_Error_Counter = 0;
    m_TX_Error_Counter = 0;
    m_Status_Register.resize(NR_OF_REGISTERBITS);
}

quint8 Error_Packet::RX_Error_Counter() const
{
    return m_RX_Error_Counter;
}

quint8 Error_Packet::TX_Error_Counter() const
{
    return m_TX_Error_Counter;
}

QBitArray Error_Packet::Status_Register() const
{
    return m_Status_Register;
}

QString Error_Packet::Status_Register_String() const
{
    if (!m_Status_Register.testBit(SYNCH) &&
        !m_Status_Register.testBit(IDLE) &&
        !m_Status_Register.testBit(TX) &&
        !m_Status_Register.testBit(RX))
    {
        return QString("Not Synchronized to CAN bus");
    }

    QString status;
    if (m_Status_Register.testBit(FLTCONF2))
    {
        status.prepend("Bus Off");
    }
    else if (m_Status_Register.testBit(FLTCONF1))
    {
        status.prepend("Error Passive");
    }
    else
    {
        status.prepend("Error Active");
    }

    QString details;
    for(int i = 0; i < m_Status_Register.size(); i++)
    {
        if (!m_Status_Register.testBit(i)) continue;
        switch(i)
        {
            case STFERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("Stuffing Error");
                break;
            case FRMERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("Form Error");
                break;
            case CRCERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("CRC Error");
                break;
            case ACKERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("Ack Error");
                break;
            case BIT0ERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("Bit0 Error");
                break;
            case BIT1ERR :
                if (!details.isEmpty()) details.append(", ");
                details.append("Bit1 Error");
                break;
            default:
                break;
        }
    }

    return (details.isEmpty()) ? status : status.append(": ").append(details);
}

QByteArray Error_Packet::serializeToFile() const
{
    int buffersize = DATETIME_BYTE_ARRAY_INDEX_4+1;
    char buffer[buffersize];
    memset(buffer, 0, buffersize);

    buffer[RX_ERROR_COUNTER_BYTE_ARRAY_INDEX] = m_RX_Error_Counter & RX_ERROR_COUNTER_MASK;
    buffer[TX_ERROR_COUNTER_BYTE_ARRAY_INDEX] = m_TX_Error_Counter & TX_ERROR_COUNTER_MASK;

    buffer[WAKINT_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(WAKINT) << WAKINT_SHIFT);
    buffer[ERRINT_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(ERRINT) << ERRINT_SHIFT);
    buffer[BOFFINT_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(BOFFINT) << BOFFINT_SHIFT);
    buffer[RX_BYTE_ARRAY_INDEX]         |= (m_Status_Register.at(RX) << RX_SHIFT);
    buffer[FLTCONF_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(FLTCONF1) << FLTCONF1_SHIFT);
    buffer[FLTCONF_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(FLTCONF2) << FLTCONF2_SHIFT);
    buffer[TX_BYTE_ARRAY_INDEX]         |= (m_Status_Register.at(TX) << TX_SHIFT);
    buffer[IDLE_BYTE_ARRAY_INDEX]       |= (m_Status_Register.at(IDLE) << IDLE_SHIFT);

    buffer[RXWRN_BYTE_ARRAY_INDEX]      |= (m_Status_Register.at(RXWRN) << RXWRN_SHIFT);
    buffer[TXWRN_BYTE_ARRAY_INDEX]      |= (m_Status_Register.at(TXWRN) << TXWRN_SHIFT);
    buffer[STFERR_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(STFERR) << STFERR_SHIFT);
    buffer[FRMERR_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(FRMERR) << FRMERR_SHIFT);
    buffer[CRCERR_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(CRCERR) << CRCERR_SHIFT);
    buffer[ACKERR_BYTE_ARRAY_INDEX]     |= (m_Status_Register.at(ACKERR) << ACKERR_SHIFT);
    buffer[BIT0ERR_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(BIT0ERR) << BIT0ERR_SHIFT);
    buffer[BIT1ERR_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(BIT1ERR) << BIT1ERR_SHIFT);

    buffer[RWRNINT_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(RWRNINT) << RWRNINT_SHIFT);
    buffer[TWRNINT_BYTE_ARRAY_INDEX]    |= (m_Status_Register.at(TWRNINT) << TWRNINT_SHIFT);
    buffer[SYNCH_BYTE_ARRAY_INDEX]      |= (m_Status_Register.at(SYNCH) << SYNCH_SHIFT);

    quint32 secsSinceEpoch = (quint32)m_timestamp.toTime_t();
    buffer[DATETIME_BYTE_ARRAY_INDEX_1] = (secsSinceEpoch & 0xFF000000) >> 24;
    buffer[DATETIME_BYTE_ARRAY_INDEX_2] = (secsSinceEpoch & 0xFF0000) >> 16;
    buffer[DATETIME_BYTE_ARRAY_INDEX_3] = (secsSinceEpoch & 0xFF00) >> 8;
    buffer[DATETIME_BYTE_ARRAY_INDEX_4] = (secsSinceEpoch & 0xFF);

    QByteArray byteArray(buffer, buffersize);
    return byteArray;
}

uint Error_Packet::rawBytesTillTimestamp() const
{
    return DATETIME_BYTE_ARRAY_INDEX_1;
}

void Error_Packet::printPacket() const
{
    qDebug() << "RX_Error_Counter: : " << m_RX_Error_Counter;
    qDebug() << "TX_Error_Counter: : " << m_TX_Error_Counter;
    qDebug() << "WAKINT: " << m_Status_Register.at(WAKINT);
    qDebug() << "ERRINT: " << m_Status_Register.at(ERRINT);
    qDebug() << "BOFFINT: " << m_Status_Register.at(BOFFINT);
    qDebug() << "RX: " << m_Status_Register.at(RX);
    qDebug() << "FLTCONF1: " << m_Status_Register.at(FLTCONF1);
    qDebug() << "FLTCONF2: " << m_Status_Register.at(FLTCONF2);
    qDebug() << "TX: " << m_Status_Register.at(TX);
    qDebug() << "IDLE: " << m_Status_Register.at(IDLE);
    qDebug() << "RXWRN: " << m_Status_Register.at(RXWRN);
    qDebug() << "TXWRN: " << m_Status_Register.at(TXWRN);
    qDebug() << "STFERR: " << m_Status_Register.at(STFERR);
    qDebug() << "FRMERR: " << m_Status_Register.at(FRMERR);
    qDebug() << "CRCERR: " << m_Status_Register.at(CRCERR);
    qDebug() << "ACKERR: " << m_Status_Register.at(ACKERR);
    qDebug() << "BIT0ERR: " << m_Status_Register.at(BIT0ERR);
    qDebug() << "BIT1ERR: " << m_Status_Register.at(BIT1ERR);
    qDebug() << "RWRNINT: " << m_Status_Register.at(RWRNINT);
    qDebug() << "TWRNINT: " << m_Status_Register.at(TWRNINT);
    qDebug() << "SYNCH: " << m_Status_Register.at(SYNCH);
}

void Error_Packet::deserialize()
{
    m_RX_Error_Counter = 0;
    m_TX_Error_Counter = 0;
    m_Status_Register.clear();
    m_Status_Register.resize(NR_OF_REGISTERBITS);

    m_RX_Error_Counter = (m_byteArray.at(RX_ERROR_COUNTER_BYTE_ARRAY_INDEX) & RX_ERROR_COUNTER_MASK) >> RX_ERROR_COUNTER_SHIFT;
    m_TX_Error_Counter = (m_byteArray.at(TX_ERROR_COUNTER_BYTE_ARRAY_INDEX) & TX_ERROR_COUNTER_MASK) >> TX_ERROR_COUNTER_SHIFT;

    m_Status_Register.setBit(WAKINT, m_byteArray.at(WAKINT_BYTE_ARRAY_INDEX) & WAKINT_MASK);
    m_Status_Register.setBit(ERRINT, m_byteArray.at(ERRINT_BYTE_ARRAY_INDEX) & ERRINT_MASK);
    m_Status_Register.setBit(BOFFINT, m_byteArray.at(BOFFINT_BYTE_ARRAY_INDEX) & BOFFINT_MASK);
    m_Status_Register.setBit(RX, m_byteArray.at(RX_BYTE_ARRAY_INDEX) & RX_MASK);
    m_Status_Register.setBit(FLTCONF1, m_byteArray.at(FLTCONF_BYTE_ARRAY_INDEX) & FLTCONF1_MASK);
    m_Status_Register.setBit(FLTCONF2, m_byteArray.at(FLTCONF_BYTE_ARRAY_INDEX) & FLTCONF2_MASK);
    m_Status_Register.setBit(TX, m_byteArray.at(TX_BYTE_ARRAY_INDEX) & TX_MASK);
    m_Status_Register.setBit(IDLE, m_byteArray.at(IDLE_BYTE_ARRAY_INDEX) & IDLE_MASK);
    m_Status_Register.setBit(RXWRN, m_byteArray.at(RXWRN_BYTE_ARRAY_INDEX) & RXWRN_MASK);
    m_Status_Register.setBit(TXWRN, m_byteArray.at(TXWRN_BYTE_ARRAY_INDEX) & TXWRN_MASK);
    m_Status_Register.setBit(STFERR, m_byteArray.at(STFERR_BYTE_ARRAY_INDEX) & STFERR_MASK);
    m_Status_Register.setBit(FRMERR, m_byteArray.at(FRMERR_BYTE_ARRAY_INDEX) & FRMERR_MASK);
    m_Status_Register.setBit(CRCERR, m_byteArray.at(CRCERR_BYTE_ARRAY_INDEX) & CRCERR_MASK);
    m_Status_Register.setBit(ACKERR, m_byteArray.at(ACKERR_BYTE_ARRAY_INDEX) & ACKERR_MASK);
    m_Status_Register.setBit(BIT0ERR, m_byteArray.at(BIT0ERR_BYTE_ARRAY_INDEX) & BIT0ERR_MASK);
    m_Status_Register.setBit(BIT1ERR, m_byteArray.at(BIT1ERR_BYTE_ARRAY_INDEX) & BIT1ERR_MASK);
    m_Status_Register.setBit(RWRNINT, m_byteArray.at(RWRNINT_BYTE_ARRAY_INDEX) & RWRNINT_MASK);
    m_Status_Register.setBit(TWRNINT, m_byteArray.at(TWRNINT_BYTE_ARRAY_INDEX) & TWRNINT_MASK);
    m_Status_Register.setBit(SYNCH, m_byteArray.at(SYNCH_BYTE_ARRAY_INDEX) & SYNCH_MASK);
}
