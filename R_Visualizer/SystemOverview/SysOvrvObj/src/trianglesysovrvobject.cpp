#include "trianglesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPainterPath>
#include <QPointF>

#include <QDebug>

TriangleSysOvrvObject::TriangleSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

TriangleSysOvrvObject::TriangleSysOvrvObject(const TriangleSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

TriangleSysOvrvObject::TriangleSysOvrvObject(TriangleSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(other)
{
}

TriangleSysOvrvObject::TriangleSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

TriangleSysOvrvObject::TriangleSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

TriangleSysOvrvObject::~TriangleSysOvrvObject()
{
}

void TriangleSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getMyColor());

    QPointF rectTopMiddle((boundRect.right() - boundRect.left()) / 2, boundRect.top());
    QPainterPath path(rectTopMiddle);

    path.lineTo(boundRect.bottomRight());
    path.lineTo(boundRect.bottomLeft());
    path.lineTo(rectTopMiddle);

    painter->save();

    painter->setBrush(colorBrush);
    painter->drawPath(path);

    painter->restore();
}

SysOvrvObject::ObjShapeType TriangleSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Triangle;
}