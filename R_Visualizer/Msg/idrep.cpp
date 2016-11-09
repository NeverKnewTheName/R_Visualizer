#include "idrep.h"

IDRep::IDRep()
{

}

IDRep::IDRep(QString name, QColor color) : name(name), color(color)
{

}

QString IDRep::getName() const
{
    return name;
}

void IDRep::setName(const QString &value)
{
    name = value;
}

QColor IDRep::getColor() const
{
    return color;
}

void IDRep::setColor(const QColor &value)
{
    color = value;
}

void IDRep::parseIN(QJsonObject jsonMsg)
{
    this->name = jsonMsg["name"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject IDRep::parseOUT()
{
    QJsonObject jsonMsg;
    jsonMsg["name"] = this->name;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}
