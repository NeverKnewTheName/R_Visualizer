#include "MsgCodeMapping.h"

#include <QDebug>

#include "fileparser.h"

MsgCodeMapping::MsgCodeMapping() :
    code(0x0),
    name(QString("")),
    color(Qt::black)
{
}

MsgCodeMapping::MsgCodeMapping(const MsgCodeMapping &other) :
    code(other.code),
    name(other.name),
    color(other.color)
{
}

MsgCodeMapping::MsgCodeMapping(const MsgCodeType &code) :
    code(code),
    name(static_cast<QString>(code)),
    /* messageFormat("#Data0# #Data1# #Data2# #Data3# #Data4# #Data5# #Data6#"), */
    color(Qt::white)
{
}

MsgCodeMapping::MsgCodeMapping(const MsgCodeType &code, const QString &name,const QColor &color) :
    code(code),
    name(name),
    color(color)
{
}

MsgCodeType MsgCodeMapping::getCode() const
{
    return code;
}

void MsgCodeMapping::setCode(const MsgCodeType &code)
{
    this->code = code;
}


QString MsgCodeMapping::getPlainTextAlias() const
{
    return name;
}

void MsgCodeMapping::setPlainTextAlias(const QString &plainTextAlias)
{
    this->name = plainTextAlias;
}

/* QString MsgCodeMapping::getMessageFormat() const */
/* { */
/*     return messageFormat; */
/* } */

/* void MsgCodeMapping::setMessageFormat(const QString &value) */
/* { */
/*     messageFormat = value; */
/* } */

QColor MsgCodeMapping::getColorRepresentation() const
{
    return color;
}

void MsgCodeMapping::setColorRepresentation(const QColor &colorRepresentation)
{
    this->color = colorRepresentation;
}

IMsgCodeMapping &MsgCodeMapping::operator =(const IMsgCodeMapping &other)
{
    this->code = other.getCode();
    this->name = other.getPlainTextAlias();
    this->color = other.getColorRepresentation();

    return *this;
}

bool MsgCodeMapping::operator ==(const MsgCodeMapping &other) const
{
    return (this->code == other.code);
}

bool MsgCodeMapping::operator ==(const IMsgCodeMapping &other) const
{
    return (this->code == other.getCode());
}

/* QString MsgCodeMapping::getMsgDataAsString(Msg &msg) */
/* { */
/*     return msg.getDataAsString(); */
/* } */

void MsgCodeMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
