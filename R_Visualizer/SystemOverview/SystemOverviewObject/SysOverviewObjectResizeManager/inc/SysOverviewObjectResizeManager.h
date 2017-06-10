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

class ISystemOverviewObject;

/**
 * @brief The SysOverviewObjectResizeManager
 */
class SysOverviewObjectResizeManager :
        public ISysOverviewObjectResizeManagerCRTPHelper<SysOverviewObjectResizeManager>
{
public:
    SysOverviewObjectResizeManager(
            ISystemOverviewObject &sysOverviewObject,
            const QSizeF &size = QSizeF(100,100)
            );
    virtual ~SysOverviewObjectResizeManager();

    virtual void paint(QPainter *painter);

    virtual void setSize(const QSizeF &size);
    virtual QSizeF getSize() const;

    virtual QRectF getBoundingRect() const;

private:
    ISystemOverviewObject &sysOverviewObject;
    QSizeF size;
};

#endif /* SYSOVERVIEWOBJECTRESIZEMANAGER_H */
