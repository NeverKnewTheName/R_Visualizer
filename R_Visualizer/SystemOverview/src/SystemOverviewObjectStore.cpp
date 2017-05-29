#include "SystemOverviewObjectStore.h"

#include "ISystemOverviewObject.h"


SystemOverviewObjectStore::SystemOverviewObjectStore(
        QObject *parent
        ) :
    ISystemOverviewObjectStore(parent)
{
}

SystemOverviewObjectStore::~SystemOverviewObjectStore()
{
}

void SystemOverviewObjectStore::addSystemOverviewObject(ISystemOverviewObject *object)
{
    sysOverviewObjStore.insert(object->getObjectName(),object);
}
