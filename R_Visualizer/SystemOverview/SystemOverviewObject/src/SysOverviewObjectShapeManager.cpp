#include "SysOverviewObjectShapeManager.h"

SysOverviewObjectShapeManager::SysOverviewObjectShapeManager(
        ISystemOverviewObject &sysOverviewObject,
        SysOverviewObjectShapeManager::SysOverviewObjectShapes shape
        ) :
    sysOverviewObject(sysOverviewObject),
    shape(shape)
{

}

SysOverviewObjectShapeManager::~SysOverviewObjectShapeManager()
{

}

SysOverviewObjectShapeManager::SysOverviewObjectShapes SysOverviewObjectShapeManager::getShape() const
{

}

void SysOverviewObjectShapeManager::setShape(const SysOverviewObjectShapeManager::SysOverviewObjectShapes &shape) const
{

}

void SysOverviewObjectShapeManager::paint(QPainter *painter, const QRectF &boundingRect, const QColor &color)
{
    painter->save();

    painter->setBrush(QBrush(color));
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
        const SysOverviewObjectShapeManager::SysOverviewObjectShapes &shape
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
        shapeNames << translateShapeToString(cntr);
    }

    return shapeNames;
}
