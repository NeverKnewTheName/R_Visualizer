#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QPainter>

#include <QTextDocument>

#include <QDebug>

MsgTypeRep::MsgTypeRep() :
    isValidObj(false),
    code(0x0),
    codeName(QString("")),
    messageFormat(QString("")),
    color(Qt::black)
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

MsgTypeRep::MsgTypeRep(const MsgCodeType code) :
    isValidObj(true),
    code(code),
    codeName(QString("0x%1").arg(code, 4, 16, QLatin1Char('0'))),
    messageFormat("#Data0# #Data1# #Data2# #Data3# #Data4# #Data5# #Data6#"),
    color(Qt::white)
{
}

MsgTypeRep::MsgTypeRep(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color) :
    isValidObj(true),
    code(code),
    codeName(codeName),
    messageFormat(messageFormat),
    color(color)
{

}

MsgCodeType MsgTypeRep::getCode() const
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

QString MsgTypeRep::getMsgDataAsString(Msg &msg)
{
    return msg.getDataAsString();
}

void MsgTypeRep::paintMsgTypeRep(QPainter *painter, const QStyleOptionViewItem &option, Msg &msg) const
{
    QTextDocument ItemText(QString("Code: %1\nData:\n0x%2 0x%3 0x%4 \n0x%5 0x%6 0x%7 0x%8")
            .arg(code)
            .arg((int)10)
            .arg((int)11)
            .arg((int)12)
            .arg((int)13)
            .arg((int)14)
            .arg((int)15)
            .arg((int)16));

    ItemText.setTextWidth(option.rect.width());

//    qDebug() << __PRETTY_FUNCTION__ << "  TextWidth: " << ItemText.textWidth();

//    ItemText.size().toSize();
//    int lineCount = ItemText.count(QChar('\n'));
//    QSize sizeHint(option.rect.width(), (option.fontMetrics.size(0,QString("X")).height()*lineCount));

    QSizeF sizeHint(ItemText.size());
//    msg.setMsgSizeHint(sizeHint.toSize());

    QRectF BoundingRect(option.rect.x(), option.rect.y(), sizeHint.width(), sizeHint.height());
//    qDebug() << __PRETTY_FUNCTION__ << "Rects: " << option.rect << BoundingRect;

//    ItemText.drawContents();

    painter->save();
//    painter->setWindow(option.rect.x(),option.rect.y(),msg.getMsgSizeHint().width(),msg.getMsgSizeHint().height());
    painter->fillRect(BoundingRect, (option.features & QStyleOptionViewItem::Alternate) ? color.darker(100) : color);
    painter->setRenderHint(QPainter::TextAntialiasing);

    painter->translate( BoundingRect.topLeft() );
    ItemText.drawContents( painter, BoundingRect.translated( -BoundingRect.topLeft() ) );

//    ItemText.drawContents(painter);
    painter->restore();
}
