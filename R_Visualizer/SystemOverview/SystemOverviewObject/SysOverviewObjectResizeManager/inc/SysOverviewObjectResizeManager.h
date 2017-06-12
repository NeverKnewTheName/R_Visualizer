/**
 * @file SysOverviewObjectResizeManager.h
 * @author Christian Neuberger
 * @date 2017-05-01
 * 
 * @brief Default #ISysOverviewObjectResizeManager
 */
#ifndef SYSOVERVIEWOBJECTRESIZEMANAGER_H
#define SYSOVERVIEWOBJECTRESIZEMANAGER_H

#include "ISysOverviewObjectResizeManager.h"

#include <QSizeF>
#include "ResizeRectCorner.h"

#include "ISystemOverviewObject.h"

/**
 * @brief The SysOverviewObjectResizeManager
 */
class SysOverviewObjectResizeManager :
        public ISysOverviewObjectResizeManagerCRTPHelper<SysOverviewObjectResizeManager>
{
public:
    SysOverviewObjectResizeManager(
            ISystemOverviewObject *sysOverviewObject,
            const QSizeF &size = QSizeF(100,100)
            );

    SysOverviewObjectResizeManager(
            const SysOverviewObjectResizeManager &copy
            );

    virtual ~SysOverviewObjectResizeManager();

    virtual void setSysOverviewObject(
            ISystemOverviewObject *newSysOverviewObject
            );

    virtual void paint(QPainter *painter);

    virtual void setSize(const QSizeF &size);
    virtual QSizeF getSize() const;

    virtual void enableResize(const bool enabled);

    virtual void resize(
            const ResizeRectCorner::CornerPos cornerPos,
            qreal x,
            qreal y
            );

    virtual QRectF getBoundingRect() const;

private:
    void initResizeCorners();
    void initResizeCornersPositions();

private:
    ISystemOverviewObject *sysOverviewObject;
    QSizeF size;
    QRectF boundingRect;
    bool resizeEnabled;
    QVector<ResizeRectCorner> resizeCorners;

    static int objCounter;

};

#endif /* SYSOVERVIEWOBJECTRESIZEMANAGER_H */
