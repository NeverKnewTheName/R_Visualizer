#ifndef RESIZERECTCORNER_H
#define RESIZERECTCORNER_H

#include <QGraphicsRectItem>

class ResizableGraphicsItem;

class ResizeRectCorner : public QGraphicsRectItem
{
public:
    enum { Type = UserType + 4 };
    typedef enum _CornerPos
    {
        topLeftCorner,
        bottomLeftCorner,
        topRightCorner,
        bottomRightCorner,
        TotalNrOfCorners
    } CornerPos;

    ResizeRectCorner(CornerPos cornerPos, qreal size = 10, ResizableGraphicsItem *parent = Q_NULLPTR);
    ResizeRectCorner(ResizeRectCorner &&ToMove);

    CornerPos getCornerPos() const;
    void setCornerPos(CornerPos cornerPos);

    qreal getCornerSize();
    void setCornerSize(const qreal &value);

    void setPosition(const QPointF &pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

private:
    CornerPos cornerPos;
    qreal cornerSize;

    // QGraphicsItem interface
public:
    int type() const;
};

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
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
};
#endif // RESIZERECTCORNER_H
