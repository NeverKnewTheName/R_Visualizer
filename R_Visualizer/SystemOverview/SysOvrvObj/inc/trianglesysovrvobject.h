#ifndef TRIANGLESYSOVRVOBJECT_H
#define TRIANGLESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class Trianglesysovrvobject : public SysOvrvObject
{
private:
    

public:
    Trianglesysovrvobject();
    ~Trianglesysovrvobject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    SysOvrvObject::QbjShapeType getShape() const;
};

#endif /* TRIANGLESYSOVRVOBJECT_H */
