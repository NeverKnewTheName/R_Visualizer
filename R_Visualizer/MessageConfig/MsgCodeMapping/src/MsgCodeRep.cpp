#include "MsgCodeRep.h"

#include <QDebug>

#include "fileparser.h"

MsgCodeRep::MsgCodeRep() :
    code(0x0),
    name(QString("")),
    color(Qt::black)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeRep &other) :
    code(other.code),
    name(other.name),
    color(other.color)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeType &code) :
    code(code),
    name(static_cast<QString>(code)),
    /* messageFormat("#Data0# #Data1# #Data2# #Data3# #Data4# #Data5# #Data6#"), */
    color(Qt::white)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeType &code, const QString &name,const QColor &color) :
    code(code),
    name(name),
    color(color)
{
}

MsgCodeType MsgCodeRep::getCode() const
{
    return code;
}

void MsgCodeRep::setCode(const MsgCodeType &code)
{
    this->code = code;
}


QString MsgCodeRep::getPlainTextAlias() const
{
    return name;
}

void MsgCodeRep::setPlainTextAlias(const QString &plainTextAlias)
{
    this->name = plainTextAlias;
}

/* QString MsgCodeRep::getMessageFormat() const */
/* { */
/*     return messageFormat; */
/* } */

/* void MsgCodeRep::setMessageFormat(const QString &value) */
/* { */
/*     messageFormat = value; */
/* } */

QColor MsgCodeRep::getColorRepresentation() const
{
    return color;
}

void MsgCodeRep::setColorRepresentation(const QColor &colorRepresentation)
{
    this->color = colorRepresentation;
}

IMsgCodeRep &MsgCodeRep::operator =(const IMsgCodeRep &other)
{
    this->code = other.getCode();
    this->name = other.getPlainTextAlias();
    this->color = other.getColorRepresentation();

    return *this;
}

bool MsgCodeRep::operator ==(const MsgCodeRep &other) const
{
    return (this->code == other.code);
}

bool MsgCodeRep::operator ==(const IMsgCodeRep &other) const
{
    return (this->code == other.getCode());
}

/* QString MsgCodeRep::getMsgDataAsString(Msg &msg) */
/* { */
/*     return msg.getDataAsString(); */
/* } */

void MsgCodeRep::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
