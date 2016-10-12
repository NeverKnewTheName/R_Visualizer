#ifndef RESIZERECTCORNER_H
#define RESIZERECTCORNER_H

#include <QGraphicsRectItem>

class ResizeRectCorner : public QGraphicsRectItem
{
public:
    ResizeRectCorner(QGraphicsItem *parent = Q_NULLPTR);

    typedef enum _CornerPos
    {
        topLeftCorner,
        bottomLeftCorner,
        topRightCorner,
        bottomRightCorner,
        TotalNrOfCorners
    } CornerPos;

    void setCornerPos(CornerPos cornerPos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    CornerPos cornerPos;
};

#endif // RESIZERECTCORNER_H
