#ifndef RESIZEABLEGRAPHICSITEM_H
#define RESIZEABLEGRAPHICSITEM_H

#include <QGraphicsItem>

#include "resizerectcorner.h"

struct Corners
{
    Corners(const qreal size, ResizableGraphicsItem *parent = Q_NULLPTR) :
        cornerTopLeft(new ResizeRectCorner(ResizeRectCorner::TopLeftCorner, size, parent)),
        cornerBottomLeft(new ResizeRectCorner(ResizeRectCorner::BottomLeftCorner, size, parent)),
        cornerTopRight(new ResizeRectCorner(ResizeRectCorner::TopRightCorner, size, parent)),
        cornerBottomRight(new ResizeRectCorner(ResizeRectCorner::BottomRightCorner, size, parent))
    {

    }

    Corners(const Corners &other) :
        cornerTopLeft(new ResizeRectCorner(*other.cornerTopLeft)),
        cornerBottomLeft(new ResizeRectCorner(*other.cornerBottomLeft)),
        cornerTopRight(new ResizeRectCorner(*other.cornerTopRight)),
        cornerBottomRight(new ResizeRectCorner(*other.cornerBottomRight))
    {
    }

    Corners(Corners &&other) :
        cornerTopLeft(other.cornerTopLeft),
        cornerBottomLeft(other.cornerBottomLeft),
        cornerTopRight(other.cornerTopRight),
        cornerBottomRight(other.cornerBottomRight)
    {
        other.cornerTopLeft = Q_NULLPTR;
        other.cornerBottomLeft= Q_NULLPTR;
        other.cornerTopRight = Q_NULLPTR;
        other.cornerBottomRight = Q_NULLPTR;
    }

    void setParentItem(QGraphicsItem *parent = Q_NULLPTR)
    {
        if(cornerTopLeft != Q_NULLPTR)
            cornerTopLeft->setParentItem(parent);

        if(cornerBottomLeft != Q_NULLPTR)
            cornerBottomLeft->setParentItem(parent);

        if(cornerTopRight != Q_NULLPTR)
            cornerTopRight->setParentItem(parent);

        if(cornerBottomRight != Q_NULLPTR)
            cornerBottomRight->setParentItem(parent);
    }

    void setPosition(const QRectF &boundingRect)
    {
        if(cornerTopLeft != Q_NULLPTR)
            cornerTopLeft->setPos(boundingRect.topLeft());

        if(cornerBottomLeft != Q_NULLPTR)
            cornerBottomLeft->setPos(boundingRect.bottomLeft());

        if(cornerTopRight != Q_NULLPTR)
            cornerTopRight->setPos(boundingRect.topRight());

        if(cornerBottomRight != Q_NULLPTR)
            cornerBottomRight->setPos(boundingRect.bottomRight());
    }

    void setVisible(const bool isVisible = true)
    {
        if(cornerTopLeft != Q_NULLPTR)
            cornerTopLeft->setVisible(isVisible);

        if(cornerBottomLeft != Q_NULLPTR)
            cornerBottomLeft->setVisible(isVisible);

        if(cornerTopRight != Q_NULLPTR)
            cornerTopRight->setVisible(isVisible);

        if(cornerBottomRight != Q_NULLPTR)
            cornerBottomRight->setVisible(isVisible);
    }

    ~Corners()
    {
        if(cornerTopLeft != Q_NULLPTR)
            delete cornerTopLeft;

        if(cornerBottomLeft != Q_NULLPTR)
            delete cornerBottomLeft;

        if(cornerTopRight != Q_NULLPTR)
            delete cornerTopRight;

        if(cornerBottomRight != Q_NULLPTR)
            delete cornerBottomRight;
    }

    ResizeRectCorner *cornerTopLeft;
    ResizeRectCorner *cornerBottomLeft;
    ResizeRectCorner *cornerTopRight;
    ResizeRectCorner *cornerBottomRight;
};

class ResizableGraphicsItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };
    ResizableGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    /**
     * \brief Copy constructor for #ResizableGraphicsItem
     * 
     * \warning This copy constructor does not copy QGraphicsItem from which
     * this class inherits. This is due to the copy constructor being private
     * in QGraphicsItem. As a workaround the parentItem of the item to copy is
     * passed to this item's QGraphicsItem constructor.
     * \warning This object does not copy child items! Derived classes are responsible 
     * for copying the child items in their copy constructors!
     * 
     * \note since copying the ResizeCorners makes the newly created ResizeCorners
     * child items of the old ResizeCorner's parent item, the parent has to be adjusted!
     */
    ResizableGraphicsItem(const ResizableGraphicsItem &other);
    /**
     * \brief Move constructor for #ResizableGraphicsItem
     * 
     * \warning This move constructor does not move QGraphicsItem from which
     * this class inherits. This is due to the move constructor being private
     * in QGraphicsItem. As a workaround the parentItem of the item to move is
     * passed to this item's QGraphicsItem constructor.
     * \warning This object does not move child items! Derived classes are responsible 
     * for moving the child items in their move constructors!
     * 
     * \note since moving the ResizeCorners makes the newly created ResizeCorners
     * child items of the old ResizeCorner's parent item, the parent has to be adjusted!
     */
    ResizableGraphicsItem(ResizableGraphicsItem &&other);
    virtual ~ResizableGraphicsItem();

    virtual void resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y);
    virtual void enableResizing(bool isOn = true);
    bool getResizeEnabled() const;

    virtual void setWidth(const qreal newWidth) = 0;
    virtual qreal getWidth() const = 0;
    virtual void setHeight(const qreal newHeight) = 0;
    virtual qreal getHeight() const = 0;

    void initResizeCorners();

    /* virtual void moveBy */

private:
    //PROBLEM: ResizeCorners are not displayed... problably positioning problem... investigate! //ToDO !!!
    Corners resizeCorners;
    /* ResizeRectCorner resizeCorners[4]; */
    bool resizeEnabled;

    // QGraphicsItem interface
public:
    /* virtual QRectF boundingRect() const = 0; */
    /* virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0; */
    /* virtual int type() const; */
};

#endif /* RESIZEABLEGRAPHICSITEM_H */
