#ifndef SYSOVRVOBJECTSTORE_H
#define SYSOVRVOBJECTSTORE_H

#include "sysovrvobject.h"

#include <QObject>
#include <QHash>

class SysOvrvObjectStore : public QObject
{
    Q_OBJECT
public:
    explicit SysOvrvObjectStore(QObject *parent = 0);

    QHash<QString, SysOvrvObject *> getObjectStore() const;

private:
    QHash<QString, SysOvrvObject*> objectStore;

signals:
    void objectAddedToStore(SysOvrvObject *addedObject);
    void objectRemovedFromStore(SysOvrvObject *removedObject);

public slots:
    void addObject();
    void rmvObject();
    void updtObject();
    void addObjToStore(SysOvrvObject *objToAdd);
    void removeObject(SysOvrvObject *objToRmv);
    void updateObject(SysOvrvObject *objToUpdt);
};

#endif // SYSOVRVOBJECTSTORE_H
