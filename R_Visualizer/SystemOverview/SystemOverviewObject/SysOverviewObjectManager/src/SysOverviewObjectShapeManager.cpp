#include "SysOverviewObjectShapeManager.h"

SysOverviewObjectShapeManager::SysOverviewObjectShapeManager(
        ISystemOverviewObject &sysOverviewObject,
        SysOverviewObjectShapeManager::SysOverviewObjectShape shape
        ) :
    ISysOverviewObjectManagerCRTPHelper(
        ISysOverviewObjectManager::ShapeType
        ),
    sysOverviewObject(sysOverviewObject),
    objColor(Qt::lightGray),
    shape(shape)
{

}

SysOverviewObjectShapeManager::~SysOverviewObjectShapeManager()
{

}

SysOverviewObjectShapeManager::SysOverviewObjectShape SysOverviewObjectShapeManager::getShape() const
{
    return this->shape;
}

void SysOverviewObjectShapeManager::setShape(
        const SysOverviewObjectShapeManager::SysOverviewObjectShape &shape
        )
{
    this->shape = shape;
}

QColor SysOverviewObjectShapeManager::getColor() const
{
    return objColor;
}

void SysOverviewObjectShapeManager::setColor(const QColor &color)
{
    objColor = color;
}

void SysOverviewObjectShapeManager::paint(
        QPainter *painter,
        const QRectF &boundingRect,
        const bool selected
        )
{
    painter->save();

    QColor curObjColor(objColor);

    if(selected)
    {
        if(curObjColor.alphaF()<0.1)
        {
            curObjColor.setAlphaF(0.1);
        }
        curObjColor = curObjColor.darker();
    }

    painter->setBrush(QBrush(curObjColor));
    painter->setPen(QColor(Qt::black));

    switch(shape)
    {
    case SysOvrvShape_Rectangle:
        painter->drawRect(boundingRect);
        break;
    case SysOvrvShape_Square:
        painter->drawRect(boundingRect);
        break;
    case SysOvrvShape_Ellipse:
        painter->drawEllipse(boundingRect);
        break;
    case SysOvrvShape_Circle:
        painter->drawEllipse(boundingRect);
        break;
    case SysOvrvShape_Triangle:
        painter->drawEllipse(boundingRect);
        break;
    }

    painter->restore();
}

QString SysOverviewObjectShapeManager::translateShapeToString(
        const SysOverviewObjectShapeManager::SysOverviewObjectShape &shape
        )
{
    switch(shape)
    {
    case SysOvrvShape_Rectangle:
        return QString("Rectangle");
        break;
    case SysOvrvShape_Square:
        return QString("Square");
        break;
    case SysOvrvShape_Ellipse:
        return QString("Ellipse");
        break;
    case SysOvrvShape_Circle:
        return QString("Circle");
        break;
    case SysOvrvShape_Triangle:
        return QString("Triangle");
        break;
    default:
        return QString("UNDEFINED");
    }
}

QStringList SysOverviewObjectShapeManager::listShapes()
{
    QStringList shapeNames;


    for(int cntr = 0; cntr < SysOvrvShape_NR_OF_SHAPES; ++cntr)
    {
        shapeNames << translateShapeToString(static_cast<SysOverviewObjectShape>(cntr));
    }

    return shapeNames;
}
