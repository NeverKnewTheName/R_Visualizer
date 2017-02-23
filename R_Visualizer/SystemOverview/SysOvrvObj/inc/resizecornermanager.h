#ifndef RESIZECORNERMANAGER_H
#define RESIZECORNERMANAGER_H

#include <QRectF>

class ResizableGraphicsItem;
class ResizeRectCorner;

class ResizeCornerManager
{
public:
    ResizeCornerManager(const qreal size, ResizableGraphicsItem *parent = Q_NULLPTR);

    ResizeCornerManager(const ResizeCornerManager &other);

    ResizeCornerManager(ResizeCornerManager &&other);

    ~ResizeCornerManager();

    void update(const QRectF &rect = QRectF());

    void setParentItem(ResizableGraphicsItem *parent = Q_NULLPTR);

    void setVisible(const bool isVisible = true);

    ResizeRectCorner *cornerTopLeft;
    ResizeRectCorner *cornerBottomLeft;
    ResizeRectCorner *cornerTopRight;
    ResizeRectCorner *cornerBottomRight;

private:
    ResizableGraphicsItem *parentItem;
};

#endif /* RESIZECORNERMANAGER_H */
