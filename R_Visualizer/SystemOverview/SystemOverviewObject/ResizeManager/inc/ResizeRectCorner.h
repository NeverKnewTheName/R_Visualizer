#ifndef RESIZERECTCORNER_H
#define RESIZERECTCORNER_H

#include <QGraphicsRectItem>

class ISysOverviewObjectResizeManager;

class ResizeRectCorner : public QGraphicsRectItem
{
public:
    enum CornerPos
    {
        CornerPos_TopLeft,
        CornerPos_TopRight,
        CornerPos_BottomLeft,
        CornerPos_BottomRight
    };

    ResizeRectCorner();
    ResizeRectCorner(
            const CornerPos cornerPos,
            ISysOverviewObjectResizeManager *resizeManager,
            QGraphicsItem *parent = Q_NULLPTR
            );
    ResizeRectCorner(const ResizeRectCorner &copy);

    ~ResizeRectCorner();

    void setPosition(const QPointF &pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

private:
    const CornerPos cornerPos;
    ISysOverviewObjectResizeManager *resizeManager;

    static int constructCount;
};

#endif // RESIZERECTCORNER_H
