#include "msg.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "fileparser.h"

#include <QDebug>

/**
 * @brief Initializes an empty Msg with invalid ID and Code as well as empty Data
 */
Msg::Msg() :
    msgTimestamp(QDateTime()),
    msgID(0x0u),
    msgCode(0x0u),
    msgData(DataByteVect())
{
}

Msg::Msg(const Msg &other) :
    msgTimestamp(other.msgTimestamp),
    msgID(other.msgID),
    msgCode(other.msgCode),
    msgData(other.msgData)
{
}

Msg::Msg(const QJsonObject &jsonObj) :
    msgTimestamp(QDateTime::fromString(jsonObj["MsgTimestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"))),
    msgID(static_cast<MsgIDType>(jsonObj["MsgID"].toInt())),
    msgCode(static_cast<MsgCodeType>(jsonObj["MsgCode"].toInt()))
{
    QJsonArray jsonData = jsonObj["MsgData"].toArray();
    msgData.DataSizeInBytes = jsonData.size();
    for(auto &&dataByteJson : jsonData)
    {
        msgData.DataBytes.append(static_cast<quint8>(dataByteJson.toInt()));
    }
}

/**
 * @brief Initializes a Msg with the given paramters
 *
 * @param[in] timestamp Timestamp of message receival
 * @param[in] id        ID of the message sender
 * @param[in] code      Code that identifies the purpose of the message
 * @param[in] dataBytes Data bytes that were sent alongside the message
 */
Msg::Msg(const QDateTime &timestamp, const MsgIDType id, const MsgCodeType code, DataByteVect dataBytes) :
    msgTimestamp(timestamp),
    msgID(id),
    msgCode(code),
    msgData(dataBytes)
{
}

Msg::~Msg()
{
}

QDateTime Msg::getTimestamp() const
{
    return msgTimestamp;
}

void Msg::setTimestamp(const QDateTime &value)
{
    msgTimestamp = value;
}

MsgIDType Msg::getId() const
{
    return msgID;
}

void Msg::setId(const MsgIDType value)
{
    msgID = value;
}

MsgCodeType Msg::getCode() const
{
    return msgCode;
}

void Msg::setCode(const MsgCodeType value)
{
    msgCode = value;
}

MsgData Msg::getData() const
{
    return msgData;
}

QString Msg::getDataAsString() const
{
    QString DataAsString("");

    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        DataAsString.append(QString("0x%1 ")
                            .arg(msgData.DataBytes.at(i)/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/));
    }
    return DataAsString.trimmed();
}

void Msg::parseIN(QJsonObject jsonMsg)
{
    msgTimestamp = QDateTime::fromString(jsonMsg["MsgTimestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    msgID = static_cast<MsgIDType>(jsonMsg["MsgID"].toInt());
    msgCode = static_cast<MsgCodeType>(jsonMsg["MsgCode"].toInt());
    QJsonArray jsonData = jsonMsg["MsgData"].toArray();
    msgData.DataSizeInBytes = jsonData.size();
    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        msgData.DataBytes.append(static_cast<quint8>(jsonData.at(i).toInt()));
    }
}

QJsonObject Msg::parseOUT() const
{
    QJsonObject jsonMsg;
    QJsonArray  jsonData;

    jsonMsg["MsgTimestamp"] = msgTimestamp.toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    jsonMsg["MsgID"] = QJsonValue(static_cast<int>(msgID));
    jsonMsg["MsgCode"] = QJsonValue(static_cast<int>(msgCode));
    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        jsonData.append(QJsonValue(static_cast<int>(msgData.DataBytes.at(i))));
    }
    jsonMsg["MsgData"] = jsonData;

    return jsonMsg;
}

MsgData Msg::getMsgData() const
{
    return msgData;
}

QByteArray Msg::getDataAsByteArray() const
{
    QByteArray data;
    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        data.append(msgData.DataBytes.at(i));
    }

    return data;
}

void Msg::setData(const DataByteVect &dataBytes)
{
    msgData = MsgData(dataBytes);
    /* msgData.DataBytes = dataBytes; */
    /* msgData.DataSizeInBytes = dataBytes.size(); */
}

void Msg::setDataByte(const quint8 index, const quint8 dataByte)
{
    if(index > msgData.DataSizeInBytes)
    {
        qDebug() << __FUNCTION__ << "Index not in range of msgData";
    }

    msgData.DataBytes[index] = dataByte;
}



///////////// MsgStorable INTERFACE //////////////////////
QJsonObject Msg::ParseToJson() const
{
    QJsonObject jsonMsg;
    QJsonArray  jsonData;

    jsonMsg["MsgTimestamp"] = msgTimestamp.toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    jsonMsg["MsgID"] = QJsonValue(static_cast<int>(msgID));
    jsonMsg["MsgCode"] = QJsonValue(static_cast<int>(msgCode));
    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        jsonData.append(QJsonValue(static_cast<int>(msgData.DataBytes.at(i))));
    }
    jsonMsg["MsgData"] = jsonData;

    return jsonMsg;
}

void Msg::ParseFromJson(const QJsonObject &jsonObj)
{
    msgTimestamp = QDateTime::fromString(jsonObj["MsgTimestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    msgID = static_cast<MsgIDType>(jsonObj["MsgID"].toInt());
    msgCode = static_cast<MsgCodeType>(jsonObj["MsgCode"].toInt());
    QJsonArray jsonData = jsonObj["MsgData"].toArray();
    msgData.DataSizeInBytes = jsonData.size();
    for(unsigned int i = 0; i < msgData.DataSizeInBytes; i++)
    {
        msgData.DataBytes.append(static_cast<quint8>(jsonData.at(i).toInt()));
    }
}

///////////// MsgStorable INTERFACE //////////////////////

void Msg::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
