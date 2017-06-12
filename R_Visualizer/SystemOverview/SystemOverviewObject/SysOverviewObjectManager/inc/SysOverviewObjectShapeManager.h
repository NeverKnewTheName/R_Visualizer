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
#include <memory>

class ISystemOverviewObject;

#include "ISysOverviewObjectColorManager.h"

/**
 * @brief The SysOverviewObjectShapeManager
 */
class SysOverviewObjectShapeManager :
        public ISysOverviewObjectManagerCRTPHelper<SysOverviewObjectShapeManager>
{
public:
    enum SysOverviewObjectShape
    {
        SysOvrvShape_Rectangle,
        SysOvrvShape_Square,
        SysOvrvShape_Ellipse,
        SysOvrvShape_Circle,
        SysOvrvShape_Triangle,
        SysOvrvShape_NR_OF_SHAPES
    };

    SysOverviewObjectShapeManager(
            ISystemOverviewObject &sysOverviewObject,
            SysOverviewObjectShape shape = SysOvrvShape_Rectangle
            /* QObject *parent = Q_NULLPTR */
            );
    SysOverviewObjectShapeManager(
            ISystemOverviewObject &sysOverviewObject,
            SysOvrvObjColorManagerPtr colorManager,
            SysOverviewObjectShape shape = SysOvrvShape_Rectangle
            /* QObject *parent = Q_NULLPTR */
            );

    SysOverviewObjectShapeManager(
            const SysOverviewObjectShapeManager &copy
            );

    virtual ~SysOverviewObjectShapeManager();

    virtual SysOverviewObjectShape getShape() const;
    virtual void setShape(const SysOverviewObjectShape &shape);

    virtual SysOvrvObjColorManagerPtr getColorManager() const;
    virtual void setColorManager(SysOvrvObjColorManagerPtr colorManager);

    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const bool selected
            );

    void update();

    static QString translateShapeToString(const SysOverviewObjectShape &shape);
    static QStringList listShapes();

private:
    ISystemOverviewObject &sysOverviewObject;
    SysOvrvObjColorManagerPtr colorManager;
    SysOverviewObjectShape shape;
};

typedef std::unique_ptr<SysOverviewObjectShapeManager> SysOvrvObjectShapeManagerPtr;

#endif /* SYSOVERVIEWOBJECTSHAPEMANAGER_H */
