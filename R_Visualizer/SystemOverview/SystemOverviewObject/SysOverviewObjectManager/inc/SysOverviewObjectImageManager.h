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

class ISystemOverviewObject;

/**
 * @brief The SysOverviewObjectImageManager
 */
class SysOverviewObjectImageManager :
        public ISysOverviewObjectManagerCRTPHelper<SysOverviewObjectImageManager>
{
public:
    SysOverviewObjectImageManager(
            ISystemOverviewObject *sysOverviewObject,
            const QImage &image
            );
    SysOverviewObjectImageManager(
            ISystemOverviewObject *sysOverviewObject,
            const QPixmap &image = QPixmap()
            );
    virtual ~SysOverviewObjectImageManager();

    virtual void setSysOverviewObject(
            ISystemOverviewObject *newSysOverviewObject
            );

    virtual void setImage(const QImage &image);
    virtual void setImage(const QPixmap &image);
    virtual QPixmap getImage() const;


    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const ObjectState objectState
            );

private:
    ISystemOverviewObject *sysOverviewObject;
    QPixmap image;

};

#endif /* SYSOVERVIEWOBJECTIMAGEMANAGER_H */
