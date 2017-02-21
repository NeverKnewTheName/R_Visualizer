#ifndef IMAGESYSOVRVOBJECT_H
#define IMAGESYSOVRVOBJECT_H

#include "sysovrvobjderivationhelper.h"

#include <QPixmap>

class ImageSysOvrvObject : public SysOvrvObjDerivationHelper<ImageSysOvrvObject>
{
public:
    ImageSysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    ImageSysOvrvObject(const ImageSysOvrvObject &other);
    ImageSysOvrvObject(ImageSysOvrvObject &&other);
    ImageSysOvrvObject(const SysOvrvObject &original);
    ImageSysOvrvObject(SysOvrvObject &&original);
    ~ImageSysOvrvObject();

    void loadImageFromFile(const QString &filePath);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    SysOvrvObject::ObjShapeType getShape() const;

    QByteArray saveObjPixmap() const;
    void loadObjPixmap(const QByteArray &savedPixmap);
private:
    QPixmap objPixMap;

};

#endif /* IMAGESYSOVRVOBJECT_H */
