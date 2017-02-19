#include "squaresysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

SquareSysOvrvObject::SquareSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObject(parent)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(const SquareSysOvrvObject &other) :
    SysOvrvObject(other)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(SquareSysOvrvObject &&other) :
    SysOvrvObject(other)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObject(original)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObject(original)
{
}

SquareSysOvrvObject::~SquareSysOvrvObject()
{
}

void SquareSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObject::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getMyColor());

    painter->save();

    painter->setBrush(colorBrush);
    painter->drawRect(boundRect);

    painter->restore();
}

SysOvrvObject::ObjShapeType SquareSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Square;
}
