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

/**
 * @brief The ISysOverviewObjectResizeManager interface
 */
class ISysOverviewObjectResizeManager
{
public:
    virtual ~ISysOverviewObjectResizeManager(){}

    virtual void paint(QPainter *painter) = 0;

    virtual void setSize(const QSizeF &size);
    virtual QSizeF getSize() const;

    virtual QRectF getBoundingRect() const;
};

#endif /* ISYSOVERVIEWOBJECTRESIZEMANAGER_H */
