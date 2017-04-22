#include "MsgIDMapping.h"
#include <QDebug>

#include "fileparser.h"

MsgIDMapping::MsgIDMapping() :
    id(0x0),
    name(""),
    color(Qt::white)
{
}

MsgIDMapping::MsgIDMapping(const MsgIDMapping &other) :
    id(other.id),
    name(other.name),
    color(other.color)
{
}

MsgIDMapping::MsgIDMapping(const MsgIDType &id) :
    id(id),
    name(static_cast<QString>(id)), //ToDO Upper case letters for HEX representation would be nice
    color(Qt::white)
{
}

MsgIDMapping::MsgIDMapping(const MsgIDType &id, const QString &name, const QColor &color) :
    id(id),
    name(name),
    color(color)
{
}

void MsgIDMapping::setID(const MsgIDType &id)
{
    this->id = id;
}

MsgIDType MsgIDMapping::getID() const
{
    return id;
}

QString MsgIDMapping::getPlainTextAlias() const
{
    return name;
}

void MsgIDMapping::setPlainTextAlias(const QString &plainTextAlias)
{
    this->name = plainTextAlias;
}

QColor MsgIDMapping::getColorRepresentation() const
{
    return color;
}

void MsgIDMapping::setColorRepresentation(const QColor &colorRepresentation)
{
    this->color = colorRepresentation;
}

IMsgIDMapping &MsgIDMapping::operator =(const IMsgIDMapping &other)
{
    this->id = other.getID();
    this->name = other.getPlainTextAlias();
    this->color = other.getColorRepresentation();

    return *this;
}

bool MsgIDMapping::operator ==(const MsgIDMapping &other) const
{
    return this->id == other.id;
}

bool MsgIDMapping::operator ==(const IMsgIDMapping &other) const
{
    return this->id == other.getID();
}

void MsgIDMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

