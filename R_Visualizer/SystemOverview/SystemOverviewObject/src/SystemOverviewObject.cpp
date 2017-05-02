#include "SystemOverviewObject.h"

#include "ISysOverviewObjectManager.h"
#include "ISysOverviewObjectResizeManager.h"

#include "ISysOverviewShapeManager.h"

#include "SysOverviewTextLabel.h"

SystemOverviewObject::SystemOverviewObject(
            QGraphicsItem *parent = Q_NULLPTR
        ) :
    ISystemOverviewObject(parent)
    objectManager(new SysOverviewObjectShapeManager()),
    objColor(Qt::lightGray),
    objName("INVALID"),
    objBoundingRect(0,0,100,100)
{
}

SystemOverviewObject::SystemOverviewObject(
                const QColor &color,
                const QString &name,
                ISysOverviewObjectManager *objectManager,
                QGraphicsItem *parent = Q_NULLPTR
            ) :
    ISystemOverviewObject(parent),
    objectManager(objectManager),
    objColor(color),
    objName(objName),
    objBoundingRect(0,0,100,100)
{
}

SystemOverviewObject::

QRectF SystemOverviewObject::boundingRect() const
{
    return objBoundingRect;
}

void SystemOverviewObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void SystemOverviewObject::focusInEvent(QFocusEvent *event)
{
}

void SystemOverviewObject::focusOutEvent(QFocusEvent *event)
{
}

void SystemOverviewObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
}

void SystemOverviewObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
}

void SystemOverviewObject::setObjectName(const QString &name)
{
    objName = name;
}

QString SystemOverviewObject::getObjectName() const
{
    return objName;
}

ISysOverviewObjectResizeManager *SystemOverviewObject::getResizeManager() const
{
    return resizeManager;
}

void SystemOverviewObject::setResizeManager(ISysOverviewObjectResizeManager *resizeManager)
{
    if(resizeManager != Q_NULLPTR)
    {
        delete this->resizeManager;
        this->resizeManager = resizeManager;
        update();
    }
}

ISysOverviewObjectManager *SystemOverviewObject::getShapeManager() const
{
    return objManager;
}

void SystemOverviewObject::setShapeManager(ISysOverviewObjectManager *shapeManager)
{
    this->objManager = shapeManager;
    update();
}


void SystemOverviewObject::setSize(const QSizeF &size)
{
    resizeManager->setSize(size);
}

QSizeF SystemOverviewObject::getSize() const
{
    resizeManager->getSize();
}

void SystemOverviewObject::setColor(const QColor &color)
{
    objColor = color;
    update();
}

QColor SystemOverviewObject::getColor() const
{
    return objColor;
}

SysOverviewTextLabel *SystemOverviewObject::addLabel()
{

}

SysOverviewTextLabel *SystemOverviewObject::addLabel(SysOverviewTextLabel *label)
{
    label->setParentItem(this);
}

SysOverviewTextLabel *SystemOverviewObject::addLabel(const QString &text, const qreal x, const qreal y)
{

}

void SystemOverviewObject::removeLabel(SysOverviewTextLabel *label)
{
    label->setParentItem(Q_NULLPTR);
    //label->deleteLater();
}

QVector<SysOverviewTextLabel *> SystemOverviewObject::getLabels() const
{

}

void SystemOverviewObject::addChildObject(ISystemOverviewObject *child)
{

}

QVector<ISystemOverviewObject *> SystemOverviewObject::getChildObjects() const
{

}

void SystemOverviewObject::enableResizing(const bool enabled)
{

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
