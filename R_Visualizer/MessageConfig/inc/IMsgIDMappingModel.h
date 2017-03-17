#ifndef IIDMODEL_H
#define IIDMODEL_H

#include <QString>
#include <QColor>
#include <QCompleter>

#include "msg.h"
#include "IMsgIDrep.h"

class IMsgIDMappingModel
{
public:
    IMsgIDMappingModel();
    virtual ~IMsgIDMappingModel();

    IDRep getIDRepToID(const MsgIDType id) const = 0;
    QString getNameToID(const MsgIDType id) const = 0;
    MsgIDType getIDToName(const QString &name) const = 0;
    QColor getColorToID(const MsgIDType id) const = 0;

    bool contains(const MsgIDType id) const = 0;

    QCompleter *createIDCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    sgnl_IDRepAdded(const IDRep &newIDRep) = 0;
    sgnl_IDRepUpdated(const IDRep &updatedIDRep) = 0;
    sgnl_IDRepUpdated(const MsgIDType relatedID) = 0;
};

#endif /* IIDMODEL_H */
