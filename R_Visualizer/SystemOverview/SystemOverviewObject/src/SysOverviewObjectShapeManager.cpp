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

}

QString SysOverviewObjectShapeManager::translateShapeToString(const SysOverviewObjectShapeManager::SysOverviewObjectShapes &shape)
{

}

QStringList SysOverviewObjectShapeManager::listShapes()
{

}
