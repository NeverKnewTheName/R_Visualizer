#ifndef SYSOVRVOBJECT_H
#define SYSOVRVOBJECT_H

#include <QGraphicsItem>
#include <QHash>

#include "resizerectcorner.h"


class SysOvrvObject : public QGraphicsItem
{
public:
    explicit SysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    explicit SysOvrvObject(SysOvrvObject *obj, QGraphicsItem *parent = Q_NULLPTR);
    ~SysOvrvObject();

    typedef enum Shapetypes
    {
        ObjShape_Rectangle,
        ObjShape_Square,
        ObjShape_Ellipse,
        ObjShape_Circle,
        ObjShape_Triangle
    }ObjShapeTypes;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setupSysOvrvObject();

    QColor getMyColor() const;
    void setMyColor(const QColor &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    void setShape(ObjShapeTypes shape);
    ObjShapeTypes getShape() const;

    SysOvrvObject &operator=(const SysOvrvObject &obj);
    SysOvrvObject *duplicate();

    void setAsChild(bool isChild);
    bool isAChild() const;

    void setResizeMode(bool modeON);
    bool getIsInResizeMode() const;
    void showResizeCorners(bool show);

    qreal getWidth() const;
    void setWidth(qreal newWidth);
    void adjustWidth(qreal factor);
    qreal getHeight() const;
    void setHeight(qreal newHeight);
    void adjustHeight(qreal factor);

    SysOvrvObject *addChildSysOvrvItem(SysOvrvObject* child);
    void removeChildSysOvrvItem(SysOvrvObject *child);
    QVector<SysOvrvObject *> &getChidSysOvrvObjects();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QString getHashedName() const;

private:
    static int objCntr;
    int localObjCntr;
    bool isInResizeMode;
    bool isChildObject;
    QString objName;
    QColor myColor;
    ObjShapeTypes shapeType;
    QVector<SysOvrvObject *> childSysOvrvObjects;
    ResizeRectCorner *corners;
    QRectF m_BoundingRect;

    void updateCorners();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // SYSOVRVOBJECT_H
