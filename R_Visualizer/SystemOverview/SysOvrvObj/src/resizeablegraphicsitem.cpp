#include "resizeablegraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

ResizableGraphicsItem::ResizableGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    resizeCorners{
        ResizeRectCorner(ResizeRectCorner::topLeftCorner, 10, this),
        ResizeRectCorner(ResizeRectCorner::bottomLeftCorner, 10, this),
        ResizeRectCorner(ResizeRectCorner::topRightCorner, 10, this),
        ResizeRectCorner(ResizeRectCorner::bottomRightCorner, 10, this)
        },
    resizeEnabled(true)
{
}

ResizableGraphicsItem::~ResizableGraphicsItem()
{

}

/* QRectF ResizableGraphicsItem::boundingRect() const */
/* { */
/* } */

/* void ResizableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) */
/* { */
/*     /1* QGraphicsItem::paint(painter, option, widget); *1/ */
/* } */

void ResizableGraphicsItem::resize(ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y)
{
    if(!resizeEnabled)
    {
        //Currently not in resize mode...
        //This should never happen!
        return;
    }
    qreal distX = 0;
    qreal distY = 0;

    qreal oldWidth = getWidth();
    qreal oldHeigth = getHeight();
    qreal newWidth = 0;
    qreal newHeight = 0;

    switch(AnchorPoint)
    {
    case ResizeRectCorner::topLeftCorner:
        newWidth = oldWidth - x;
        newHeight = oldHeigth - y;
        distX = x;
        distY = y;
        break;
    case ResizeRectCorner::bottomLeftCorner:
        newWidth = oldWidth - x;
        distX = x;
        newHeight = oldHeigth + y;
        break;
    case ResizeRectCorner::topRightCorner:
        newWidth = oldWidth + x;
        newHeight = oldHeigth - y;
        distY = y;
        break;
    case ResizeRectCorner::bottomRightCorner:
        newWidth = oldWidth + x;
        newHeight = oldHeigth + y;
        break;
    default:
        distX = distY = newWidth = newHeight = 0;
        qDebug() << "INVALID CORNER?!";
    }

    prepareGeometryChange();
    if(newWidth <= 0.1)
    {
        distX = 0;
        newWidth = 0;
    }
    if(newWidth > 0 )
    {
        setWidth(newWidth);
    }
    if(newHeight <= 0.1)
    {
        distY = 0;
        newHeight = 0;
    }
    if(newHeight > 0 )
    {
        setHeight(newHeight);
    }

    moveBy(distX,distY);
    initResizeCorners(boundingRect());
}

void ResizableGraphicsItem::enableResizing(bool isOn)
{
    resizeEnabled = isOn;
    if(isOn)
    {
       for(ResizeRectCorner &corner : resizeCorners)
       {
           corner.setVisible(true);
       }
    }
    else
    {
        for(ResizeRectCorner &corner : resizeCorners)
        {
            corner.setVisible(false);
        }
    }
}

bool ResizableGraphicsItem::getResizeEnabled() const
{
    return resizeEnabled;
}

void ResizableGraphicsItem::initResizeCorners(const QRectF &boundingRect)
{
    resizeCorners[0].setPosition(boundingRect.topLeft());
    resizeCorners[1].setPosition(boundingRect.bottomLeft());
    resizeCorners[2].setPosition(boundingRect.topRight());
    resizeCorners[3].setPosition(boundingRect.bottomRight());
}

