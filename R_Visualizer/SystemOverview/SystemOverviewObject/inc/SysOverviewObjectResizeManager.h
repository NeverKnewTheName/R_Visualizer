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

class ISystemOverviewObject;

/**
 * @brief The SysOverviewObjectResizeManager
 */
class SysOverviewObjectResizeManager
{
public:
    SysOverviewObjectResizeManager(
            ISystemOverviewObject &sysOverviewObject,
            const QsizeF &size = QSizeF(100,100)
            );
    virtual ~SysOverviewObjectResizeManager();

    virtual void paint(QPainter *painter) = 0;

    virtual void setSize(const QSizeF &size);
    virtual QSizeF getSize() const;

    virtual QRectF getBoundingRect() const;

private:
    ISystemOverviewObject &sysOverviewObject;

};

#endif /* SYSOVERVIEWOBJECTRESIZEMANAGER_H */
