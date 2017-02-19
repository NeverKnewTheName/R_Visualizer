#ifndef CIRCLESYSOVRVOBJECT_H
#define CIRCLESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class CircleSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    CircleSysOvrvObject();
    ~CircleSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    SysOvrvObject::QbjShapeType getShape() const;
};

#endif /* CIRCLESYSOVRVOBJECT_H */
