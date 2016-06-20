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

public slots:
    void addObject();
    void addObjToStore(SysOvrvObject *objToAdd);
    void removeObject(QString &objectName);
    void updateObject(QString &objectName);
};

#endif // SYSOVRVOBJECTSTORE_H
