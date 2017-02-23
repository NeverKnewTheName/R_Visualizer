#include "resizecornermanager.h"

#include "resizerectcorner.h"
#include "resizeablegraphicsitem.h"

#include <QDebug>

ResizeCornerManager::ResizeCornerManager(const qreal size, ResizableGraphicsItem *parent) :
    parentItem(parent),
    cornerTopLeft(new ResizeRectCorner(ResizeRectCorner::TopLeftCorner, size, parent)),
    cornerBottomLeft(new ResizeRectCorner(ResizeRectCorner::BottomLeftCorner, size, parent)),
    cornerTopRight(new ResizeRectCorner(ResizeRectCorner::TopRightCorner, size, parent)),
    cornerBottomRight(new ResizeRectCorner(ResizeRectCorner::BottomRightCorner, size, parent))
{
    qDebug() << __PRETTY_FUNCTION__;
}

ResizeCornerManager::ResizeCornerManager(const ResizeCornerManager &other) :
    parentItem(other.parentItem),
    cornerTopLeft(new ResizeRectCorner(*other.cornerTopLeft)),
    cornerBottomLeft(new ResizeRectCorner(*other.cornerBottomLeft)),
    cornerTopRight(new ResizeRectCorner(*other.cornerTopRight)),
    cornerBottomRight(new ResizeRectCorner(*other.cornerBottomRight))
{
    qDebug() << __PRETTY_FUNCTION__;
}

ResizeCornerManager::ResizeCornerManager(ResizeCornerManager &&other) :
    parentItem(other.parentItem),
    cornerTopLeft(other.cornerTopLeft),
    cornerBottomLeft(other.cornerBottomLeft),
    cornerTopRight(other.cornerTopRight),
    cornerBottomRight(other.cornerBottomRight)
{
    qDebug() << __PRETTY_FUNCTION__;

    other.setParentItem(Q_NULLPTR);
    other.cornerTopLeft = Q_NULLPTR;
    other.cornerBottomLeft= Q_NULLPTR;
    other.cornerTopRight = Q_NULLPTR;
    other.cornerBottomRight = Q_NULLPTR;
}

ResizeCornerManager::~ResizeCornerManager()
{
    qDebug() << __PRETTY_FUNCTION__;

    if(cornerTopLeft != Q_NULLPTR)
        delete cornerTopLeft;

    if(cornerBottomLeft != Q_NULLPTR)
        delete cornerBottomLeft;

    if(cornerTopRight != Q_NULLPTR)
        delete cornerTopRight;

    if(cornerBottomRight != Q_NULLPTR)
        delete cornerBottomRight;
}

void ResizeCornerManager::update(const QRectF &rect)
{
    /* qDebug() << __PRETTY_FUNCTION__; */
    if(parentItem == Q_NULLPTR)
        return;

    const QRectF &boundingRect = parentItem->boundingRect();

    /* qDebug() << "Bounding Rect: " << boundingRect; */

    if(cornerTopLeft != Q_NULLPTR)
    {
        cornerTopLeft->updatePosition();
        cornerTopLeft->update(rect);
        /* qDebug() << "CornerTopLeft: " << cornerTopLeft->boundingRect(); */
    }

    if(cornerBottomLeft != Q_NULLPTR)
    {
        cornerBottomLeft->updatePosition();
        cornerBottomLeft->update(rect);
        /* qDebug() << "CornerBottomLeft: " << cornerBottomLeft->boundingRect(); */
    }

    if(cornerTopRight != Q_NULLPTR)
    {
        cornerTopRight->updatePosition();
        cornerTopRight->update(rect);
        /* qDebug() << "CornerTopRight: " << cornerTopRight->boundingRect(); */
    }

    if(cornerBottomRight != Q_NULLPTR)
    {
        cornerBottomRight->updatePosition();
        cornerBottomRight->update(rect);
        /* qDebug() << "CornerBottomRight: " << cornerBottomRight->boundingRect(); */
    }
}

void ResizeCornerManager::setParentItem(ResizableGraphicsItem *parent)
{
    parentItem = parent;
    if(cornerTopLeft != Q_NULLPTR)
        cornerTopLeft->setParentItem((parent));

    if(cornerBottomLeft != Q_NULLPTR)
        cornerBottomLeft->setParentItem((parent));

    if(cornerTopRight != Q_NULLPTR)
        cornerTopRight->setParentItem((parent));

    if(cornerBottomRight != Q_NULLPTR)
        cornerBottomRight->setParentItem((parent));
}

void ResizeCornerManager::setVisible(const bool isVisible)
{
    if(cornerTopLeft != Q_NULLPTR)
        cornerTopLeft->setVisible(isVisible);

    if(cornerBottomLeft != Q_NULLPTR)
        cornerBottomLeft->setVisible(isVisible);

    if(cornerTopRight != Q_NULLPTR)
        cornerTopRight->setVisible(isVisible);

    if(cornerBottomRight != Q_NULLPTR)
        cornerBottomRight->setVisible(isVisible);

    update();
}
