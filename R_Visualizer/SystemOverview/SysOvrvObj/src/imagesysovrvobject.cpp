#include "imagesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

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
    SysOvrvObjDerivationHelper(other)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObjDerivationHelper(original)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObjDerivationHelper(original)
{
}

ImageSysOvrvObject::~ImageSysOvrvObject()
{
}

void ImageSysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SysOvrvObjDerivationHelper::paint(painter, option, widget);
}

SysOvrvObject::ObjShapeType ImageSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Image;
}

