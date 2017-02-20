#ifndef RECTSYSOVRVOBJECT_H
#define RECTSYSOVRVOBJECT_H

#include "sysovrvobjderivationhelper.h"

class RectSysOvrvObject : public SysOvrvObjDerivationHelper<RectSysOvrvObject>
{
private:
    

public:
    RectSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    RectSysOvrvObject(const RectSysOvrvObject &other);
    RectSysOvrvObject(RectSysOvrvObject &&other);
    RectSysOvrvObject(const SysOvrvObject &original);
    RectSysOvrvObject(SysOvrvObject &&original);
    ~RectSysOvrvObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;

};

#endif /* RECTSYSOVRVOBJECT_H */
