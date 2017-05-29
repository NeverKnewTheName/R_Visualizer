#include "sysoverviewgraphicsview.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QPointF>
#include "ISystemOverviewObject.h"

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
    ISystemOverviewObject *currentObject =
        qgraphicsitem_cast<ISystemOverviewObject*>(
                itemAt(event->pos())
                );

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
            currentObject =
                qgraphicsitem_cast<ISystemOverviewObject*>(
                        currentObject->parentItem()
                        );
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

ISystemOverviewObject *SysOverviewGraphicsView::getObjAtPos(const QPointF &pos) const
{
    ISystemOverviewObject *currentObject =
        qgraphicsitem_cast<ISystemOverviewObject*>(
                itemAt(mapFromScene(pos))
                );

    while(currentObject != Q_NULLPTR)
    {
        // Get to top level object!
        ISystemOverviewObject *tempObj =
            qgraphicsitem_cast<ISystemOverviewObject*>(
                    currentObject->parentItem()
                    );

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
