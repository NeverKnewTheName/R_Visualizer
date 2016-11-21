#include "msg.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>

/**
 * @brief Initializes an empty Msg with invalid ID and Code as well as empty Data
 */
Msg::Msg() :
    MsgTimestamp(QDateTime()),
    MsgID(0x0u),
    MsgCode(0x0u),
    MsgData({
            DataByteVect(),
            0u
            })
{
}

Msg::Msg(const Msg &other) :
    MsgTimestamp(other.getTimestamp()),
    MsgID(other.getId()),
    MsgCode(other.getCode()),
    MsgData(other.getMsgData())
{
}

/**
 * @brief Initializes a Msg with the given paramters
 *
 * @param[in] timestamp Timestamp of message receival
 * @param[in] id        ID of the message sender
 * @param[in] code      Code that identifies the purpose of the message
 * @param[in] dataBytes Data bytes that were sent alongside the message
 */
Msg::Msg(QDateTime timestamp, quint16 id, quint16 code, DataByteVect dataBytes) :
    MsgTimestamp(timestamp),
    MsgID(id),
    MsgCode(code),
    MsgData({
            dataBytes,
            dataBytes.size()
            })
{
}

Msg::~Msg()
{
}

QDateTime Msg::getTimestamp() const
{
    return MsgTimestamp;
}

void Msg::setTimestamp(const QDateTime value)
{
    MsgTimestamp = value;
}

quint16 Msg::getId() const
{
    return MsgID;
}

void Msg::setId(const quint16 value)
{
    MsgID = value;
}

quint16 Msg::getCode() const
{
    return MsgCode;
}

void Msg::setCode(const quint16 value)
{
    MsgCode = value;
}

PMsgDataStruc Msg::getData()
{
    return &MsgData;
}

QString Msg::getDataAsString() const
{
    QString DataAsString("");

    for(unsigned int i = 0; i < MsgData.DataSizeInBytes; i++)
    {
        DataAsString.append(QString("0x%1 ")
                            .arg(MsgData.DataBytes.at(i)/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/));
    }
    return DataAsString.trimmed();
}

void Msg::parseIN(QJsonObject jsonMsg)
{
    MsgTimestamp = QDateTime::fromString(jsonMsg["MsgTimestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    MsgID = static_cast<quint16>(jsonMsg["MsgID"].toInt());
    MsgCode = static_cast<quint16>(jsonMsg["MsgCode"].toInt());
    QJsonArray jsonData = jsonMsg["MsgData"].toArray();
    MsgData.DataSizeInBytes = jsonData.size();
    for(unsigned int i = 0; i < MsgData.DataSizeInBytes; i++)
    {
        MsgData.DataBytes.append(static_cast<quint8>(jsonData.at(i).toInt()));
    }
}

QJsonObject Msg::parseOUT() const
{
    QJsonObject jsonMsg;
    QJsonArray  jsonData;

    jsonMsg["MsgTimestamp"] = MsgTimestamp.toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    jsonMsg["MsgID"] = QJsonValue(static_cast<int>(MsgID));
    jsonMsg["MsgCode"] = QJsonValue(static_cast<int>(MsgCode));
    for(unsigned int i = 0; i < MsgData.DataSizeInBytes; i++)
    {
        jsonData.append(QJsonValue(static_cast<int>(MsgData.DataBytes.at(i))));
    }
    jsonMsg["MsgData"] = jsonData;

    return jsonMsg;
}

MsgDataStruc Msg::getMsgData() const
{
    return MsgData;
}

/**
 * @brief Returns the Msg's MsgData as a QByteArray
 * @return MsgData as QByteArray
 */
QByteArray Msg::getDataAsByteArray() const
{
    QByteArray data;
    for(unsigned int i = 0; i < MsgData.DataSizeInBytes; i++)
    {
        data.append(MsgData.DataBytes.at(i));
    }

    return data;
}

void Msg::setData(const DataByteVect dataBytes)
{
    MsgData.DataBytes = dataBytes;
    MsgData.DataSizeInBytes = dataBytes.size();
}

void Msg::setDataByte(quint8 index, quint8 dataByte)
{
    if(index > MsgData.DataSizeInBytes)
    {
        qDebug() << __FUNCTION__ << "Index not in range of MsgData";
    }

    MsgData.DataBytes[index] = dataByte;
}