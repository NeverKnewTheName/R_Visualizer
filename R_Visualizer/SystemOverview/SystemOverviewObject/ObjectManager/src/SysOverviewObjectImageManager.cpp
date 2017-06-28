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
    this->image = QPixmap::fromImage(image);
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
    painter->save();

    painter->drawPixmap(
                boundingRect,
                image,
                QRectF(image.rect())
                );

    switch(objectState)
    {
    case ObjectState_Normal:
        break;
    case ObjectState_Selected:
        painter->setPen(QPen(QBrush(QColor(Qt::blue)),2));
    case ObjectState_Highlighted:
        painter->setBrush(QColor(55,55,55,100));
        painter->drawRect(boundingRect);
        break;
    case ObjectState_Disabled:
        break;
    }


    painter->restore();
}


void SysOverviewObjectImageManager::setSysOverviewObject(ISystemOverviewObject *newSysOverviewObject)
{
    this->sysOverviewObject = newSysOverviewObject;
}
