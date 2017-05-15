/**
 * @file SysOverviewObjectShapeManager.h
 * @author Christian Neuberger
 * @date 2017-05-01
 * 
 * @brief Default #ISysOverviewObjectShapeManager
 */
#ifndef SYSOVERVIEWOBJECTSHAPEMANAGER_H
#define SYSOVERVIEWOBJECTSHAPEMANAGER_H

#include "ISysOverviewObjectManager.h"

class ISystemOverviewObject;

/**
 * @brief The SysOverviewObjectShapeManager
 */
class SysOverviewObjectShapeManager : public ISysOverviewObjectManager
{
public:
    enum SysOverviewObjectShapes
    {
        SysOvrvShape_Rectangle,
        SysOvrvShape_Square,
        SysOvrvShape_Ellipse,
        SysOvrvShape_Circle,
        SysOvrvShape_Triangle,
    };

    SysOverviewObjectShapeManager(
            ISystemOverviewObject &sysOverviewObject,
            SysOverviewObjectShapes shape = SysOvrvShape_Rectangle
            /* QObject *parent = Q_NULLPTR */
            );
    virtual ~SysOverviewObjectShapeManager();

    virtual SysOverviewObjectShapes getShape() const;
    virtual void setShape(const SysOverviewObjectShapes &shape) const;

    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const QColor &color
            );

    static QString translateShapeToString(const SysOverviewObjectShapes &shape);
    static QStringList listShapes();

private:
    ISystemOverviewObject &sysOverviewObject;
    SysOverviewObjectShapes shape;
};

#endif /* SYSOVERVIEWOBJECTSHAPEMANAGER_H */
