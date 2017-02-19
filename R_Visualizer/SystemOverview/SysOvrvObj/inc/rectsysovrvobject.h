#ifndef RECTSYSOVRVOBJECT_H
#define RECTSYSOVRVOBJECT_H

#include "sysovrvobject.h"

class RectSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    RectSysOvrvObject();
    ~RectSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    SysOvrvObject::QbjShapeType getShape() const;
};

#endif /* RECTSYSOVRVOBJECT_H */
