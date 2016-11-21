#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QPainter>

MsgTypeRep::MsgTypeRep() :
    isValidObj(false),
    code(0x0),
    codeName(QString("")),
    messageFormat(QString("")),
    color(QColor(Qt::white))
{

}

MsgTypeRep::MsgTypeRep(const MsgTypeRep &other) :
    isValidObj(other.isValid()),
    code(other.getCode()),
    codeName(other.getCodeName()),
    messageFormat(other.getMessageFormat()),
    color(other.getColor())
{

}

MsgTypeRep::MsgTypeRep(const quint8/*ToDo MsgCodeType*/ code, const QString &codeName, const QString &messageFormat, const QColor &color) :
    isValidObj(true),
    code(code),
    codeName(codeName),
    messageFormat(messageFormat),
    color(color)
{

}

quint8/*ToDo MsgCodeType*/ MsgTypeRep::getCode() const
{
    return code;
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

MsgTypeRep MsgTypeRep::createObjFromJson(const QJsonObject &jsonMsg)
{
    return MsgTypeRep(
                jsonMsg["code"].toInt(),
                jsonMsg["codeName"].toString(),
                jsonMsg["messageFormat"].toString(),
                QColor(jsonMsg["color"].toString())
            );
}

void MsgTypeRep::parseIN(const QJsonObject &jsonMsg)
{
//    this->code = jsonMsg["code"].toInt();
    this->codeName = jsonMsg["codeName"].toString();
    this->messageFormat = jsonMsg["messageFormat"].toString();
    this->color = QColor(jsonMsg["color"].toString());
}

QJsonObject MsgTypeRep::parseOUT() const
{
    QJsonObject jsonMsg;
    jsonMsg["code"] = this->code;
    jsonMsg["codeName"] = this->codeName;
    jsonMsg["messageFormat"] = this->messageFormat;
    jsonMsg["color"] = this->color.name();
    return jsonMsg;
}

bool MsgTypeRep::isValid() const
{
    return isValidObj;
}

bool MsgTypeRep::operator==(const MsgTypeRep &other) const
{
    return (this->code == other.getCode());
}

const QPixmap &MsgTypeRep::paintMsgTypeRep(const QRect &boundingRect)
{
    if((boundingRect.size() == MsgTypeRepPixmap.size()) && !MsgTypeRepPixmap.isNull())
    {
        return MsgTypeRepPixmap;
    }
    MsgTypeRepPixmap = QPixmap(boundingRect.size());
    MsgTypeRepPixmap.fill(color);

    QPainter pixmapPainter(&MsgTypeRepPixmap);

    pixmapPainter.drawText(
                MsgTypeRepPixmap.rect(),
                Qt::TextWordWrap |
                Qt::AlignCenter,
                QString("Code: %1\nData: 0x%2 0x%3 0x%4 0x%5 0x%6 0x%7 0x%8")
                .arg(code)
                .arg(10,2,16,'0')
                .arg(11,2,16,'0')
                .arg(12,2,16,'0')
                .arg(13,2,16,'0')
                .arg(14,2,16,'0')
                .arg(15,2,16,'0')
                .arg(16,2,16,'0')
                );

    return MsgTypeRepPixmap;
}
