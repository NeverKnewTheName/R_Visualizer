#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include "msg.h"

#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QStyleOptionViewItem>


class MsgTypeRep
{
public:
    MsgTypeRep();
    MsgTypeRep(const MsgTypeRep &other);
    MsgTypeRep(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    MsgCodeType getCode() const;

    QString getCodeName() const;
    void setCodeName(const QString &value);

    QString getMessageFormat() const;
    void setMessageFormat(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    static MsgTypeRep createObjFromJson(const QJsonObject &jsonMsg);
    void parseIN(const QJsonObject &jsonMsg);
    QJsonObject parseOUT() const;

    bool isValid() const;
    bool operator==(const MsgTypeRep &other) const;

    QString getMsgDataAsString(Msg &msg);
    void paintMsgTypeRep(QPainter *painter, const QStyleOptionViewItem &option, Msg &msg) const;

private:
    bool isValidObj;
    const MsgCodeType code;  //ToDO MsgCodeType...
    QString codeName;
    QString messageFormat;
    QColor color;
    QSize MsgTypeRepSizeHint;
};

#endif // MSGTYPEREP_H
