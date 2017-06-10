#include "SystemOverviewObjectStore.h"


SystemOverviewObjectStore::SystemOverviewObjectStore(
        QObject *parent
        ) :
    ISystemOverviewObjectStore(parent)
{
}

SystemOverviewObjectStore::~SystemOverviewObjectStore()
{
    clear();
}

void SystemOverviewObjectStore::addSystemOverviewObject(ISysOvrvObjPtr object)
{
    sysOverviewObjStore.insert(object->getObjectName(),object);
    emit sgnl_objectAdded(object);
}

ISysOvrvObjPtr SystemOverviewObjectStore::getObj(const QString &objectName)
{
    return sysOverviewObjStore.value(objectName);
}

void SystemOverviewObjectStore::removeObj(const QString &objectName)
{
    if(sysOverviewObjStore.contains(objectName))
    {
        ISysOvrvObjPtr objToRemove = sysOverviewObjStore.value(objectName);
        sysOverviewObjStore.remove(objectName);
        emit sgnl_objectRemoved(objToRemove);
    }
}

QVector<ISysOvrvObjPtr> SystemOverviewObjectStore::getObjects() const
{
    return sysOverviewObjStore.values().toVector();
}

void SystemOverviewObjectStore::clear()
{
    QList<ISysOvrvObjPtr> objects = sysOverviewObjStore.values();
    for(ISysOvrvObjPtr object : objects)
    {
        sysOverviewObjStore.remove(object->getObjectName());
        emit sgnl_objectRemoved(object);
    }
}
