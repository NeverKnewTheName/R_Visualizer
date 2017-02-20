#include "circlesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

CircleSysOvrvObject::CircleSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(const CircleSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(CircleSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(other)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

CircleSysOvrvObject::CircleSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

CircleSysOvrvObject::~CircleSysOvrvObject()
{
}

void CircleSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
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

void CircleSysOvrvObject::resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y)
{
    if((x>0 ? x : -x) > (y>0 ? y : -y))
    {
        if(
                AnchorPoint == ResizeRectCorner::BottomLeftCorner || 
                AnchorPoint == ResizeRectCorner::TopRightCorner
                )
        {
            y = -x;
        }
        else
        {
            y = x;
        }
    }
    else
    {
        if(
                AnchorPoint == ResizeRectCorner::BottomLeftCorner || 
                AnchorPoint == ResizeRectCorner::TopRightCorner
                )
        {
            x = -y;
        }
        else
        {
            x = y;
        }
    }
    SysOvrvObjDerivationHelper::resize(AnchorPoint, x, y);
}
