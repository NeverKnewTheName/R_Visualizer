#include "circlesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

CircleSysOvrvObject::CircleSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObject(parent)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(const CircleSysOvrvObject &other) :
    SysOvrvObject(other)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(CircleSysOvrvObject &&other) :
    SysOvrvObject(other)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObject(original)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObject(original)
{
}

CircleSysOvrvObject::~CircleSysOvrvObject()
{
}

void CircleSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObject::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getMyColor());
    painter->save();

    painter->setBrush(colorBrush);
    painter->drawEllipse(boundRect);

    painter->restore();
}

SysOvrvObject::ObjShapeType CircleSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Circle;
}

