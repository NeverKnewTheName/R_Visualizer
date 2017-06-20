#include "SysOverviewObjectResizeManager.h"
#include "ISystemOverviewObject.h"

#include <QDebug>

int SysOverviewObjectResizeManager::objCounter = 0;

SysOverviewObjectResizeManager::SysOverviewObjectResizeManager(
        ISystemOverviewObject *sysOverviewObject,
        const QSizeF &size
        ) :
    sysOverviewObject(sysOverviewObject),
    size(size),
    boundingRect(QPointF(0,0),size),
    resizeEnabled(false),
    resizeCorners()
{
    initResizeCorners();
    enableResize(resizeEnabled);

    objCounter++;
    qDebug() << "ResizeManager -- Constructor: " << objCounter;
}

SysOverviewObjectResizeManager::SysOverviewObjectResizeManager(
        const SysOverviewObjectResizeManager &copy
        ) :
    sysOverviewObject(copy.sysOverviewObject),
    size(copy.size),
    boundingRect(copy.boundingRect),
    resizeEnabled(copy.resizeEnabled),
    resizeCorners()
{
    initResizeCorners();
    enableResize(resizeEnabled);

    objCounter++;
    qDebug() << "ResizeManager -- CopyConstructor: " << objCounter;
}

SysOverviewObjectResizeManager::~SysOverviewObjectResizeManager()
{
    resizeCorners.clear();
    objCounter--;
    qDebug() << "ResizeManager -- Destructor: " << objCounter;
}

ISysOverviewObjectResizeManager::ResizeManagerType SysOverviewObjectResizeManager::getType() const
{
    return ISysOverviewObjectResizeManager::ResizeManagerType_RectCornerResizeManager;
}

void SysOverviewObjectResizeManager::setSysOverviewObject(
        ISystemOverviewObject *newSysOverviewObject
                                                          )
{
    sysOverviewObject = newSysOverviewObject;
    initResizeCorners();
    initResizeCornersPositions();
}

void SysOverviewObjectResizeManager::paint(QPainter *painter)
{
    initResizeCornersPositions();
}

void SysOverviewObjectResizeManager::setSize(const QSizeF &size)
{
    this->size = size;
    boundingRect = QRectF(QPointF(0,0),size);
    sysOverviewObject->update();
}

QSizeF SysOverviewObjectResizeManager::getSize() const
{
    return this->size;
}

void SysOverviewObjectResizeManager::enableResize(const bool enabled)
{
    resizeEnabled = enabled;

    for(ResizeRectCorner &corner : resizeCorners)
    {
        corner.setVisible(resizeEnabled);
    }
}

void SysOverviewObjectResizeManager::resize(
        const ResizeRectCorner::CornerPos cornerPos,
        qreal x,
        qreal y
        )
{
    if(!resizeEnabled)
    {
        //Currently not in resize mode...
        //This should never happen!
        return;
    }
    qreal distX = 0;
    qreal distY = 0;

    qreal oldWidth = size.width();
    qreal oldHeigth = size.height();
    qreal newWidth = 0;
    qreal newHeight = 0;

    switch(cornerPos)
    {
    case ResizeRectCorner::CornerPos_TopLeft:
        newWidth = oldWidth - x;
        newHeight = oldHeigth - y;
        distX = x;
        distY = y;
        break;
    case ResizeRectCorner::CornerPos_BottomLeft:
        newWidth = oldWidth - x;
        distX = x;
        newHeight = oldHeigth + y;
        break;
    case ResizeRectCorner::CornerPos_TopRight:
        newWidth = oldWidth + x;
        newHeight = oldHeigth - y;
        distY = y;
        break;
    case ResizeRectCorner::CornerPos_BottomRight:
        newWidth = oldWidth + x;
        newHeight = oldHeigth + y;
        break;
    default:
        distX = distY = newWidth = newHeight = 0;
    }

    if(newWidth <= 0.1)
    {
        distX = 0;
        newWidth = 0;
    }
    if(newWidth > 0 )
    {
        sysOverviewObject->prepareSizeChange();
        size.setWidth(newWidth);
    }
    if(newHeight <= 0.1)
    {
        distY = 0;
        newHeight = 0;
    }
    if(newHeight > 0 )
    {
        sysOverviewObject->prepareSizeChange();
        size.setHeight(newHeight);
    }


    sysOverviewObject->move(distX,distY);
}

QRectF SysOverviewObjectResizeManager::getBoundingRect() const
{
    return QRectF(0,0,size.width(),size.height());
}

void SysOverviewObjectResizeManager::initResizeCorners()
{
    resizeCorners.clear();
    resizeCorners.append(
                ResizeRectCorner(
                    ResizeRectCorner::CornerPos_TopLeft,
                    this,
                    sysOverviewObject
                  )
                );
    resizeCorners.append(
                ResizeRectCorner(
                    ResizeRectCorner::CornerPos_TopRight,
                    this,
                    sysOverviewObject
                  )
                );
    resizeCorners.append(
                ResizeRectCorner(
                    ResizeRectCorner::CornerPos_BottomLeft,
                    this,
                    sysOverviewObject
                  )
                );
    resizeCorners.append(
                ResizeRectCorner(
                    ResizeRectCorner::CornerPos_BottomRight,
                    this,
                    sysOverviewObject
                  )
                );
    resizeCorners.resize(4);
}

void SysOverviewObjectResizeManager::initResizeCornersPositions()
{
    QRectF boundingRect(getBoundingRect());
    resizeCorners[0].setPosition(boundingRect.topLeft());
    resizeCorners[1].setPosition(boundingRect.topRight());
    resizeCorners[2].setPosition(boundingRect.bottomLeft());
    resizeCorners[3].setPosition(boundingRect.bottomRight());
}
