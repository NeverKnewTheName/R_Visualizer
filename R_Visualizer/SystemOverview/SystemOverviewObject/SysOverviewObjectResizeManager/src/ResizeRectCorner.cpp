#include "ResizeRectCorner.h"

#include "ISysOverviewObjectResizeManager.h"
#include <QGraphicsSceneMouseEvent>

ResizeRectCorner::ResizeRectCorner() :
    QGraphicsRectItem(QRectF(0,0,10,10)),
    resizeManager(Q_NULLPTR),
    cornerPos(CornerPos_TopLeft)
{
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

ResizeRectCorner::ResizeRectCorner(
        const CornerPos cornerPos,
        ISysOverviewObjectResizeManager *resizeManager,
        QGraphicsItem *parent
        ) :
    QGraphicsRectItem(QRectF(0,0,10,10),parent),
    resizeManager(resizeManager),
    cornerPos(cornerPos)
{
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

ResizeRectCorner::ResizeRectCorner(
        const ResizeRectCorner &copy
        ) :
    QGraphicsRectItem(QRectF(copy.x(),copy.y(),10,10),copy.parentItem()),
    resizeManager(copy.resizeManager),
    cornerPos(copy.cornerPos)
{
}

void ResizeRectCorner::setPosition(const QPointF &pos)
{
    QPointF calcPos(pos);

    switch (cornerPos) {
    case CornerPos_TopLeft:
        calcPos.setX(calcPos.x()-10);
        calcPos.setY(calcPos.y()-10);
        break;
    case CornerPos_TopRight:
        calcPos.setY(calcPos.y()-10);
        break;
    case CornerPos_BottomLeft:
        calcPos.setX(calcPos.x()-10);
        calcPos.setY(calcPos.y()+10);
        break;
    case CornerPos_BottomRight:
        calcPos.setY(calcPos.y()+10);
        break;
    default:
        break;
    }

    setPos(pos);
}

void ResizeRectCorner::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(resizeManager != Q_NULLPTR)
    {
        qreal distX = event->pos().x() - event->lastPos().x();
        qreal distY = event->pos().y() - event->lastPos().y();

        resizeManager->resize(cornerPos, distX, distY);
    }
}

void ResizeRectCorner::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

}

void ResizeRectCorner::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

}
