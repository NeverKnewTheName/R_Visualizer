#ifndef RESIZEABLEGRAPHICSITEM_H
#define RESIZEABLEGRAPHICSITEM_H

#include <QGraphicsItem>

#include "resizerectcorner.h"

class ResizableGraphicsItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };
    ResizableGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~ResizableGraphicsItem();

    virtual void resize(ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y);
    virtual void enableResizing(bool isOn = true);
    bool getResizeEnabled() const;

    virtual void setWidth(const qreal newWidth) = 0;
    virtual qreal getWidth() const = 0;
    virtual void setHeight(const qreal newHeight) = 0;
    virtual qreal getHeight() const = 0;

    void initResizeCorners(const QRectF &boundingRect);

private:
    ResizeRectCorner resizeCorners[4];
    bool resizeEnabled;

    // QGraphicsItem interface
public:
    /* virtual QRectF boundingRect() const = 0; */
    /* virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0; */
    /* virtual int type() const; */
};

#endif /* RESIZEABLEGRAPHICSITEM_H */
