#include "SystemOverview.h"

#include "ISystemOverviewObjectStore.h"

#include "IMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

SystemOverview::SystemOverview(
        ISystemOverviewObjectStore *systemOverviewObjectStore,
        QObject *parent
        ) :
    ISystemOverview(parent),
    systemOverviewObjectStore(systemOverviewObjectStore)
{
    connect(
                systemOverviewObjectStore,
                &ISystemOverviewObjectStore::sgnl_objectAdded,
                this,
                &ISystemOverview::sgnl_objectAdded
            );
    connect(
                systemOverviewObjectStore,
                &ISystemOverviewObjectStore::sgnl_objectRemoved,
                this,
                &ISystemOverview::sgnl_objectRemoved
            );
}

SystemOverview::~SystemOverview()
{
    systemOverviewObjectStore->clear();
}

void SystemOverview::receiveMsg(const IMsg &receivedMsg)
{
    const MessageTypeIdentifier &msgType = receivedMsg.getMsgType();

    QVector<ISysOvrvObjPtr> objects = systemOverviewObjectStore->getObjects();
    for(ISysOvrvObjPtr object : objects)
    {
        QVector<SysOvrvObjTriggerPtr> triggers =
                object->getGlobalObjectTriggers();
        for(SysOvrvObjTriggerPtr trigger : triggers)
        {
            trigger->trigger(receivedMsg);
        }
    }
}

void SystemOverview::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
    //ToDo
}

void SystemOverview::addObject(ISysOvrvObjPtr object)
{
    systemOverviewObjectStore->addSystemOverviewObject(object);
}

void SystemOverview::removeObject(ISysOvrvObjPtr object)
{
    systemOverviewObjectStore->removeObj(object->getObjectName());
}

void SystemOverview::removeObject(const QString &objectName)
{
    ISysOvrvObjPtr objToRemove = getObject(objectName);
    if(!objToRemove.isNull())
    {
        removeObject(objToRemove);
    }
}

ISysOvrvObjPtr SystemOverview::getObject(const QString &objectName) const
{
    return systemOverviewObjectStore->getObj(objectName);
}

void SystemOverview::clear()
{
    systemOverviewObjectStore->clear();
}
