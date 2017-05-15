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
    resizeManager(
    objColor(Qt::lightGray),
    objName("INVALID"),
    objBoundingRect(0,0,100,100)
{
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphics::ItemSendsGeometryChanges |
            QGraphics::ItemSendsScenePositionChanges
        );
}

SystemOverviewObject::SystemOverviewObject(
                const QString &name,
                const QColor &color,
                const QSizeF &size,
                ISysOverviewObjectManager *objectManager,
                QGraphicsItem *parent = Q_NULLPTR
            ) :
    ISystemOverviewObject(parent),
    objectManager(objectManager),
    objName(objName),
    objColor(color),
    objBoundingRect(QPaintF(0,0),size)
{
    setFlags(
            QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphics::ItemSendsGeometryChanges |
            QGraphics::ItemSendsScenePositionChanges
        );
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
    if(resizeEnabled)
    {
        resizeManager->paint(painter);
    }

    const QRectF &boundingRect = resizeManager->getBoundingRect();

    QColor fillColor(getCurObjColor);

    shapeManager->paint(painter, boundingRect, fillColor);
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
