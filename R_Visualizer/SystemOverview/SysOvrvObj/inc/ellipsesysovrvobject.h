#ifndef ELLIPSESYSOVRVOBJECT_H
#define ELLIPSESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class EllipseSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    EllipseSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    EllipseSysOvrvObject(const EllipseSysOvrvObject &other);
    EllipseSysOvrvObject(EllipseSysOvrvObject &&other);
    EllipseSysOvrvObject(const SysOvrvObject &original);
    EllipseSysOvrvObject(SysOvrvObject &&original);
    ~EllipseSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;
};

#endif /* ELLIPSESYSOVRVOBJECT_H */
