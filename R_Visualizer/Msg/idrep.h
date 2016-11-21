#ifndef IDREP_H
#define IDREP_H

#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>

class IDRep
{
public:
    IDRep();
    IDRep(const IDRep& other);
    IDRep(const quint16 id, const QString &name, const QColor &color); /*ToDo MsgIDType*/

    QString getName() const;
    void setName(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    static IDRep createObjFromJson(const QJsonObject &jsonMsg);
    void parseIN(const QJsonObject &jsonMsg);
    QJsonObject parseOUT() const;

    bool isValid() const;
    bool operator==(const IDRep &other) const;

//    IDRep &operator=(const IDRep &other);

    quint16 getId() const;

    const QPixmap &paintIDRep(const QRect &boundingRect);

private:
    bool isValidObj;
    const quint16/*ToDo MsgIDType*/ id;
    QString name;
    QColor color;
    QPixmap IDRepPixmap;
};

#endif // IDREP_H
