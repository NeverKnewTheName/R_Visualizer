#include "squaresysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

SquareSysOvrvObject::SquareSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(const SquareSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(SquareSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(other)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

SquareSysOvrvObject::SquareSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

SquareSysOvrvObject::~SquareSysOvrvObject()
{
}

void SquareSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
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
