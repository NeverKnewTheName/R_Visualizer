#include "SysOverviewObjectResizeManager.h"

SysOverviewObjectResizeManager::SysOverviewObjectResizeManager(
        ISystemOverviewObject &sysOverviewObject,
        const QSizeF &size
        ) :
    sysOverviewObject(sysOverviewObject),
    size(size)
{

}

SysOverviewObjectResizeManager::~SysOverviewObjectResizeManager()
{

}

void SysOverviewObjectResizeManager::paint(QPainter *painter)
{

}

void SysOverviewObjectResizeManager::setSize(const QSizeF &size)
{
    this->size = size;
}

QSizeF SysOverviewObjectResizeManager::getSize() const
{
    return this->size;
}

QRectF SysOverviewObjectResizeManager::getBoundingRect() const
{
    return QRectF(QPointF(0,0),size);
}
