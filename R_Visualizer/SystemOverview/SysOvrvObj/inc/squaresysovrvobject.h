#ifndef SQUARESYSOVRVOBJECT_H
#define SQUARESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class SquareSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    SquareSysOvrvObject();
    ~SquareSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    SysOvrvObject::QbjShapeType getShape() const;
};

#endif /* SQUARESYSOVRVOBJECT_H */
