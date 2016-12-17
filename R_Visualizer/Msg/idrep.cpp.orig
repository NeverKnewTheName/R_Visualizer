#include "idrep.h"
#include <QPainter>

#include <QDebug>

IDRep::IDRep() :
    isValidObj(false),
    id(0x0),
    name(QString("")),
    color(QColor(Qt::white))
{

}

IDRep::IDRep(const IDRep &other) :
    isValidObj(other.isValid()),
    id(other.getId()),
    name(other.getName()),
    color(other.getColor())
{

}

IDRep::IDRep(const quint16/*ToDo MsgIDType*/ id, const QString &name, const QColor &color) :
    isValidObj(true),
    id(id),
    name(name),
    color(color)
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

IDRep IDRep::createObjFromJson(const QJsonObject &jsonMsg)
{
    return IDRep(jsonMsg["id"].toInt(), jsonMsg["name"].toString(), QColor(jsonMsg["color"].toString()));
}

void IDRep::parseIN(const QJsonObject &jsonMsg)
{
    this->name = jsonMsg["name"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject IDRep::parseOUT() const
{
    QJsonObject jsonMsg;
    jsonMsg["id"] = this->id;
    jsonMsg["name"] = this->name;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}

bool IDRep::isValid() const
{
    return isValidObj;
}

bool IDRep::operator==(const IDRep &other) const
{
    return (this->id == other.getId());
}

//IDRep &IDRep::operator=(const IDRep &other)
//{

//}

quint16 IDRep::getId() const
{
    return id;
}

const QPixmap &IDRep::paintIDRep(const QRect &boundingRect)
{
    if((boundingRect.size() == IDRepPixmap.size()) && !IDRepPixmap.isNull())
    {
        return IDRepPixmap;
    }
    qDebug() << "IDRep repaint";
    IDRepPixmap = QPixmap(boundingRect.size());
    IDRepPixmap.fill(color);

    QPainter pixmapPainter(&IDRepPixmap);

    pixmapPainter.setRenderHint(QPainter::TextAntialiasing);
    pixmapPainter.drawText(
                IDRepPixmap.rect(),
                Qt::TextWordWrap |
                Qt::AlignCenter,
                name);

    return IDRepPixmap;
}
