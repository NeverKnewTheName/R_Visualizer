#include "ellipsesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

EllipseSysOvrvObject::EllipseSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObject(parent)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(const EllipseSysOvrvObject &other) :
    SysOvrvObject(other)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(EllipseSysOvrvObject &&other) :
    SysOvrvObject(other)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObject(original)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObject(original)
{
}

EllipseSysOvrvObject::~EllipseSysOvrvObject()
{
}

void EllipseSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObject::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getMyColor());
    painter->save();

    painter->setBrush(colorBrush);
    painter->drawEllipse(boundRect);

    painter->restore();
}

SysOvrvObject::ObjShapeType EllipseSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Ellipse;
}

