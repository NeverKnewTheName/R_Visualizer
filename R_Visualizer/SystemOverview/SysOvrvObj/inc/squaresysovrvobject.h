#ifndef SQUARESYSOVRVOBJECT_H
#define SQUARESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class SquareSysOvrvObject : public SysOvrvObject
{
public:
    SquareSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    SquareSysOvrvObject(const SquareSysOvrvObject &other);
    SquareSysOvrvObject(SquareSysOvrvObject &&other);
    SquareSysOvrvObject(const SysOvrvObject &original);
    SquareSysOvrvObject(SysOvrvObject &&original);
    ~SquareSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;
private:
    

};

#endif /* SQUARESYSOVRVOBJECT_H */
