#include "rectsysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

RectSysOvrvObject::RectSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

RectSysOvrvObject::RectSysOvrvObject(const RectSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

RectSysOvrvObject::RectSysOvrvObject(RectSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(other)
{
}

RectSysOvrvObject::RectSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

RectSysOvrvObject::RectSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

RectSysOvrvObject::~RectSysOvrvObject()
{
}

void RectSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
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

