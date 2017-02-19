#ifndef TRIANGLESYSOVRVOBJECT_H
#define TRIANGLESYSOVRVOBJECT_H

#include "sysovrvobject.h"

class TriangleSysOvrvObject : public SysOvrvObject
{
private:
    

public:
    TriangleSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    TriangleSysOvrvObject(const TriangleSysOvrvObject &other);
    TriangleSysOvrvObject(TriangleSysOvrvObject &&other);
    TriangleSysOvrvObject(const SysOvrvObject &original);
    TriangleSysOvrvObject(SysOvrvObject &&original);
    ~TriangleSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;
};

#endif /* TRIANGLESYSOVRVOBJECT_H */
