#include "sysoverviewgraphicsview.h"

#include <QMenu>
#include <QContextMenuEvent>

SysOverviewGraphicsView::SysOverviewGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    sysOvrvObjStore = new SysOvrvObjectStore(this);

}

void SysOverviewGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction * actionAdd = menu.addAction("Add Object");
    QAction * actionRmv = menu.addAction("Remove Object");
    QAction * actionUpdt = menu.addAction("Update Object");

    connect(actionAdd, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::addObject);

    menu.exec(event->globalPos());
}
