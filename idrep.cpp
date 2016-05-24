#include "idrep.h"

IDRep::IDRep()
{

}

IDRep::IDRep(int id, QString name, QColor color) : id(id), name(name), color(color)
{

}

int IDRep::getId() const
{
    return id;
}

void IDRep::setId(int value)
{
    id = value;
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
    this->id = jsonMsg["id"].toInt();
    this->name = jsonMsg["name"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject IDRep::parseOUT()
{
    QJsonObject jsonMsg;
    jsonMsg["id"] = this->id;
    jsonMsg["name"] = this->name;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}
