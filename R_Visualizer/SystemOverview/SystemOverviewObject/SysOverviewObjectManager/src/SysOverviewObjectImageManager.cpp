#include "SysOverviewObjectImageManager.h"

#include "ISystemOverviewObject.h"

SysOverviewObjectImageManager::SysOverviewObjectImageManager(
        ISystemOverviewObject *sysOverviewObject,
        const QImage &image
        ) :
    ISysOverviewObjectManagerCRTPHelper(ImageType),
    sysOverviewObject(sysOverviewObject),
    image(QPixmap::fromImage(image))
{

}

SysOverviewObjectImageManager::SysOverviewObjectImageManager(
        ISystemOverviewObject *sysOverviewObject,
        const QPixmap &image
        ) :
    ISysOverviewObjectManagerCRTPHelper(ImageType),
    sysOverviewObject(sysOverviewObject),
    image(image)
{

}

SysOverviewObjectImageManager::~SysOverviewObjectImageManager()
{

}

void SysOverviewObjectImageManager::setImage(const QImage &image)
{

}

void SysOverviewObjectImageManager::setImage(const QPixmap &image)
{
    this->image = image;
    sysOverviewObject->update();
}

QPixmap SysOverviewObjectImageManager::getImage() const
{
    return image;
}

void SysOverviewObjectImageManager::paint(
        QPainter *painter,
        const QRectF &boundingRect,
        const ISysOverviewObjectManager::ObjectState objectState
        )
{

}


void SysOverviewObjectImageManager::setSysOverviewObject(ISystemOverviewObject *newSysOverviewObject)
{
}
