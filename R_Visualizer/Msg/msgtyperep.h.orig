#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>

class MsgTypeRep
{
public:
    MsgTypeRep();
    MsgTypeRep(const MsgTypeRep &other);
    MsgTypeRep(const quint8/*ToDo MsgCodeType*/ code, const QString &codeName, const QString &messageFormat, const QColor &color);

    quint8 getCode() const;  //ToDO MsgCodeType

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

    const QPixmap &paintMsgTypeRep(const QRect &boundingRect);

private:
    bool isValidObj;
    const quint8 code;  //ToDO MsgCodeType...
    QString codeName;
    QString messageFormat;
    QColor color;
    QPixmap MsgTypeRepPixmap;
};

#endif // MSGTYPEREP_H
