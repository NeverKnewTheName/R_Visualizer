#include "SystemOverviewObject.h"

#include "ISysOverviewObjectResizeManager.h"
#include "SysOverviewObjectResizeManager.h"

#include "ISysOverviewObjectManager.h"
#include "SysOverviewObjectShapeManager.h"

#include "ISysOverviewObjectTrigger.h"

#include "SysOverviewTextLabel.h"

#include <QCursor>
#include <QFocusEvent>

SystemOverviewObject::SystemOverviewObject(
            QGraphicsItem *parent
        ) :
    ISystemOverviewObjectCRTPHelper(parent),
    objManager(
        new SysOverviewObjectShapeManager(
            this
            )
        ),
    resizeManager(
        new SysOverviewObjectResizeManager(
            this
            )
        ),
    objName("INVALID"),
    resizeEnabled(false),
    movingEnabled(false),
    editingEnabled(false),
    highlighted(false)
{
    resizeManager->setSize(QSizeF(100,100));
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges |
            QGraphicsItem::ItemSendsScenePositionChanges
        );
    updateToolTip();
}

SystemOverviewObject::SystemOverviewObject(
                const QString &name,
                const QSizeF &size,
                ISysOverviewObjectManager *objectManager,
                QGraphicsItem *parent
            ) :
    ISystemOverviewObjectCRTPHelper(parent),
    objManager(objectManager),
    resizeManager(
        new SysOverviewObjectResizeManager(
            this
            )
        ),
    objName(name),
    resizeEnabled(false),
    movingEnabled(false),
    editingEnabled(false),
    highlighted(false)
{
    resizeManager->setSize(size);
    objManager->setSysOverviewObject(this);
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges |
            QGraphicsItem::ItemSendsScenePositionChanges
                );
    updateToolTip();
}

SystemOverviewObject::SystemOverviewObject(
        const SystemOverviewObject &copy
        ) :
    ISystemOverviewObjectCRTPHelper(copy.parentItem()),
    objManager(copy.objManager->clone()),
    resizeManager(copy.resizeManager->clone()),
    objName(copy.objName),
    resizeEnabled(copy.resizeEnabled),
    movingEnabled(copy.movingEnabled),
    editingEnabled(copy.editingEnabled),
    highlighted(copy.highlighted)
{
    setPos(copy.pos());
    enableResizing(resizeEnabled);
    resizeManager->setSysOverviewObject(this);
    objManager->setSysOverviewObject(this);

    for(ISysOvrvObjPtr copyChild : copy.childObjects)
    {
        addChildObject(ISysOvrvObjPtr(copyChild->clone()));
    }
    for(SysOvrvTextLabelPtr copyLabel : copy.textLabels)
    {
        addLabel(
                    SysOvrvTextLabelPtr(
                        new SysOverviewTextLabel(*copyLabel)
                        )
                    );
    }

    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges |
            QGraphicsItem::ItemSendsScenePositionChanges
                );
    updateToolTip();
}

SystemOverviewObject::~SystemOverviewObject()
{
    objManager.reset();
    resizeManager.reset();
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

    ISysOverviewObjectManager::ObjectState state =
            ISysOverviewObjectManager::ObjectState_Normal;
    if(isSelected())
    {
        state =
                ISysOverviewObjectManager::ObjectState_Selected;
    }
    else if(highlighted)
    {
        state =
                ISysOverviewObjectManager::ObjectState_Highlighted;
    }

    objManager->paint(painter, boundingRect, state);

    painter->restore();
}

void SystemOverviewObject::focusInEvent(QFocusEvent *event)
{
    if(isMovingEnabled())
    {
        setCursor(QCursor(Qt::SizeAllCursor));
        setHighlighted(true);
    }
    if((parentItem() != Q_NULLPTR) && !isEditingEnabled())
    {
        ISystemOverviewObject *parent =
                dynamic_cast<ISystemOverviewObject *>(parentItem());
        if(parent != Q_NULLPTR)
        {
            parent->focusInEvent(event);
            return;
        }
    }
    else
    {
        for(ISysOvrvObjPtr child : childObjects)
        {
            child->setHighlighted(true);
        }
    }
}

