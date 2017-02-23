#include "resizerectcorner.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPainter>

#include "resizeablegraphicsitem.h"

#include <QDebug>

ResizeRectCorner::ResizeRectCorner(const CornerPos cornerPos, const qreal size, ResizableGraphicsItem *parent) :
    QGraphicsRectItem(QRectF(0,0,size,size), parent),
    cornerPos(cornerPos),
    cornerSize(size)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    /* qDebug() << __PRETTY_FUNCTION__ << " CornerPos: " << cornerPos << " size: " << cornerSize; */
}

ResizeRectCorner::ResizeRectCorner(const ResizeRectCorner &other) :
    QGraphicsRectItem(other.parentItem()),
    cornerPos(other.cornerPos),
    cornerSize(other.cornerSize)
{
    setFlags(other.flags());
    setAcceptHoverEvents(other.acceptHoverEvents());
    
    /* qDebug() << __PRETTY_FUNCTION__ << " CornerPos: " << cornerPos << " size: " << cornerSize; */
}

void ResizeRectCorner::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
}

void ResizeRectCorner::setCornerPos(ResizeRectCorner::CornerPos cornerPos)
{
    this->cornerPos = cornerPos;
}

void ResizeRectCorner::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ResizableGraphicsItem *parentToResize = dynamic_cast<ResizableGraphicsItem*>(parentItem());
    if(parentToResize == Q_NULLPTR)
    {
        return;
    }

    qreal distX = event->pos().x() - event->lastPos().x();
    qreal distY = event->pos().y() - event->lastPos().y();

    parentToResize->resize(cornerPos, distX, distY);
}

void ResizeRectCorner::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::SizeAllCursor));
}

void ResizeRectCorner::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}

ResizeRectCorner::CornerPos ResizeRectCorner::getCornerPos() const
{
    return cornerPos;
}

void ResizeRectCorner::setCornerSize(const qreal &value)
{
    cornerSize = value;
}

void ResizeRectCorner::updatePosition()
{
    ResizableGraphicsItem *parent = dynamic_cast<ResizableGraphicsItem *>(parentItem());

    if(parent == Q_NULLPTR)
    {
        return;
    }

    const QRectF &parentBoundingRect = parent->boundingRect();

    switch(cornerPos)
    {
    case TopLeftCorner:
        {
            const QPointF &pos = parentBoundingRect.topLeft();
            setPos(pos.x()-cornerSize,pos.y()-cornerSize);
        }
        break;
    case BottomLeftCorner:
        {
            const QPointF &pos = parentBoundingRect.bottomLeft();
            setPos(pos.x()-cornerSize,pos.y());
        }
        break;
    case TopRightCorner:
        {
            const QPointF &pos = parentBoundingRect.topRight();
            setPos(pos.x(),pos.y()-cornerSize);
        }
        break;
    case BottomRightCorner:
        {
            const QPointF &pos = parentBoundingRect.bottomRight();
            setPos(pos.x(),pos.y());
        }
        break;
    default:
        /* setRect(0,0,cornerSize,cornerSize); */
        break;
    }

    update();
}

qreal ResizeRectCorner::getCornerSize()
{
    return cornerSize;
}



int ResizeRectCorner::type() const
{
    return Type;
}

