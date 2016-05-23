#include "msg.h"

Msg::Msg()
{

}

Msg::Msg(int timestamp, int id, int message)
    : timestamp(timestamp), id(id), message(message)
{
}

int Msg::getTimestamp() const
{
    return timestamp;
}

void Msg::setTimestamp(int value)
{
    timestamp = value;
}

int Msg::getId() const
{
    return id;
}

void Msg::setId(int value)
{
    id = value;
}

int Msg::getCode() const
{
    return code;
}

void Msg::setCode(int value)
{
    code = value;
}

int Msg::getMessage() const
{
    return message;
}

void Msg::setMessage(int value)
{
    message = value;
}

void Msg::parseIN(QJsonObject jsonMsg)
{
    this->timestamp = jsonMsg["timestamp"].toInt();
    this->id = jsonMsg["id"].toInt();
    this->code = jsonMsg["code"].toInt();
    this->message = jsonMsg["message"].toInt();
}

QJsonObject Msg::parseOUT()
{
    QJsonObject jsonMsg;
    (jsonMsg)["timestamp"] = this->timestamp;
    (jsonMsg)["id"] = this->id;
    (jsonMsg)["code"] = this->code;
    (jsonMsg)["message"] = this->message;
    return jsonMsg;
}
