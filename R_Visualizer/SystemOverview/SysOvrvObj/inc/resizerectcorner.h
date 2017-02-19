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

#endif // RESIZERECTCORNER_H
