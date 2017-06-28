#include "resizerectcorner.h"
#include "sysovrvobject.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <QDebug>

ResizeRectCorner::ResizeRectCorner(CornerPos cornerPos, qreal size, ResizableGraphicsItem *parent) :
    QGraphicsRectItem(parent),
    cornerPos(cornerPos),
    cornerSize(size)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

ResizeRectCorner::ResizeRectCorner(ResizeRectCorner &&ToMove) :
    QGraphicsRectItem(ToMove.parentItem()),
    cornerPos(ToMove.cornerPos),
    cornerSize(ToMove.cornerSize)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
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
    case topLeftCorner:
        setRect(pos.x()-cornerSize,pos.y()-cornerSize,cornerSize,cornerSize);
        break;
    case bottomLeftCorner:
        setRect(pos.x()-cornerSize,pos.y(),cornerSize,cornerSize);
        break;
    case topRightCorner:
        setRect(pos.x(),pos.y()-cornerSize,cornerSize,cornerSize);
        break;
    case bottomRightCorner:
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


int ResizeRectCorner::type() const
{
    return Type;
}

QRectF ResizableGraphicsItem::boundingRect() const
{
}

void ResizableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

int ResizableGraphicsItem::type() const
{
    return Type;
}
