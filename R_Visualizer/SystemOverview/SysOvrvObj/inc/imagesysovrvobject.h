#ifndef IMAGESYSOVRVOBJECT_H
#define IMAGESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class ImageSysOvrvObject : public SysOvrvObject
{
public:
    ImageSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    ImageSysOvrvObject(const ImageSysOvrvObject &other);
    ImageSysOvrvObject(ImageSysOvrvObject &&other);
    ImageSysOvrvObject(const SysOvrvObject &original);
    ImageSysOvrvObject(SysOvrvObject &&original);
    ~ImageSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;
};

#endif /* IMAGESYSOVRVOBJECT_H */
