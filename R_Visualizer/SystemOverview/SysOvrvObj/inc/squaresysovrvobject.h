#ifndef SQUARESYSOVRVOBJECT_H
#define SQUARESYSOVRVOBJECT_H

#include "sysovrvobjderivationhelper.h"

class SquareSysOvrvObject : public SysOvrvObjDerivationHelper<SquareSysOvrvObject>
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

    void resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y) Q_DECL_OVERRIDE;

private:
    

};

#endif /* SQUARESYSOVRVOBJECT_H */
