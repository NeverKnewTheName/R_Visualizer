/**
 * @file ISysOverviewObjectResizeManager.h
 * @author Christian Neuberger
 * @date 2017-05-01
 * 
 * @brief Interface for resize managers for #ISystemOverviewObject
 */
#ifndef ISYSOVERVIEWOBJECTRESIZEMANAGER_H
#define ISYSOVERVIEWOBJECTRESIZEMANAGER_H


#include <QPainter>
#include <QRectF>
#include <QSizeF>

#include "ResizeRectCorner.h"

class ISystemOverviewObject;

#include <memory>

/**
 * @brief The ISysOverviewObjectResizeManager interface
 */
class ISysOverviewObjectResizeManager
{
public:
    enum ResizeManagerType
    {
        ResizeManagerType_RectCornerResizeManager,
        ResizeManagerType_NR_OF_RESIZE_MANAGER_TYPES
    };

    virtual ~ISysOverviewObjectResizeManager(){}

    virtual ResizeManagerType getType() const = 0;

    virtual ISysOverviewObjectResizeManager *clone() const = 0;

    virtual void setSysOverviewObject(
            ISystemOverviewObject *newSysOverviewObject
            ) = 0;

    virtual void paint(QPainter *painter) = 0;

    virtual void setSize(const QSizeF &size) = 0;
    virtual QSizeF getSize() const = 0;

    virtual void resize(
            const ResizeRectCorner::CornerPos cornerPos,
            qreal x,
            qreal y
            ) = 0;

    virtual void enableResize(const bool enabled) = 0;

    virtual QRectF getBoundingRect() const = 0;
};

typedef std::unique_ptr<ISysOverviewObjectResizeManager> SysOvrvObjectResizeManagerPtr;

template<class Derivate>
class ISysOverviewObjectResizeManagerCRTPHelper : public ISysOverviewObjectResizeManager
{
public:
    virtual ISysOverviewObjectResizeManager *clone() const
    {
        return new Derivate(static_cast<const Derivate &>(*this));
    }
};

#endif /* ISYSOVERVIEWOBJECTRESIZEMANAGER_H */
