#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>

class MsgTypeRep
{
public:
    MsgTypeRep();
    MsgTypeRep(int code, QString message, QColor color = QColor(Qt::white));

    int getCode() const;
    void setCode(int value);

    QString getMessage() const;
    void setMessage(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT();

private:
    int code;
    QString message;
    QColor color;
};

#endif // MSGTYPEREP_H
