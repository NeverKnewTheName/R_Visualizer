#include "squaresysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>
#include <QStyleOptionGraphicsItem>

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
    SysOvrvObjDerivationHelper(std::move(other))
{
}

SquareSysOvrvObject::SquareSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
    const qreal x = getWidth();
    const qreal y = getHeight();
    const qreal newDimension = (x+y)/2;
    setHeight(newDimension);
    setWidth(newDimension);
}

SquareSysOvrvObject::SquareSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(std::move(original))
{
    const qreal x = getWidth();
    const qreal y = getHeight();
    const qreal newDimension = (x+y)/2;
    setHeight(newDimension);
    setWidth(newDimension);
}

SquareSysOvrvObject::~SquareSysOvrvObject()
{
}

void SquareSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
    QRectF boundRect = boundingRect();
    QBrush colorBrush(getCurObjColor());

    painter->save();

    painter->setBrush(colorBrush);
    painter->drawRect(boundRect);

    painter->restore();
}

SysOvrvObject::ObjShapeType SquareSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Square;
}

//maybe abstract in another superclass for quadratic shapes...
void SquareSysOvrvObject::resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y)
{
    const qreal xAbs = (x>0 ? x : -x);
    const qreal yAbs = (y>0 ? y : -y);

    if( xAbs > yAbs )
    {
        x /= 2;
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
        y /= 2;
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
