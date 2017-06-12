/**
 * @file SystemOverviewObject.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SystemOverviewObject
 */
#ifndef SYSTEMOVERVIEWOBJECT_H
#define SYSTEMOVERVIEWOBJECT_H

#include "ISystemOverviewObject.h"

#include <QString>
#include <QColor>
#include <QSizeF>

/**
 * @brief The SystemOverviewObject
 */
class SystemOverviewObject : public ISystemOverviewObject
{
public:
    SystemOverviewObject(
            QGraphicsItem *parent = Q_NULLPTR
            );
    SystemOverviewObject(
            const QString &name,
            const QSizeF &size = QSizeF(100,100),
            ISysOverviewObjectManager *objectManager = Q_NULLPTR,
            QGraphicsItem *parent = Q_NULLPTR
            );
    virtual ~SystemOverviewObject();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    // ISystemOverviewObject interface
public:
    virtual void setObjectName(const QString &name);
    virtual QString getObjectName() const;
    virtual SysOvrvObjectResizeManagerPtr getResizeManager() const;
    virtual void setResizeManager(SysOvrvObjectResizeManagerPtr resizeManager);
    virtual SysOvrvObjectManagerPtr getShapeManager() const;
    virtual void setShapeManager(SysOvrvObjectManagerPtr shapeManager);

    /* virtual SysOverviewTextLabel *addLabel(); */
    virtual SysOvrvTextLabelPtr addLabel(SysOvrvTextLabelPtr label);
    virtual SysOvrvTextLabelPtr addLabel(
            const QString &text,
            const qreal x,
            const qreal y
            );
    virtual void removeLabel(SysOvrvTextLabelPtr label);
    virtual QVector<SysOvrvTextLabelPtr > getLabels() const;
    SysOvrvTextLabelPtr convertLabelPointer(SysOverviewTextLabel *label) const;

    virtual void addChildObject(ISysOvrvObjPtr child);
    virtual void removeChildObject(ISysOvrvObjPtr child);
    virtual QVector<ISysOvrvObjPtr> getChildObjects() const;
    ISysOvrvObjPtr convertObjectPointer(ISystemOverviewObject *object) const;

    virtual void enableResizing(const bool enabled);
    virtual bool isResizingEnabled() const;
    virtual void enableMoving(const bool enabled);
    virtual bool isMovingEnabled() const;

    virtual void move(qreal x, qreal y);

private:
    SysOvrvObjectManagerPtr objManager;
    SysOvrvObjectResizeManagerPtr resizeManager;
    QVector<SysOvrvTextLabelPtr> textLabels;
    QVector<ISysOvrvObjPtr> childObjects;
    QString objName;
    bool resizeEnabled;
    bool movingEnabled;
};

#endif /* SYSTEMOVERVIEWOBJECT_H */
