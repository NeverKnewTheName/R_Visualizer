#include "imagesysovrvobject.h"

#include <QBuffer>
#include <QPainter>
#include <QBrush>
#include <QPointF>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

ImageSysOvrvObject::ImageSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObjDerivationHelper(parent)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(const ImageSysOvrvObject &other) :
    SysOvrvObjDerivationHelper(other)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(ImageSysOvrvObject &&other) :
    SysOvrvObjDerivationHelper(std::move(other))
{
}

ImageSysOvrvObject::ImageSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(std::move(original))
{
}

ImageSysOvrvObject::~ImageSysOvrvObject()
{
}

void ImageSysOvrvObject::loadImageFromFile(const QString &filePath)
{
    objPixMap = QPixmap(filePath);
    update();
}

void ImageSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);

    painter->save();

    painter->drawPixmap(boundingRect(), objPixMap, objPixMap.rect());

    painter->restore();
}

SysOvrvObject::ObjShapeType ImageSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Image;
}

QByteArray ImageSysOvrvObject::saveObjPixmap() const
{
    QByteArray pixmapSave;
    QBuffer saveBuffer(&pixmapSave);

    saveBuffer.open(QIODevice::WriteOnly);
    objPixMap.save(&saveBuffer, "PNG");
}

void ImageSysOvrvObject::loadObjPixmap(const QByteArray &savedPixmap)
{
    objPixMap.loadFromData(savedPixmap, "PNG");
    update();
}
