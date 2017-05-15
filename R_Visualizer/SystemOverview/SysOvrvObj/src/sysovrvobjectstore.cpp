#include "sysovrvobjectstore.h"

#include "sysoverviewgraphicsview.h"
#include "sysovrvobjectdialog.h"

#include <QDebug>

SysOvrvObjectStore::SysOvrvObjectStore(QObject *parent) : QObject(parent)
{

}

QVector<SysOvrvObject *> SysOvrvObjectStore::getObjectStore() const
{
    return objectStore;
}

void SysOvrvObjectStore::addMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj)
{
    TriggerIdentifier triggerIdentifier(id,code);
    QVector<SysOvrvObject*>objVector = objectTriggerStore[triggerIdentifier];
    if(objVector.contains(relatedSysOvrvObj))
    {
        qDebug() << "The objectTriggerStore does already contain the SysOvrvObject: " << relatedSysOvrvObj->getObjName()
                << " for the trigger with id " << id << " and code " << code;
        return;
    }
    objVector.append(relatedSysOvrvObj);
}

void SysOvrvObjectStore::removeMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj)
{
    TriggerIdentifier triggerIdentifier(id,code);
    QVector<SysOvrvObject*>objVector = objectTriggerStore[triggerIdentifier];

    if(!objVector.contains(relatedSysOvrvObj))
    {
        qDebug() << "objectTriggerStore does not contain the SysOvrvObject: " << relatedSysOvrvObj->getObjName()
                << " for the trigger with id " << id << " and code " << code;
        return;
    }

    objVector.removeAll(relatedSysOvrvObj);

    if(objVector.isEmpty())
    {
        qDebug() << "The objectVector is empty, therefore remove id " << id << " and code " << code 
                 << " from the objectTriggerStore";
        objectTriggerStore.remove(triggerIdentifier);
    }
}

void SysOvrvObjectStore::addObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        qDebug() << "Nullptr passed to addObject!";
        return;
    }
    if(objectStore.contains(obj))
    {
        qDebug() << "ObjectStore already contains: " << obj->getObjName();
        return;
    }
    objectStore.append(obj);

    emit sgnl_objectAddedToStore(obj);
}

void SysOvrvObjectStore::removeObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        qDebug() << "Nullptr passed to rmvObject!";
        return;
    }
    if(objectStore.contains(obj))
    {
        qDebug() << "ObjectStore does not contain: " << obj->getObjName();
        return;
    }
    objectStore.removeAll(obj);

    emit sgnl_objectRemovedFromStore(obj);
    /* removeObject(curObj); */
    //ToTHINK DOES NOT DELETE OBJECT!!!
}

void SysOvrvObjectStore::updateObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        qDebug() << "Nullptr passed to updtObject!";
        return;
    }
//    QList<MsgIDType> triggerIDs = curObj->getTriggerIDs();
//    for(const MsgIDType &id : triggerIDs)
//    {
//        QList<MsgCodeType> triggerCodes = curObj->getTriggerCodesToID(id);
//        for(const MsgCodeType &code : triggerCodes)
//        {
//            removeMesageToWatch(id, code, curObj);
//        }
//    }
    /* curObj->enableResizing(true); */
    /* curObjPos = curObj->pos(); */
    /* updateObject(curObj); */
}

/* void SysOvrvObjectStore::duplicateObject() */
/* { */
    /* SysOvrvObject *curObj = static_cast<SysOverviewGraphicsView*>(parent())->getCurrentObject(); */
    /* if(curObj == NULL) */
    /*     return; */
    /* curObjPos = curObj->pos(); */
    /* SysOvrvObject *newObj = curObj->duplicate(); */
    /* newObj->setAsChild(false); */
    /* this->objectStore[newObj->getHashedName()] = newObj; */
    /* qDebug() << "GraphicsItem added: " << newObj->getObjName(); */

    /* newObj->enableResizing(false); */
    /* emit this->objectAddedToStore(newObj,curObjPos); */
