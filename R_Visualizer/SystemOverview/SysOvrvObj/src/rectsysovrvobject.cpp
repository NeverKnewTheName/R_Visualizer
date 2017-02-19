#include "rectsysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

RectSysOvrvObject::RectSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObject(parent)
{
}

RectSysOvrvObject::RectSysOvrvObject(const RectSysOvrvObject &other) :
    SysOvrvObject(other)
{
}

RectSysOvrvObject::RectSysOvrvObject(RectSysOvrvObject &&other) :
    SysOvrvObject(other)
{
}

RectSysOvrvObject::RectSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObject(original)
{
}

RectSysOvrvObject::RectSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObject(original)
{
}

RectSysOvrvObject::~RectSysOvrvObject()
{
}

void RectSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObject::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getMyColor());
    painter->save();

    painter->setBrush(colorBrush);
    painter->drawRect(boundRect);

    painter->restore();
}

SysOvrvObject::ObjShapeType RectSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Rectangle;
}

