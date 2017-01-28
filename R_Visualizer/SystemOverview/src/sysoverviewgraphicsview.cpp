#include "sysoverviewgraphicsview.h"

#include <QMenu>
#include <QContextMenuEvent>
#include "sysovrvobject.h"

#include <QDebug>

SysOverviewGraphicsView::SysOverviewGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    currentObject(NULL)
{
    sysOvrvObjStore = new SysOvrvObjectStore(this);
}

void SysOverviewGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    qDebug() << "Pos: " << event->pos();
    currentMousePos = mapToScene(event->pos());
    qDebug() << "CurMousePos mapped: " << currentMousePos;
    currentObject = qgraphicsitem_cast<SysOvrvObject*>(itemAt(event->pos()));

    if(currentObject == NULL)
    {
        QAction * actionAdd = menu.addAction("Add Object");
        connect(actionAdd, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::addObject);
    }
    else
    {
        while(currentObject->parentItem() != NULL)
            currentObject = qgraphicsitem_cast<SysOvrvObject*>(currentObject->parentItem());

        QAction * actionRmv = menu.addAction("Remove Object");
        QAction * actionEdit = menu.addAction("Edit Object");
        QAction * actionDuplctObj = menu.addAction("Duplicate Object");
//        connect(actionRmv, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::rmvObject);
        QAction::connect(actionRmv, &QAction::triggered, [this] () {
            sysOvrvObjStore->removeObject(currentObject);
        } );
//        connect(actionEdit, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::updtObject);
        QAction::connect(actionEdit, &QAction::triggered, [this] () {
            sysOvrvObjStore->updateObject(currentObject);
        } );
//        connect(actionDuplctObj, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::duplicateObject);
        QAction::connect(actionDuplctObj, &QAction::triggered, [this] () {
            sysOvrvObjStore->duplicateObject();
        } );
    }

    menu.exec(event->globalPos());
}

SysOvrvObject *SysOverviewGraphicsView::getCurrentObject() const
{
    return currentObject;
}

SysOvrvObjectStore *SysOverviewGraphicsView::getObjectStore() const
{
    return sysOvrvObjStore;
}

const QPointF &SysOverviewGraphicsView::GetCurrentMousePos() const
{
    return currentMousePos;
}

