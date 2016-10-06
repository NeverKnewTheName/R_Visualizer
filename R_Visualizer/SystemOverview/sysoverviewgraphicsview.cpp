#include "sysoverviewgraphicsview.h"

#include <QMenu>
#include <QContextMenuEvent>
#include "sysovrvobject.h"

SysOverviewGraphicsView::SysOverviewGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    currentObject(NULL)
{
    sysOvrvObjStore = new SysOvrvObjectStore(this);
}

void SysOverviewGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction * actionAdd = menu.addAction("Add Object");
    QAction * actionRmv = menu.addAction("Remove Object");
    QAction * actionUpdt = menu.addAction("Update Object");

    currentObject = qgraphicsitem_cast<SysOvrvObject*>(itemAt(event->pos()));

    connect(actionAdd, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::addObject);
    connect(actionRmv, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::rmvObject);
    connect(actionUpdt, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::updtObject);

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
