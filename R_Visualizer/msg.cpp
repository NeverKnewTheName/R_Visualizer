#include "msg.h"

Msg::Msg()
{
    this->timestamp = QDateTime();
    this->id = 0x0u;
    this->data = {
         0,0,0,0,0,0,0,0
    };
}

Msg::Msg(QDateTime timestamp, unsigned int id, MsgDataT &data) : timestamp(timestamp), id(id), data(data)
{

}

Msg::Msg(QDateTime timestamp, unsigned int id, QByteArray &data) : timestamp(timestamp), id(id)
{
    this->data = {
         data.at(0),0,0,0,0,0,0,0
    };
    if(data.length() > 1 )
    {
        this->data.data0 = data.at(1);
    }
    if(data.length() > 2 )
    {
        this->data.data1 = data.at(2);
    }
    if(data.length() > 3 )
    {
        this->data.data2 = data.at(3);
    }
    if(data.length() > 4 )
    {
        this->data.data3 = data.at(4);
    }
    if(data.length() > 5 )
    {
        this->data.data4 = data.at(5);
    }
    if(data.length() > 6 )
    {
        this->data.data5 = data.at(6);
    }
    if(data.length() > 7 )
    {
        this->data.data6 = data.at(7);
    }

}

Msg::Msg(QDateTime timestamp, unsigned int id, quint8 code, quint8 data0, quint8 data1, quint8 data2, quint8 data3, quint8 data4, quint8 data5, quint8 data6)
    : timestamp(timestamp), id(id), data({code, data0, data1, data2, data3, data4, data5, data6})
{

}

QDateTime Msg::getTimestamp() const
{
    return timestamp;
}

void Msg::setTimestamp(QDateTime value)
{
    timestamp = value;
}

unsigned int Msg::getId() const
{
    return id;
}

void Msg::setId(unsigned int value)
{
    id = value;
}


quint8 Msg::getCode() const
{
    //return this->data.at(0x7u);
    return this->data.code;
}

void Msg::setCode(quint8 value)
{
    //this->data.at(0x7u) = value;
    this->data.code = value;
}

//ToDO
//unsigned int Msg::getMessage() const
//{
//    return message;
//}

void Msg::setMessage(quint8 data0, quint8 data1, quint8 data2, quint8 data3, quint8 data4, quint8 data5, quint8 data6)
{
    this->data = { this->data.code, data0, data1, data2, data3, data4, data5, data6 };
}

QString Msg::getMessageAsString() const
{
    return QString("0x%1%2%3%4%5%6%7")
            .arg(this->data.data0/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data1/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data2/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data3/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data4/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data5/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data6/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
}

QString Msg::getDataAsString() const
{
    return QString("Code:\t0x%1\nMessage:\t0x%2%3%4%5%6%7%8")
            .arg(this->data.code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data0/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data1/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data2/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data3/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data4/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data5/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
            .arg(this->data.data6/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
}

void Msg::parseIN(QJsonObject jsonMsg)
{
    this->timestamp = QDateTime::fromString(jsonMsg["timestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    this->id = jsonMsg["id"].toInt();
    QJsonObject jsonData = jsonMsg["data"].toObject();
    this->data  = { jsonData["code"].toInt(), jsonData["data0"].toInt(), jsonData["data1"].toInt(), jsonData["data2"].toInt(), jsonData["data3"].toInt(), jsonData["data4"].toInt(), jsonData["data5"].toInt(), jsonData["data6"].toInt() };
}

QJsonObject Msg::parseOUT() const
{
    QJsonObject jsonMsg;
    QJsonObject jsonData;
    jsonMsg["timestamp"] = this->timestamp.toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    jsonMsg["id"] = QJsonValue(static_cast<int>(this->id));
    jsonData["code"] = this->data.code;
    jsonData["data0"] = this->data.data0;
    jsonData["data1"] = this->data.data1;
    jsonData["data2"] = this->data.data2;
    jsonData["data3"] = this->data.data3;
    jsonData["data4"] = this->data.data4;
    jsonData["data5"] = this->data.data5;
    jsonData["data6"] = this->data.data6;
    jsonMsg["data"] = jsonData;

    return jsonMsg;
}

MsgDataT Msg::getData() const
{
    return this->data;
}

QByteArray Msg::getDataAsByteArray() const
{
    QByteArray data;
    data.append( this->data.code);
    data.append( this->data.data0);
    data.append( this->data.data1);
    data.append( this->data.data2);
    data.append( this->data.data3);
    data.append( this->data.data4);
    data.append( this->data.data5);
    data.append( this->data.data6);

    return data;
}

void Msg::setData(const MsgDataT &value)
{
    this->data = value;
}

void Msg::setData(quint8 code, quint8 data0, quint8 data1, quint8 data2, quint8 data3, quint8 data4, quint8 data5, quint8 data6)
{
    this->data = { code, data0, data1, data2, data3, data4, data5, data6 };
}
