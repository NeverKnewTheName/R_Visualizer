#include "resizerectcorner.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPainter>

#include "resizeablegraphicsitem.h"

#include <QDebug>

ResizeRectCorner::ResizeRectCorner(const CornerPos cornerPos, const qreal size, ResizableGraphicsItem *parent) :
    QGraphicsRectItem(parent),
    cornerPos(cornerPos),
    cornerSize(size)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

ResizeRectCorner::ResizeRectCorner(const ResizeRectCorner &other) :
    QGraphicsRectItem(other.parentItem()),
    cornerPos(std::move(other.cornerPos)),
    cornerSize(std::move(other.cornerSize))
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void ResizeRectCorner::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    painter->drawEllipse(QRectF(100,100,10,10));
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
    switch(cornerPos)
    {
    case TopLeftCorner:
        setRect(pos.x()-cornerSize,pos.y()-cornerSize,cornerSize,cornerSize);
        break;
    case BottomLeftCorner:
        setRect(pos.x()-cornerSize,pos.y(),cornerSize,cornerSize);
        break;
    case TopRightCorner:
        setRect(pos.x(),pos.y()-cornerSize,cornerSize,cornerSize);
        break;
    case BottomRightCorner:
        setRect(pos.x(),pos.y(),cornerSize,cornerSize);
        break;
    default:
        setRect(0,0,cornerSize,cornerSize);
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

