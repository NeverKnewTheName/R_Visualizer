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
            const QColor &color = QColor(Qt::lightGray),
            const QSizeF &size = QSizeF(100,100),
            ISysOverviewObjectManager *objectManager,
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
    virtual ISysOverviewObjectResizeManager *getResizeManager() const;
    virtual void setResizeManager(ISysOverviewObjectResizeManager *resizeManager);
    virtual ISysOverviewObjectManager *getShapeManager() const;
    virtual void setShapeManager(ISysOverviewObjectManager *shapeManager);

    virtual void setSize(const QSizeF &size);
    virtual QSizeF getSize() const;
    virtual void setColor(const QColor &color);
    virtual QColor getColor() const;

    virtual SysOverviewTextLabel *addLabel();
    virtual SysOverviewTextLabel *addLabel(SysOverviewTextLabel *label);
    virtual SysOverviewTextLabel *addLabel(
            const QString &text,
            const qreal x,
            const qreal y
            );
    virtual void removeLabel(SysOverviewTextLabel *label);
    virtual QVector<SysOverviewTextLabel *> getLabels() const;

    virtual void addChildObject(ISystemOverviewObject *child);
    virtual QVector<ISystemOverviewObject *> getChildObjects() const;

    virtual void enableResizing(const bool enabled);
    virtual bool isResizingEnabled() const;
    virtual void enableMoving(const bool enabled);
    virtual bool isMovingEnabled() const;

private:
    ISysOverviewObjectManager *objManager;
    ISysOverviewObjectResizeManager *resizeManager;
    QString objName;
    QColor objColor;
    QRectF objBoundingRect;
    bool resizeEnabled;
    bool movingEnabled;
};

#endif /* SYSTEMOVERVIEWOBJECT_H */
