#include "sysovrvobjectstore.h"

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

void SysOvrvObjectStore::addObjToStore(SysOvrvObject *objToAdd)
{
    this->objectStore[objToAdd->getObjName()] = objToAdd;
    qDebug() << "GraphicsItem added: " << objToAdd->getObjName();
    disconnect(qobject_cast<SysOvrvObjectDialog *>(sender()), &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
    delete sender();
}

void SysOvrvObjectStore::removeObject(QString &objectName)
{
    SysOvrvObject *objToRemove = this->objectStore.value(objectName);
    this->objectStore.remove(objectName);
    if(objToRemove != Q_NULLPTR) delete objToRemove;
}

void SysOvrvObjectStore::updateObject(QString &objectName)
{
    SysOvrvObject *objToEdit = this->objectStore.value(objectName);
    if(objToEdit != Q_NULLPTR)
    {
        SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog();
        connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectStore::addObjToStore);
        addSysOvrvObjectDialog->exec();
    }
}
