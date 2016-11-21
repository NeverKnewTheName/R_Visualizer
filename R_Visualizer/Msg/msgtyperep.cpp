#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QPainter>

#include <QTextDocument>

MsgTypeRep::MsgTypeRep() :
    isValidObj(false),
    code(0x0),
    codeName(QString("")),
    messageFormat(QString("")),
    color(QColor(Qt::black))
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

MsgTypeRep::MsgTypeRep(const MsgCodeType/*ToDo MsgCodeType*/ code, const QString &codeName, const QString &messageFormat, const QColor &color) :
    isValidObj(true),
    code(code),
    codeName(codeName),
    messageFormat(messageFormat),
    color(color)
{

}

MsgCodeType/*ToDo MsgCodeType*/ MsgTypeRep::getCode() const
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
                static_cast<const MsgCodeType>(jsonMsg["code"].toInt()),
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
    jsonMsg["code"] = static_cast<int>(this->code);
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

void MsgTypeRep::paintMsgTypeRep(const QRect &rect, QPixmap &destPixMap)
{
    QTextDocument ItemText(QString("Code: %1\nData: 0x%2 0x%3 0x%4 0x%5 0x%6 0x%7 0x%8")
            .arg(code)
            .arg((int)10,(int)2,(int)16,'0')
            .arg((int)11,(int)2,(int)16,'0')
            .arg((int)12,(int)2,(int)16,'0')
            .arg((int)13,(int)2,(int)16,'0')
            .arg((int)14,(int)2,(int)16,'0')
            .arg((int)15,(int)2,(int)16,'0')
            .arg((int)16,(int)2,(int)16,'0')
                           );

    ItemText.setTextWidth(rect.width());
    destPixMap = QPixmap(ItemText.size().toSize());
    destPixMap.fill( /*(rect.features & QStyleOptionViewItem::Alternate) ? color.darker() :*/ color);

    QPainter pixmapPainter(&destPixMap);

    pixmapPainter.setRenderHint(QPainter::TextAntialiasing);
    ItemText.drawContents(&pixmapPainter, destPixMap.rect());

//    QPainter pixmapPainter(&destPixMap);

//    pixmapPainter.drawText(
//                destPixMap.rect(),
//                ItemText.toPlainText(),
//                ItemText.
//                );
}
