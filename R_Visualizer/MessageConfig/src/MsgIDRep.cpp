#include "MsgIDRep.h"
#include <QDebug>

#include "fileparser.h"

MsgIDRep::MsgIDRep() :
    id(0x0),
    name(""),
    color(Qt::white)
{
}

MsgIDRep::MsgIDRep(const MsgIDRep &other) :
    id(other.id),
    name(other.name),
    color(other.color)
{
}

MsgIDRep::MsgIDRep(const MsgIDType id) :
    id(id),
    name(QString("0x%1").arg(id, 4, 16, QLatin1Char('0'))), //ToDO Upper case letters for HEX representation would be nice
    color(Qt::white)
{
}

MsgIDRep::MsgIDRep(const MsgIDType id, const QString &name, const QColor &color) :
    id(id),
    name(name),
    color(color)
{
}

void MsgIDRep::setID(const MsgIDType id)
{
    this->id = id;
}

MsgIDType MsgIDRep::getID() const
{
    return id;
}

QString MsgIDRep::getPlainTextAlias() const
{
    return name;
}

void MsgIDRep::setPlainTextAlias(const QString &plainTextAlias)
{
    this->name = plainTextAlias;
}

QColor MsgIDRep::getColorRepresentation() const
{
    return color;
}

void MsgIDRep::setColorRepresentation(const QColor &colorRepresentation)
{
    this->color = colorRepresentation;
}

void MsgIDRep::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

