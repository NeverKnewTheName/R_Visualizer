#include "ellipsesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

EllipseSysOvrvObject::EllipseSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(const EllipseSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(EllipseSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(other)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

EllipseSysOvrvObject::EllipseSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

EllipseSysOvrvObject::~EllipseSysOvrvObject()
{
}

void EllipseSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
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

