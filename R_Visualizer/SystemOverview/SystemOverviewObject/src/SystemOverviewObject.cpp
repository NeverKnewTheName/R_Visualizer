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
    objColor(Qt::lightGray),
    objName("INVALID"),
    objBoundingRect(0,0,100,100)
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
                const QColor &color,
                const QSizeF &size,
                ISysOverviewObjectManager *objectManager,
                QGraphicsItem *parent
            ) :
    ISystemOverviewObject(parent),
    objManager(objectManager),
    resizeManager(new SysOverviewObjectResizeManager(*this)),
    objName(objName),
    objColor(color),
    objBoundingRect(QPointF(0,0),size)
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

void SystemOverviewObject::setSize(const QSizeF &size)
{
    resizeManager->setSize(size);
}

QSizeF SystemOverviewObject::getSize() const
{
    return resizeManager->getSize();
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

/* SysOverviewTextLabel *SystemOverviewObject::addLabel() */
/* { */
/* */
/* } */

SysOvrvTextLabelPtr SystemOverviewObject::addLabel(SysOvrvTextLabelPtr label)
{
    label->setParentItem(this);
}

SysOvrvTextLabelPtr SystemOverviewObject::addLabel(
        const QString &text,
        const qreal x,
        const qreal y
        )
{

}

void SystemOverviewObject::removeLabel(SysOvrvTextLabelPtr label)
{
    label->setParentItem(Q_NULLPTR);
    //label->deleteLater();
}

QVector<SysOvrvTextLabelPtr> SystemOverviewObject::getLabels() const
{

}

void SystemOverviewObject::addChildObject(ISysOvrvObjPtr child)
{

}

QVector<ISysOvrvObjPtr> SystemOverviewObject::getChildObjects() const
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

QColor SystemOverviewObject::getCurObjColor() const
{
    if(isSelected())
    {
        QColor objColor(getColor());
        if(objColor.alphaF()<0.1)
        {
            objColor.setAlphaF(0.1);
        }
        return objColor.darker();
    }
    else
    {
        return getColor();
    }
}
