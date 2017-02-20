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
        TopLeftCorner,
        BottomLeftCorner,
        TopRightCorner,
        BottomRightCorner,
        TotalNrOfCorners
    } CornerPos;

    ResizeRectCorner(const CornerPos cornerPos, const qreal size = 10, ResizableGraphicsItem *parent = Q_NULLPTR);
    ResizeRectCorner(const ResizeRectCorner &other);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

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

#endif // RESIZERECTCORNER_H
