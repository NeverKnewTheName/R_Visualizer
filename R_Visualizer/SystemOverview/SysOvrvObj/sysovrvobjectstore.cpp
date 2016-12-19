#include "sysovrvobjectstore.h"

#include "sysoverviewgraphicsview.h"
#include "sysovrvobjectdialog.h"

#include <QDebug>

SysOvrvObjectStore::SysOvrvObjectStore(QObject *parent) : QObject(parent)
{

}

QHash<QString, SysOvrvObject *> SysOvrvObjectStore::getObjectStore() const
{
    return objectStore;
}

void SysOvrvObjectStore::addMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj)
{
    QVector<SysOvrvObject*>objVector = msgParserStore[id][code];
    if(objVector.contains(relatedSysOvrvObj))
        return;
    objVector.append(relatedSysOvrvObj);
}

void SysOvrvObjectStore::removeMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj)
{
    QVector<SysOvrvObject*>objVector = msgParserStore[id][code];
    if(objVector.contains(relatedSysOvrvObj))
        return;
    objVector.removeAll(relatedSysOvrvObj);
    if(objVector.isEmpty())
        msgParserStore[id].remove(code);
    if(msgParserStore[id].isEmpty())
        msgParserStore.remove(id);
}

void SysOvrvObjectStore::addObject()
{
    SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog();
    connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
    curObjPos = static_cast<SysOverviewGraphicsView*>(parent())->GetCurrentMousePos();
    addSysOvrvObjectDialog->exec();
}

void SysOvrvObjectStore::rmvObject()
{
    SysOvrvObject *curObj = static_cast<SysOverviewGraphicsView*>(parent())->getCurrentObject();

    if(curObj == NULL)
        return;
    removeObject(curObj);
    delete curObj;
}

void SysOvrvObjectStore::updtObject()
{
    SysOvrvObject *curObj = static_cast<SysOverviewGraphicsView*>(parent())->getCurrentObject();

    if(curObj == NULL)
        return;
//    QList<MsgIDType> triggerIDs = curObj->getTriggerIDs();
//    for(const MsgIDType &id : triggerIDs)
//    {
//        QList<MsgCodeType> triggerCodes = curObj->getTriggerCodesToID(id);
//        for(const MsgCodeType &code : triggerCodes)
//        {
//            removeMesageToWatch(id, code, curObj);
//        }
//    }
    curObj->enableResizing(true);
    curObjPos = curObj->pos();
    updateObject(curObj);
}

void SysOvrvObjectStore::duplicateObject()
{
    SysOvrvObject *curObj = static_cast<SysOverviewGraphicsView*>(parent())->getCurrentObject();
    if(curObj == NULL)
        return;
    curObjPos = curObj->pos();
    SysOvrvObject *newObj = curObj->duplicate();
    newObj->setAsChild(false);
    this->objectStore[newObj->getHashedName()] = newObj;
    qDebug() << "GraphicsItem added: " << newObj->getObjName();

    newObj->enableResizing(false);
    emit this->objectAddedToStore(newObj,curObjPos);
}

void SysOvrvObjectStore::addObjToStore(SysOvrvObject *objToAdd)
{
    this->objectStore[objToAdd->getHashedName()] = objToAdd;
    qDebug() << "GraphicsItem added: " << objToAdd->getObjName();
    disconnect(qobject_cast<SysOvrvObjectDialog *>(sender()), &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
    delete sender();
//    QList<MsgIDType> triggerIDs = objToAdd->getTriggerIDs();
//    for(const MsgIDType &id : triggerIDs)
//    {
//        QList<MsgCodeType> triggerCodes = objToAdd->getTriggerCodesToID(id);
//        for(const MsgCodeType &code : triggerCodes)
//        {
//            addMesageToWatch(id, code, objToAdd);
//        }
//    }
    objToAdd->enableResizing(false);
    emit this->objectAddedToStore(objToAdd,curObjPos);
}

void SysOvrvObjectStore::removeObject(SysOvrvObject *objToRmv)
{
    this->objectStore.remove(objToRmv->getHashedName());
//    QList<MsgIDType> triggerIDs = objToRmv->getTriggerIDs();
//    for(const MsgIDType &id : triggerIDs)
//    {
//        QList<MsgCodeType> triggerCodes = objToRmv->getTriggerCodesToID(id);
//        for(const MsgCodeType &code : triggerCodes)
//        {
//            removeMesageToWatch(id, code, objToRmv);
//        }
//    }
    emit this->objectRemovedFromStore(objToRmv);
}

void SysOvrvObjectStore::updateObject(SysOvrvObject *objToUpdt)
{
    if( objToUpdt != Q_NULLPTR)
    {
        removeObject(objToUpdt);
        SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog(objToUpdt);
        connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
        addSysOvrvObjectDialog->exec();
    }
}

void SysOvrvObjectStore::receiveMessage(Data_PacketPtr ptr)
{

    QDateTime timeStamp = ptr->timestamp();
    const MsgIDType id = ptr->frame().ID_Standard;
    QByteArray canData = ptr->frame().data;

    const MsgCodeType code = canData.at(0);

    qDebug() << "SysOvrvObjectStore::receiveMessage " << id << " " << code;

    //are there entries associated with the given id
    if(!msgParserStore.contains(id))
        return;
    //are there entries associated with the given code
    if(!msgParserStore[id].contains(code))
        return;

    QVector<SysOvrvObject *> relatedSysOvrvObjs = msgParserStore[id][code];

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
