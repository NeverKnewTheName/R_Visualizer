#ifndef IMAGESYSOVRVOBJECT_H
#define IMAGESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class ImageSysOvrvObject : public SysOvrvObject
{
public:
    ImageSysOvrvObject();
    ~ImageSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    SysOvrvObject::QbjShapeType getShape() const;
};

#endif /* IMAGESYSOVRVOBJECT_H */
