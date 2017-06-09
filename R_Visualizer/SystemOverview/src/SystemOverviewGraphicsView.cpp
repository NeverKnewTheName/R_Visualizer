#include "SystemOverviewGraphicsView.h"

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "ISystemOverviewObject.h"

#include <QDebug>

SystemOverviewGraphicsView::SystemOverviewGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

}


void SystemOverviewGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *sysOvrvContextMenu = new QMenu(this);
    QPointF currentMousePos = mapToScene(event->pos());

    ISystemOverviewObject *objectAtMousePos = qgraphicsitem_cast<ISystemOverviewObject*>(itemAt(event->pos()));

    if(objectAtMousePos == Q_NULLPTR)
    {
        // There is no object at the current mouse position
        QAction *actionAdd = sysOvrvContextMenu->addAction("Add Object");
        connect(
                    actionAdd,
                    &QAction::triggered,
                    [=](){
                            qDebug() << "Add Object here: " << currentMousePos;
                            emit sgnl_RequestAddObject(currentMousePos);
                        }
                    );
    }
    else
    {
        // There is an object at the current mouse position
        while(objectAtMousePos->parentItem() != Q_NULLPTR)
        {
            objectAtMousePos = qgraphicsitem_cast<ISystemOverviewObject*>(objectAtMousePos->parentItem());
        }

        QAction *actionRemove = sysOvrvContextMenu->addAction("Remove Object");
        QAction *actionEdit = sysOvrvContextMenu->addAction("Edit Object");

        connect(
                actionRemove,
                &QAction::triggered,
                [=](){
                    qDebug() << "Remove Object at: " << currentMousePos;
                    emit sgnl_RequestRemoveObject(objectAtMousePos);
                    }
                );
        connect(
                actionEdit,
                &QAction::triggered,
                [=](){
                    qDebug() << "Edit Object at: " << currentMousePos;
                    emit sgnl_RequestEditObject(objectAtMousePos);
                    }
                );
    }

    sysOvrvContextMenu->setAttribute(Qt::WA_DeleteOnClose);
    sysOvrvContextMenu->exec(event->globalPos());
}
