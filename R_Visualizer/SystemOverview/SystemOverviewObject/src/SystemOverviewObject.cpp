#include "SystemOverviewObject.h"

#include "ISysOverviewObjectManager.h"
#include "ISysOverviewObjectResizeManager.h"

#include "ISysOverviewObjectManager.h"
#include "SysOverviewObjectShapeManager.h"

#include "SysOverviewObjectResizeManager.h"

#include "SysOverviewTextLabel.h"

#include <QCursor>

SystemOverviewObject::SystemOverviewObject(
            QGraphicsItem *parent
        ) :
    ISystemOverviewObject(parent),
    objManager(new SysOverviewObjectShapeManager(*this)),
    resizeManager(new SysOverviewObjectResizeManager(*this)),
    objName("INVALID")
{
    resizeManager->setSize(QSizeF(100,100));
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges |
            QGraphicsItem::ItemSendsScenePositionChanges
        );
}

SystemOverviewObject::SystemOverviewObject(
                const QString &name,
                const QSizeF &size,
                ISysOverviewObjectManager *objectManager,
                QGraphicsItem *parent
            ) :
    ISystemOverviewObject(parent),
    objManager(objectManager),
    resizeManager(new SysOverviewObjectResizeManager(*this)),
    objName(objName)
{
    resizeManager->setSize(size);
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges |
            QGraphicsItem::ItemSendsScenePositionChanges
                );
}

SystemOverviewObject::~SystemOverviewObject()
{

}

QRectF SystemOverviewObject::boundingRect() const
{
    return resizeManager->getBoundingRect();
}

void SystemOverviewObject::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget
        )
{
    painter->save();

    if(resizeEnabled)
    {
        resizeManager->paint(painter);
    }

    const QRectF &boundingRect = resizeManager->getBoundingRect();

    objManager->paint(painter, boundingRect, isSelected());

    painter->restore();
}

void SystemOverviewObject::focusInEvent(QFocusEvent *event)
{
}

void SystemOverviewObject::focusOutEvent(QFocusEvent *event)
{
}

void SystemOverviewObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::OpenHandCursor));
}

void SystemOverviewObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::ArrowCursor));
}

void SystemOverviewObject::setObjectName(const QString &name)
{
    objName = name;
}

QString SystemOverviewObject::getObjectName() const
{
    return objName;
}

SysOvrvObjectResizeManagerPtr SystemOverviewObject::getResizeManager() const
{
    return SysOvrvObjectResizeManagerPtr(resizeManager->clone());
}

void SystemOverviewObject::setResizeManager(SysOvrvObjectResizeManagerPtr resizeManager)
{
    this->resizeManager.reset(resizeManager.release());
//    this->resizeManager = resizeManager;
    update();
}

SysOvrvObjectManagerPtr SystemOverviewObject::getShapeManager() const
{
    return SysOvrvObjectManagerPtr(objManager->clone());
}

void SystemOverviewObject::setShapeManager(SysOvrvObjectManagerPtr shapeManager)
{
//    this->objManager = shapeManager;
    this->objManager.reset(shapeManager.release());
    update();
}

/* SysOverviewTextLabel *SystemOverviewObject::addLabel() */
/* { */
/* */
/* } */

SysOvrvTextLabelPtr SystemOverviewObject::addLabel(SysOvrvTextLabelPtr label)
{
    label->setParentItem(this);
    textLabels.append(label);
    label->setPos(mapToScene(pos()));
    return label;
}

SysOvrvTextLabelPtr SystemOverviewObject::addLabel(
        const QString &text,
        const qreal x,
        const qreal y
        )
{
    SysOvrvTextLabelPtr newLabel(new SysOverviewTextLabel(text,this));
    newLabel->setPos(x,y);
    return addLabel(newLabel);
}

void SystemOverviewObject::removeLabel(SysOvrvTextLabelPtr label)
{
    QGraphicsItem *labelParent = label->parentItem();
    if(labelParent == this)
    {
        label->setParentItem(Q_NULLPTR);
        textLabels.removeAll(label);
    }
    //label->deleteLater();
}

QVector<SysOvrvTextLabelPtr> SystemOverviewObject::getLabels() const
{
    return textLabels;
}

SysOvrvTextLabelPtr SystemOverviewObject::convertLabelPointer(SysOverviewTextLabel *label) const
{
    for(SysOvrvTextLabelPtr labelPtr : textLabels)
    {
        if(labelPtr.data() == label)
        {
            return labelPtr;
        }
    }
    return SysOvrvTextLabelPtr(Q_NULLPTR);
}

void SystemOverviewObject::addChildObject(ISysOvrvObjPtr child)
{
    child->setParentItem(this);
    if(!childObjects.contains(child))
    {
        childObjects.append(child);
    }
}

void SystemOverviewObject::removeChildObject(ISysOvrvObjPtr child)
{
    child->setParentItem(Q_NULLPTR);
    childObjects.removeAll(child);
}

QVector<ISysOvrvObjPtr> SystemOverviewObject::getChildObjects() const
{
    return childObjects;
}

ISysOvrvObjPtr SystemOverviewObject::convertObjectPointer(
        ISystemOverviewObject *object
        ) const
{
    for(ISysOvrvObjPtr objPtr : childObjects)
    {
        if(objPtr.data() == object)
        {
            return objPtr;
        }
    }
    return ISysOvrvObjPtr(Q_NULLPTR);
}

void SystemOverviewObject::enableResizing(const bool enabled)
{
    resizeManager->enableResize(enabled);
}

bool SystemOverviewObject::isResizingEnabled() const
{
}

void SystemOverviewObject::enableMoving(const bool enabled)
{

}

bool SystemOverviewObject::isMovingEnabled() const
{

}

void SystemOverviewObject::move(qreal x, qreal y)
{
    moveBy(x,y);
}
