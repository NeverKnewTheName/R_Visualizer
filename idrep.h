#ifndef IDREP_H
#define IDREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>

class IDRep
{
public:
    IDRep();
    IDRep(int id, QString name, QColor color = QColor(Qt::white));

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT();

private:
    int id;
    QString name;
    QColor color;
};

#endif // IDREP_H