/* } */

/* void SysOvrvObjectStore::addObjToStore(SysOvrvObject *objToAdd) */
/* { */
    /* this->objectStore[objToAdd->getHashedName()] = objToAdd; */
    /* qDebug() << "GraphicsItem added: " << objToAdd->getObjName(); */
    /* disconnect(qobject_cast<SysOvrvObjectDialog *>(sender()), &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore); */
    /* delete sender(); */
/* //    QList<MsgIDType> triggerIDs = objToAdd->getTriggerIDs(); */
/* //    for(const MsgIDType &id : triggerIDs) */
/* //    { */
/* //        QList<MsgCodeType> triggerCodes = objToAdd->getTriggerCodesToID(id); */
/* //        for(const MsgCodeType &code : triggerCodes) */
/* //        { */
/* //            addMesageToWatch(id, code, objToAdd); */
/* //        } */
/* //    } */
    /* objToAdd->enableResizing(false); */
    /* emit this->objectAddedToStore(objToAdd,curObjPos); */
/* } */

/* void SysOvrvObjectStore::removeObject(SysOvrvObject *objToRmv) */
/* { */
    /* this->objectStore.remove(objToRmv->getHashedName()); */
/* //    QList<MsgIDType> triggerIDs = objToRmv->getTriggerIDs(); */
/* //    for(const MsgIDType &id : triggerIDs) */
/* //    { */
/* //        QList<MsgCodeType> triggerCodes = objToRmv->getTriggerCodesToID(id); */
/* //        for(const MsgCodeType &code : triggerCodes) */
/* //        { */
/* //            removeMesageToWatch(id, code, objToRmv); */
/* //        } */
/* //    } */
    /* emit this->objectRemovedFromStore(objToRmv); */
/* } */

/* void SysOvrvObjectStore::updateObject(SysOvrvObject *objToUpdt) */
/* { */
    /* if( objToUpdt != Q_NULLPTR) */
    /* { */
    /*     removeObject(objToUpdt); */
    /*     SysOvrvObjectDialog addSysOvrvObjectDialog(objToUpdt); */
    /*     connect(&addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore); */
    /*     addSysOvrvObjectDialog.exec(); */
    /* } */
/* } */

void SysOvrvObjectStore::slt_receiveMessage(const Msg &newMsg)
{
    const MsgIDType id = newMsg.getMsgID();
    const MsgCodeType code = newMsg.getMsgCode();
    const TriggerIdentifier triggerIdentifier(id,code);

    qDebug() << "SysOvrvObjectStore::receiveMessage " << id << " " << code;

    //are there entries associated with the given id
    if(!objectTriggerStore.contains(triggerIdentifier))
    {
        qDebug() << "ojbectTriggerStore does not contain triggers for id " << id << " and code " << code;
        return;
    }

    const QVector<SysOvrvObject *> &relatedSysOvrvObjs = objectTriggerStore[triggerIdentifier];

//    for(SysOvrvObject *relatedSysOvrvObj : relatedSysOvrvObjs)
//    {
//        qDebug() << "Trigger from ParserStore: " << relatedSysOvrvObj->getObjName();
//        relatedSysOvrvObj->msgReceived(id,code,canData);
//    }

    // // // DEBUG // // //
//    for(SysOvrvObject *obj : this->objectStore.values())
//    {
//        qDebug() << "Trigger: " << obj->getObjName();
//        obj->msgReceived(id, code, canData);
//    }
    // // // DEBUG // // //
}

void SysOvrvObjectStore::slt_addObject(SysOvrvObject *objToAdd)
{
    addObject(objToAdd);
}

void SysOvrvObjectStore::slt_removeObject(SysOvrvObject *objToRmv)
{
    removeObject(objToRmv);
}

void SysOvrvObjectStore::slt_updateObject(SysOvrvObject *objToUpdt)
{
    updateObject(objToUpdt);
}
