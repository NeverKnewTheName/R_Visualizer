#include "ResizeRectCorner.h"

#include "ISysOverviewObjectResizeManager.h"
#include <QGraphicsSceneMouseEvent>

#include <QCursor>

#include <QDebug>

int ResizeRectCorner::constructCount = 0;

ResizeRectCorner::ResizeRectCorner() :
    QGraphicsRectItem(QRectF(0,0,10,10)),
    resizeManager(Q_NULLPTR),
    cornerPos(CornerPos_TopLeft)
{
    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemIsFocusable,false);
//    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setAcceptHoverEvents(true);

    constructCount++;
    qDebug() << "ResizeRectCorner -- Default Constructor: " << constructCount;
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
    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemIsFocusable,false);
//    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setAcceptHoverEvents(true);

    constructCount++;
    qDebug() << "ResizeRectCorner -- Constructor: " << constructCount;
}

ResizeRectCorner::ResizeRectCorner(
        const ResizeRectCorner &copy
        ) :
    QGraphicsRectItem(QRectF(copy.x(),copy.y(),10,10),copy.parentItem()),
    resizeManager(copy.resizeManager),
    cornerPos(copy.cornerPos)
{
    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemIsFocusable,false);
//    setFlag(QGraphicsItem::ItemIsSelectable,false);
    setAcceptHoverEvents(true);

    constructCount++;
    qDebug() << "ResizeRectCorner -- COPY: " << constructCount;
}

ResizeRectCorner::~ResizeRectCorner()
{
    constructCount--;
    setParentItem(Q_NULLPTR);
    qDebug() << "ResizeRectCorner -- DESTRUCTOR: " << constructCount;
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
        break;
    case CornerPos_BottomRight:
        break;
    default:
        break;
    }

    setPos(calcPos);
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
    setCursor(QCursor(Qt::SizeAllCursor));
}

void ResizeRectCorner::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}
