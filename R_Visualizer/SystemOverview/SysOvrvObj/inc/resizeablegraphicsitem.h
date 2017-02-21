#ifndef RESIZEABLEGRAPHICSITEM_H
#define RESIZEABLEGRAPHICSITEM_H

#include <QGraphicsItem>

#include "resizecornermanager.h"
#include "resizerectcorner.h"

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

    virtual void update(const QRectF &rect = QRectF());

    virtual void resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y);
    void enableResizing(bool isOn = true);
    bool getResizeEnabled() const;

    virtual void setWidth(const qreal newWidth) = 0;
    virtual qreal getWidth() const = 0;
    virtual void setHeight(const qreal newHeight) = 0;
    virtual qreal getHeight() const = 0;

    void initResizeCorners();

    /* virtual void moveBy */

private:
    //PROBLEM: ResizeCorners are not displayed... problably positioning problem... investigate! //ToDO !!!
    ResizeCornerManager resizeCorners;
    /* ResizeRectCorner resizeCorners[4]; */
    bool resizeEnabled;

    // QGraphicsItem interface
public:
    /* virtual QRectF boundingRect() const = 0; */
    /* virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0; */
    /* virtual int type() const; */
};

#endif /* RESIZEABLEGRAPHICSITEM_H */
