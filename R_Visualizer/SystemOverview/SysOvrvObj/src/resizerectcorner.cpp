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

void ResizeRectCorner::setPosition(const QPointF &pos)
{
    /* qDebug() << __PRETTY_FUNCTION__ << " passed pos: " << pos; */
    /* qDebug() << "CornerPos: " << cornerPos; */
    switch(cornerPos)
    {
    case TopLeftCorner:
        setPos(pos.x()-cornerSize,pos.y()-cornerSize);
        /* setRect(pos.x()-cornerSize,pos.y()-cornerSize,cornerSize,cornerSize); */
        break;
    case BottomLeftCorner:
        setPos(pos.x()-cornerSize,pos.y());
        /* setRect(pos.x()-cornerSize,pos.y(),cornerSize,cornerSize); */
        break;
    case TopRightCorner:
        setPos(pos.x(),pos.y()-cornerSize);
        /* setRect(pos.x(),pos.y()-cornerSize,cornerSize,cornerSize); */
        break;
    case BottomRightCorner:
        setPos(pos.x(),pos.y());
        /* setRect(pos.x(),pos.y(),cornerSize,cornerSize); */
        break;
    default:
        /* setRect(0,0,cornerSize,cornerSize); */
        break;
    }
}

qreal ResizeRectCorner::getCornerSize()
{
    return cornerSize;
}



int ResizeRectCorner::type() const
{
    return Type;
}

