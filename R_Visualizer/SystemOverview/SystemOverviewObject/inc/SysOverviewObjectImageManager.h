/**
 * @file SysOverviewObjectImageManager.h
 * @author Christian Neuberger
 * @date 2017-05-02
 * 
 * @brief Manager for Images for #ISystemOverviewObject
 */
#ifndef SYSOVERVIEWOBJECTIMAGEMANAGER_H
#define SYSOVERVIEWOBJECTIMAGEMANAGER_H

#include "ISysOverviewObjectManager.h"

#include <QImage>
#include <QPixmap>

/**
 * @brief The SysOverviewObjectImageManager
 */
class SysOverviewObjectImageManager
{
public:
    SysOverviewObjectImageManager(
            ISystemOverviewObject *sysOverviewObject,
            const QImage &image
            );
    SysOverviewObjectImageManager(
            ISystemOverviewObject *sysOverviewObject,
            const QPixmap &image
            );
    virtual ~SysOverviewObjectImageManager();

    virtual void setImage(const QImage &image);
    virtual void setImage(const QPixmap &image);
    virtual QPixmap getImage() const;


    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const QColor &color
            );

private:
    ISystemOverviewObject *sysOverviewObject;
    QPixmap image;
};

#endif /* SYSOVERVIEWOBJECTIMAGEMANAGER_H */
