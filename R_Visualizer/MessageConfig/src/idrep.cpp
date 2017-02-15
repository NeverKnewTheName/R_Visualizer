#include "idrep.h"
#include <QPainter>

#include <QDebug>

#include "fileparser.h"

IDRep::IDRep() :
    isValidObj(false),
    id(0x0),
    name(""),
    color(Qt::white)
{
}

IDRep::IDRep(const IDRep &other) :
    isValidObj(other.isValid()),
    id(other.getId()),
    name(other.getName()),
    color(other.getColor())
{
}

IDRep::IDRep(const MsgIDType id) :
    isValidObj(true),
    id(id),
    name(QString("0x%1").arg(id, 4, 16, QLatin1Char('0'))), //ToDO Upper case letters for HEX representation would be nice
    color(Qt::white)
{
}

IDRep::IDRep(const MsgIDType id, const QString &name, const QColor &color) :
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
    return IDRep(static_cast<MsgIDType>(jsonMsg["id"].toInt()), jsonMsg["name"].toString(), QColor(jsonMsg["color"].toString()));
}

void IDRep::parseIN(const QJsonObject &jsonMsg)
{
    this->name = jsonMsg["name"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject IDRep::parseOUT() const
{
    QJsonObject jsonMsg;
    jsonMsg["id"] = static_cast<int>(this->id);
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

MsgIDType IDRep::getId() const
{
    return id;
}

void IDRep::paintIDRep(QPainter *painter, const QStyleOptionViewItem &option) const
{
//    qDebug() << "IDRep repaint: "<<id << " color: " << color;

//    QBrush brush();

    painter->save();
//    painter->setBrush(brush);
    painter->setFont(option.font);
    painter->setRenderHint(QPainter::TextAntialiasing);
//    painter->setBackground(brush);

    painter->fillRect(option.rect, (option.features & QStyleOptionViewItem::Alternate) ? color.darker(100) : color);
    painter->drawText(
                option.rect,
                Qt::TextWordWrap |
                Qt::AlignCenter,
                name);
    painter->restore();
}

void IDRep::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
