#include "resizeablegraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

ResizableGraphicsItem::ResizableGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    resizeCorners(10, this),
    resizeEnabled(false)
{
    /* initResizeCorners(); */
}

ResizableGraphicsItem::ResizableGraphicsItem(const ResizableGraphicsItem &other) :
    QGraphicsItem(other.parentItem()),
    resizeCorners(other.resizeCorners),
    resizeEnabled(other.resizeEnabled)
{
    resizeCorners.setParentItem(this);
}

ResizableGraphicsItem::ResizableGraphicsItem(ResizableGraphicsItem &&other) :
    QGraphicsItem(other.parentItem()),
    resizeCorners(std::move(other.resizeCorners)),
    resizeEnabled(other.resizeEnabled)
{
    resizeCorners.setParentItem(this);
}

ResizableGraphicsItem::~ResizableGraphicsItem()
{

}

void ResizableGraphicsItem::update(const QRectF &rect)
{
    QGraphicsItem::update(rect);
    resizeCorners.update(rect);
}

/* QRectF ResizableGraphicsItem::boundingRect() const */
/* { */
/* } */

/* void ResizableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) */
/* { */
/*     /1* QGraphicsItem::paint(painter, option, widget); *1/ */
/* } */

void ResizableGraphicsItem::resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y)
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
    case ResizeRectCorner::TopLeftCorner:
        newWidth = oldWidth - x;
        newHeight = oldHeigth - y;
        distX = x;
        distY = y;
        break;
    case ResizeRectCorner::BottomLeftCorner:
        newWidth = oldWidth - x;
        distX = x;
        newHeight = oldHeigth + y;
        break;
    case ResizeRectCorner::TopRightCorner:
        newWidth = oldWidth + x;
        newHeight = oldHeigth - y;
        distY = y;
        break;
    case ResizeRectCorner::BottomRightCorner:
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
    update();
}

void ResizableGraphicsItem::enableResizing(bool isOn)
{
    resizeEnabled = isOn;
    resizeCorners.setVisible(isOn);
}

bool ResizableGraphicsItem::getResizeEnabled() const
{
    return resizeEnabled;
}

void ResizableGraphicsItem::initResizeCorners()
{
    //DEPRECATED
}

