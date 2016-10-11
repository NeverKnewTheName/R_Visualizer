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
        QAction * actionRmv = menu.addAction("Remove Object");
        QAction * actionUpdt = menu.addAction("Update Object");
        connect(actionRmv, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::rmvObject);
        connect(actionUpdt, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::updtObject);
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
