#ifndef IDREP_H
#define IDREP_H

#include "msg.h"

#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QStyleOptionViewItem>

class IDRep
{
public:
    IDRep();
    IDRep(const IDRep& other);
    IDRep(const MsgIDType id, const QString &name, const QColor &color); /*ToDo MsgIDType*/

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

    MsgIDType getId() const;

    void paintIDRep(const QRect &rect, QPixmap &destPixMap) const;

private:
    bool isValidObj;
    const MsgIDType/*ToDo MsgIDType*/ id;
    QString name;
    QColor color;
    QPixmap IDRepPixmap;
};

#endif // IDREP_H
