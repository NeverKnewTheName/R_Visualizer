#include "SystemOverviewObjectStore.h"


SystemOverviewObjectStore::SystemOverviewObjectStore(
        QObject *parent
        ) :
    ISystemOverviewObjectStore(parent)
{
}

SystemOverviewObjectStore::~SystemOverviewObjectStore()
{
}

SystemOverviewObjectStore::addSystemOverviewObject(ISysOverviewObject *object)
{
    sysOverviewObjStore->insert(object->getName(),object);
}

SystemOverviewObjectStore::

SystemOverviewObjectStore::
