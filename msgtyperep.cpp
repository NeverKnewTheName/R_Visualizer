#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonArray>

MsgTypeRep::MsgTypeRep()
{

}

MsgTypeRep::MsgTypeRep(int code, QString message, QColor color) : code(code), message(message), color(color)
{

}

int MsgTypeRep::getCode() const
{
    return code;
}

void MsgTypeRep::setCode(int value)
{
    code = value;
}

QString MsgTypeRep::getMessage() const
{
    return message;
}

void MsgTypeRep::setMessage(const QString &value)
{
    message = value;
}

QColor MsgTypeRep::getColor() const
{
    return color;
}

void MsgTypeRep::setColor(const QColor &value)
{
    color = value;
}

void MsgTypeRep::parseIN(QJsonObject jsonMsg)
{
    this->code = jsonMsg["code"].toInt();
    this->message = jsonMsg["message"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject MsgTypeRep::parseOUT()
{
    QJsonObject jsonMsg;
    jsonMsg["code"] = this->code;
    jsonMsg["message"] = this->message;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}
