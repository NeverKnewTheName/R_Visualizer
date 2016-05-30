#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>

class MsgTypeRep
{
public:
    MsgTypeRep();
    MsgTypeRep(int code, QString codeName, QString messageFormat, QColor color = QColor(Qt::white));

    int getCode() const;
    void setCode(int value);

    QString getCodeName() const;
    void setCodeName(const QString &value);

    QString getMessageFormat() const;
    void setMessageFormat(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT();

private:
    int code;
    QString codeName;
    QString messageFormat;
    QColor color;
};

#endif // MSGTYPEREP_H
