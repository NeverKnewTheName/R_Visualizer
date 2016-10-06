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

void SysOvrvObjectStore::addObject()
{
    SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog();
    connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
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
    updateObject(curObj);
}

void SysOvrvObjectStore::addObjToStore(SysOvrvObject *objToAdd)
{
    this->objectStore[objToAdd->getObjName()] = objToAdd;
    qDebug() << "GraphicsItem added: " << objToAdd->getObjName();
    disconnect(qobject_cast<SysOvrvObjectDialog *>(sender()), &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
    delete sender();
    emit this->objectAddedToStore(objToAdd);
}

void SysOvrvObjectStore::removeObject(SysOvrvObject *objToRmv)
{
    this->objectStore.remove(objToRmv->getObjName());
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
