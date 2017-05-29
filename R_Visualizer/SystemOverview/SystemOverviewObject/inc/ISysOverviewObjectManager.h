/**
 * @file ISysOverviewObjectManager.h
 * @author Christian Neuberger
 * @date 2017-05-01
 * 
 * @brief Interface for managers for #ISystemOverviewObject
 */
#ifndef ISYSOVERVIEWOBJECTMANAGER_H
#define ISYSOVERVIEWOBJECTMANAGER_H

#include <QPainter>
#include <QRectF>
#include <QColor>

/**
 * @brief The ISysOverviewObjectManager interface
 */
class ISysOverviewObjectManager
{
public:
    virtual ~ISysOverviewObjectManager(){}

    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const QColor &color
            ) = 0;
};

#endif /* ISYSOVERVIEWOBJECTMANAGER_H */
