#ifndef SYSOVRVOBJECTSTORE_H
#define SYSOVRVOBJECTSTORE_H

#include "sysovrvobject.h"
#include "can_packet.h"
#include "msg.h"

#include <QObject>
#include <QHash>

class SysOvrvObjectStore : public QObject
{
    Q_OBJECT
public:
    explicit SysOvrvObjectStore(QObject *parent = 0);

    QHash<QString, SysOvrvObject *> getObjectStore() const;
    void addMesageToWatch(quint16 id, quint8 code, SysOvrvObject *relatedSysOvrvObj);

private:
    QHash<QString, SysOvrvObject*> objectStore;
    QHash<quint16, QHash<quint8, QVector<SysOvrvObject*>>> msgParserStore;
    QPointF curObjPos;

signals:
    void objectAddedToStore(SysOvrvObject *addedObject, QPointF &pos);
    void objectRemovedFromStore(SysOvrvObject *removedObject);

public slots:
    void addObject();
    void rmvObject();
    void updtObject();
    void duplicateObject();
    void addObjToStore(SysOvrvObject *objToAdd);
    void removeObject(SysOvrvObject *objToRmv);
    void updateObject(SysOvrvObject *objToUpdt);
    void receiveMessage(Data_PacketPtr ptr);
};

#endif // SYSOVRVOBJECTSTORE_H
