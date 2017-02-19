#ifndef SYSOVRVOBJECTSTORE_H
#define SYSOVRVOBJECTSTORE_H

#include "sysovrvobject.h"
#include "can_packet.h"

#include <QObject>
#include <QHash>

class Msg;

class SysOvrvObjectStore : public QObject
{
    Q_OBJECT
public:
    explicit SysOvrvObjectStore(QObject *parent = 0);

    QHash<QString, SysOvrvObject *> getObjectStore() const;
    void addMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj);
    void removeMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj);

    void addObject(SysOvrvObject *obj);
    void removeObject(SysOvrvObject *obj);
    void updateObject(SysOvrvObject *obj);

private:
    QHash<QString, SysOvrvObject*> objectStore;
    QHash<MsgIDType, QHash<MsgCodeType, QVector<SysOvrvObject*>>> msgParserStore;
    QPointF curObjPos;

signals:
    void objectAddedToStore(SysOvrvObject *addedObject);
    void objectRemovedFromStore(SysOvrvObject *removedObject);

public slots:
    void slt_addObject(SysOvrvObject *objToAdd);
    void slt_removeObject(SysOvrvObject *objToRmv);
    void slt_updateObject(SysOvrvObject *objToUpdt);
    void slt_receiveMessage(const Msg &newMsg);
};

#endif // SYSOVRVOBJECTSTORE_H
