#include "sysoverviewgraphicsview.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QPointF>
#include "sysovrvobject.h"

#include <QDebug>

SysOverviewGraphicsView::SysOverviewGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    editingEnabled(false)
{
}

void SysOverviewGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    if(!editingEnabled)
    {
        return;
    }
    QMenu menu(this);
    qDebug() << "Pos: " << event->pos();
    QPointF currentMousePos = mapToScene(event->pos());
    qDebug() << "CurMousePos mapped: " << currentMousePos;
    SysOvrvObject *currentObject = qgraphicsitem_cast<SysOvrvObject*>(itemAt(event->pos()));

    if(currentObject == Q_NULLPTR)
    {
        QAction * actionAdd = menu.addAction("Add Object");
        connect(actionAdd, &QAction::triggered, [=](){
                emit sgnl_addObjRequest(currentMousePos);
                });
    }
    else
    {
        while(currentObject->parentItem() != Q_NULLPTR)
        {
            // Get to top level object!
            currentObject = qgraphicsitem_cast<SysOvrvObject*>(currentObject->parentItem());
        }

        QAction * actionRmv = menu.addAction("Remove Object");
        QAction * actionEdit = menu.addAction("Edit Object");
        QAction * actionDuplctObj = menu.addAction("Duplicate Object");

        QAction::connect(actionRmv, &QAction::triggered, [=](){
                emit sgnl_removeObjRequest(currentObject);
        } );
        QAction::connect(actionEdit, &QAction::triggered, [=](){
                emit sgnl_updateObjRequest(currentObject);
        } );
        QAction::connect(actionDuplctObj, &QAction::triggered, [=](){
                emit sgnl_duplicateObjRequest(currentObject);
        } );
    }

    menu.exec(event->globalPos());
}

SysOvrvObject *SysOverviewGraphicsView::getObjAtPos(const QPointF &pos) const
{
    SysOvrvObject *currentObject = itemAt(pos);

    while(currentObject != Q_NULLPTR)
    {
        // Get to top level object!
        SysOvrvObject *tempObj = qgraphicsitem_cast<SysOvrvObject*>(currentObject->parentItem());

        if(tempObj == Q_NULLPTR)
        {
            break;
        }

        currentObject = tempObj;
    }

    return currentObject;
}

void SysOverviewGraphicsView::enableEditing(const bool enable)
{
    editingEnabled = enable;
}

