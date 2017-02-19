#ifndef CIRCLESYSOVRVOBJECT_H
#define CIRCLESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class CircleSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    CircleSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    CircleSysOvrvObject(const CircleSysOvrvObject &other);
    CircleSysOvrvObject(CircleSysOvrvObject &&other);
    CircleSysOvrvObject(const SysOvrvObject &original);
    CircleSysOvrvObject(SysOvrvObject &&original);
    ~CircleSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;
};

#endif /* CIRCLESYSOVRVOBJECT_H */
