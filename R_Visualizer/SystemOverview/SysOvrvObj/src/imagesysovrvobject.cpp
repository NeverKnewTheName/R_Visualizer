#include "imagesysovrvobject.h"

#include <QPainter>
#include <QBrush>
#include <QPointF>

#include <QDebug>

ImageSysOvrvObject::ImageSysOvrvObject(QGraphicsItem *parent) :
    SysOvrvObject(parent)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(const ImageSysOvrvObject &other) :
    SysOvrvObject(other)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(ImageSysOvrvObject &&other) :
    SysOvrvObject(other)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(const SysOvrvObject &original) :
    SysOvrvObject(original)
{
}

ImageSysOvrvObject::ImageSysOvrvObject(SysOvrvObject &&original) :
    SysOvrvObject(original)
{
}

ImageSysOvrvObject::~ImageSysOvrvObject()
{
}

void ImageSysOvrvObject::paint(QPainter *paint, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

SysOvrvObject::ObjShapeType ImageSysOvrvObject::getShape() const
{
    return SysOvrvObject::ObjShape_Image;
}

