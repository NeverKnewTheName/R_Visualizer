#include "resizerectcorner.h"
#include "sysovrvobject.h"
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

ResizeRectCorner::ResizeRectCorner(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void ResizeRectCorner::setCornerPos(ResizeRectCorner::CornerPos cornerPos)
{
    this->cornerPos = cornerPos;
}

void ResizeRectCorner::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    SysOvrvObject *parentToResize = qgraphicsitem_cast<SysOvrvObject*>(parentItem());

    qreal distX = event->pos().x() - event->lastPos().x();
    qreal distY = event->pos().y() - event->lastPos().y();

    qreal newWidth;
    qreal factorWidth;
    qreal newHeight;
    qreal factorHeight;

    qDebug() << "Resizing distX: " << distX << " distY: " << distY << " cornerPos:" << cornerPos;

    switch(this->cornerPos)
    {
    case topLeftCorner:
        newWidth = parentToResize->getWidth()-distX;
        factorWidth = newWidth / parentToResize->getWidth();
        if(newWidth >= 0.1)
        {
            parentToResize->moveBy(distX, 0);
            parentToResize->adjustWidth(factorWidth);
        }

        newHeight = parentToResize->getHeight()-distY;
        factorHeight = newHeight / parentToResize->getHeight();
        if(newHeight >= 0.1)
        {
            parentToResize->moveBy(0, distY);
            parentToResize->adjustHeight(factorHeight);
        }
        break;
    case bottomLeftCorner:
        newWidth = parentToResize->getWidth()-distX;
        factorWidth = newWidth / parentToResize->getWidth();
        if(newWidth >= 0.1)
        {
            parentToResize->moveBy(distX, 0);
            parentToResize->adjustWidth(factorWidth);
        }

        newHeight = parentToResize->getHeight()+distY;
        factorHeight = newHeight / parentToResize->getHeight();
        parentToResize->adjustHeight(factorHeight);
        break;
    case topRightCorner:
        newWidth = parentToResize->getWidth()+distX;
        factorWidth = newWidth / parentToResize->getWidth();
        parentToResize->adjustWidth(factorWidth);

        newHeight = parentToResize->getHeight()-distY;
        factorHeight = newHeight / parentToResize->getHeight();
        if(newHeight >= 0.1)
        {
            parentToResize->moveBy(0, distY);
            parentToResize->adjustHeight(factorHeight);
        }
        break;
    case bottomRightCorner:
        newWidth = parentToResize->getWidth()+distX;
        factorWidth = newWidth / parentToResize->getWidth();
        parentToResize->adjustWidth(factorWidth);

        newHeight = parentToResize->getHeight()+distY;
        factorHeight = newHeight / parentToResize->getHeight();
        parentToResize->adjustHeight(factorHeight);
        break;
    default:
        qDebug() << "INVALID CORNER?!";
    }

    //    QGraphicsRectItem::mouseMoveEvent(event);
}
