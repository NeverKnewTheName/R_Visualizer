#ifndef IDREP_H
#define IDREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>

class IDRep
{
public:
    IDRep();
    IDRep(QString name, QColor color = QColor(Qt::white));

    QString getName() const;
    void setName(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT();

private:
    QString name;
    QColor color;
};

#endif // IDREP_H
