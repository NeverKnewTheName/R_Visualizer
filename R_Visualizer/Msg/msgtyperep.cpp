#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonArray>

MsgTypeRep::MsgTypeRep()
{

}

MsgTypeRep::MsgTypeRep(int code, QString codeName, QString messageFormat, QColor color) : code(code), codeName(codeName), messageFormat(messageFormat), color(color)
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


QString MsgTypeRep::getCodeName() const
{
    return codeName;
}

void MsgTypeRep::setCodeName(const QString &value)
{
    codeName = value;
}

QString MsgTypeRep::getMessageFormat() const
{
    return messageFormat;
}

void MsgTypeRep::setMessageFormat(const QString &value)
{
    messageFormat = value;
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
    this->codeName = jsonMsg["codeName"].toString();
    this->messageFormat = jsonMsg["messageFormat"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject MsgTypeRep::parseOUT()
{
    QJsonObject jsonMsg;
    jsonMsg["code"] = this->code;
    jsonMsg["codeName"] = this->codeName;
    jsonMsg["messageFormat"] = this->messageFormat;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}
