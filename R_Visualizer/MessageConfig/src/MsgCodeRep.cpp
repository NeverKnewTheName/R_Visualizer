#include "MsgCodeRep.h"

#include <QDebug>

#include "fileparser.h"

MsgCodeRep::MsgCodeRep() :
    code(0x0),
    codeName(QString("")),
    color(Qt::black)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeRep &other) :
    code(other.code),
    codeName(other.codeName),
    color(other.color)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeType code) :
    code(code),
    codeName(QString("0x%1").arg(code, 4, 16, QLatin1Char('0'))),
    /* messageFormat("#Data0# #Data1# #Data2# #Data3# #Data4# #Data5# #Data6#"), */
    color(Qt::white)
{
}

MsgCodeRep::MsgCodeRep(const MsgCodeType code, const QString &codeName,const QColor &color) :
    code(code),
    codeName(codeName),
    color(color)
{
}

MsgCodeType MsgCodeRep::getCode() const
{
    return code;
}

void MsgCodeRep::setCode(const MsgCodeType code)
{
    this->code = code;
}


QString MsgCodeRep::getPlainTextAlias() const
{
    return codeName;
}

void MsgCodeRep::setPlainTextAlias(const QString &plainTextAlias)
{
    this->codeName = plainTextAlias;
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

bool MsgCodeRep::operator==(const MsgCodeRep &other) const
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