void SystemOverviewObject::focusOutEvent(QFocusEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    setHighlighted(false);
    ISystemOverviewObject *parent =
            dynamic_cast<ISystemOverviewObject *>(parentItem());
    if(parent != Q_NULLPTR)
    {
        parent->focusOutEvent(event);
    }
    for(ISysOvrvObjPtr child : childObjects)
    {
        child->setHighlighted(false);
    }
    QGraphicsItem::focusOutEvent(event);
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

void SystemOverviewObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if((parentItem() != Q_NULLPTR) && !isMovingEnabled())
    {
        ISystemOverviewObject *parent =
                dynamic_cast<ISystemOverviewObject *>(parentItem());
        if(parent != Q_NULLPTR)
        {
            parent->mouseMoveEvent(event);
            return;
        }
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void SystemOverviewObject::setObjectName(const QString &name)
{
    objName = name;
    updateToolTip();
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

SysOvrvTextLabelPtr SystemOverviewObject::addLabel(SysOvrvTextLabelPtr label)
{
    label->setParentItem(this);
    textLabels.append(label);
    label->setPos(mapToScene(pos()));
    return addChildLabel(label);
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

SysOvrvTextLabelPtr SystemOverviewObject::addChildLabel(SysOvrvTextLabelPtr label)
{
    globalTextLabels.append(label);
    ISystemOverviewObject *parent =
            dynamic_cast<ISystemOverviewObject*>(parentItem());
    if(parent != Q_NULLPTR)
    {
        parent->addChildLabel(label);
    }

    return label;
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

QVector<SysOvrvTextLabelPtr> SystemOverviewObject::getGlobalLabes() const
{
    return globalTextLabels;
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
    resizeEnabled = enabled;
    resizeManager->enableResize(enabled);
}

void SystemOverviewObject::enableChildrenResizing(const bool enabled)
{
    for(ISysOvrvObjPtr child : childObjects)
    {
        child->enableResizing(enabled);
    }
}

bool SystemOverviewObject::isResizingEnabled() const
{
    return resizeEnabled;
}

void SystemOverviewObject::enableMoving(const bool enabled)
{
    movingEnabled = enabled;
//    setFlag(QGraphicsItem::ItemIsMovable, enabled);
}

void SystemOverviewObject::enableChildrenMoving(const bool enabled)
{
    for(ISysOvrvObjPtr child : childObjects)
    {
        child->enableMoving(enabled);
    }
}

bool SystemOverviewObject::isMovingEnabled() const
{
    return movingEnabled;
}

void SystemOverviewObject::enableEditing(const bool enabled)
{
    editingEnabled = enabled;
    setFlag(QGraphicsItem::ItemIsSelectable,enabled);
}

void SystemOverviewObject::enableChildrenEditing(const bool enabled)
{
    for(ISysOvrvObjPtr child : childObjects)
    {
        child->enableEditing(enabled);
    }
}

bool SystemOverviewObject::isEditingEnabled() const
{
    return editingEnabled;
}

void SystemOverviewObject::move(qreal x, qreal y)
{
    prepareGeometryChange();
    moveBy(x,y);
    update();
}

void SystemOverviewObject::prepareSizeChange()
{
    prepareGeometryChange();
}

void SystemOverviewObject::setHighlighted(const bool enabled)
{
    highlighted = enabled;
    for(ISysOvrvObjPtr child : childObjects)
    {
        child->setHighlighted(enabled);
    }
    update();
}

void SystemOverviewObject::addObjectTrigger(SysOvrvObjTriggerPtr triggerToAdd)
{
    localTriggers.append(triggerToAdd);
    addChildObjectTrigger(triggerToAdd);
}

void SystemOverviewObject::addChildObjectTrigger(SysOvrvObjTriggerPtr triggerToAdd)
{
    globalTriggers.append(triggerToAdd);

    ISystemOverviewObject *parent =
            dynamic_cast<ISystemOverviewObject*>(parentItem());
    if(parent != Q_NULLPTR)
    {
        parent->addChildObjectTrigger(triggerToAdd);
    }
}

void SystemOverviewObject::removeObjectTrigger(SysOvrvObjTriggerPtr triggerToRemove)
{
    if(localTriggers.removeAll(triggerToRemove) > 0)
    {
        removeChildObjectTrigger(triggerToRemove);
    }
}

void SystemOverviewObject::removeChildObjectTrigger(SysOvrvObjTriggerPtr triggerToRemove)
{
    globalTriggers.removeAll(triggerToRemove);

    ISystemOverviewObject *parent =
            dynamic_cast<ISystemOverviewObject*>(parentItem());
    if(parent != Q_NULLPTR)
    {
        parent->removeChildObjectTrigger(triggerToRemove);
    }
}

QVector<SysOvrvObjTriggerPtr> SystemOverviewObject::getLocalObjectTriggers() const
{
    return localTriggers;
}

QVector<SysOvrvObjTriggerPtr> SystemOverviewObject::getGlobalObjectTriggers() const
{
    return globalTriggers;
}

void SystemOverviewObject::updateToolTip()
{
    QString childTip("Nr. ChildObjects: ");
    childTip.append(QString::number(childObjects.size(),10));
    setToolTip(objName + QString("\n") + childTip);
}
