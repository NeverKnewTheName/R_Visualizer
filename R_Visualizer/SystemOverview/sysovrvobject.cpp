#include "sysovrvobject.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <QDebug>

SysOvrvObject::SysOvrvObject()
{
    pressed = false;
    myColor = QColor(Qt::gray);
    shapeType = 0;
    this->update();
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
}

QRectF SysOvrvObject::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void SysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(myColor);

    if(pressed)
    {
        brush.setColor(myColor.darker());
    }

    painter->setBrush(brush);

    switch(shapeType)
    {
    case 0: // Rect
        painter->drawRect(rect);
        break;
    case 1: // Square
        rect.setY(rect.x());
        painter->drawRect(rect);
        break;
    case 2: // Circle
        painter->drawEllipse(rect);
        break;
    case 3: // Triangle
    {
        QPainterPath path;
        QPointF rectTopMiddle((rect.right() - rect.left()) / 2, rect.top());
        path.moveTo(rectTopMiddle);
        path.lineTo(rect.right(), rect.bottom());
        path.lineTo(rect.left(), rect.bottom());
        path.lineTo(rectTopMiddle);
        painter->drawPath(path);
    }
        break;
    }
}

QHash<QString, SysOvrvObject *> SysOvrvObject::getObjStore() const
{
    return objStore;
}

void SysOvrvObject::setObjStore(const QHash<QString, SysOvrvObject *> &value)
{
    objStore = value;
}

QString SysOvrvObject::getObjName() const
{
    return objName;
}

void SysOvrvObject::setObjName(const QString &value)
{
    objName = value;
}

void SysOvrvObject::setShape(int shape)
{
    shapeType = shape;
    this->update();
}

int SysOvrvObject::getShape() const
{
    return shapeType;
}

void SysOvrvObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal distX = event->pos().x() - event->lastPos().x();
    qreal distY = event->pos().y() - event->lastPos().y();
    moveBy(distX,distY);

}
