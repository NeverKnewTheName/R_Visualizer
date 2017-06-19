/**
 * @file ISystemOverviewObject.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The ISystemOverviewObject interface
 */
#ifndef ISYSTEMOVERVIEWOBJECT_H
#define ISYSTEMOVERVIEWOBJECT_H

#include <QVector>

#include <QString>
#include <QSize>
#include <QColor>

#include <QGraphicsItem>
#include <QSharedPointer>

#include "ISysOverviewObjectTrigger.h"

#include "IFileParsable.h"
#include "fileparser.h"

class ISysOverviewObjectResizeManager;
class ISysOverviewObjectManager;


class SysOverviewTextLabel;

#include <memory>

typedef QSharedPointer<SysOverviewTextLabel> SysOvrvTextLabelPtr;
typedef std::unique_ptr<ISysOverviewObjectResizeManager> SysOvrvObjectResizeManagerPtr;
typedef std::unique_ptr<ISysOverviewObjectManager> SysOvrvObjectManagerPtr;

class ISystemOverviewObject;
typedef QSharedPointer<ISystemOverviewObject> ISysOvrvObjPtr;

/**
 * @brief The ISystemOverviewObject interface
 */
class ISystemOverviewObject :
        public QGraphicsItem,
        public IFileParsable
{
public:
    ISystemOverviewObject(
            QGraphicsItem *parent = Q_NULLPTR
            ) :
        QGraphicsItem(parent)
    {}
    virtual ~ISystemOverviewObject(){}

    virtual ISystemOverviewObject *clone() const = 0;

public:
    virtual void focusInEvent(QFocusEvent *event) = 0;
    virtual void focusOutEvent(QFocusEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;

    virtual void setObjectName(const QString &name) = 0;
    virtual QString getObjectName() const = 0;

    virtual SysOvrvObjectResizeManagerPtr getResizeManager() const = 0;
    virtual void setResizeManager(
            SysOvrvObjectResizeManagerPtr resizeManager
            ) = 0;

    virtual SysOvrvObjectManagerPtr getShapeManager() const = 0;
    virtual void setShapeManager(
            SysOvrvObjectManagerPtr shapeManager
            ) = 0;

    /* virtual SysOverviewTextLabel *addLabel() = 0; */
    virtual SysOvrvTextLabelPtr addLabel(SysOvrvTextLabelPtr label) = 0;
    virtual SysOvrvTextLabelPtr addLabel(
            const QString &text,
            const qreal x,
            const qreal y
            ) = 0;
    virtual SysOvrvTextLabelPtr addChildLabel(SysOvrvTextLabelPtr label) = 0;

    virtual void removeLabel(SysOvrvTextLabelPtr label) = 0;
    virtual QVector<SysOvrvTextLabelPtr > getLabels() const = 0;
    virtual QVector<SysOvrvTextLabelPtr> getGlobalLabes() const = 0;
    virtual SysOvrvTextLabelPtr convertLabelPointer(
            SysOverviewTextLabel *label
            ) const = 0;

    virtual void addChildObject(ISysOvrvObjPtr child) = 0;
    virtual void removeChildObject(ISysOvrvObjPtr child) = 0;
    virtual QVector<ISysOvrvObjPtr > getChildObjects() const = 0;
    virtual ISysOvrvObjPtr convertObjectPointer(
            ISystemOverviewObject *object
            ) const = 0;

    virtual void enableResizing(const bool enabled) = 0;
    virtual void enableChildrenResizing(const bool enabled) = 0;
    virtual bool isResizingEnabled() const = 0;

    virtual void enableMoving(const bool enabled) = 0;
    virtual void enableChildrenMoving(const bool enabled) = 0;
    virtual bool isMovingEnabled() const = 0;

    virtual void enableEditing(const bool enabled) = 0;
    virtual void enableChildrenEditing(const bool enabled) = 0;
    virtual bool isEditingEnabled() const = 0;

    virtual void move(qreal x, qreal y) = 0;
    virtual void prepareSizeChange() = 0;

    virtual void setHighlighted(const bool enabled) = 0;

    virtual void addObjectTrigger(
            SysOvrvObjTriggerPtr triggerToAdd
            ) = 0;
    virtual void addChildObjectTrigger(
            SysOvrvObjTriggerPtr triggerToAdd
            ) = 0;

    virtual void removeObjectTrigger(
            SysOvrvObjTriggerPtr triggerToRemove
            ) = 0;
    virtual void removeChildObjectTrigger(
            SysOvrvObjTriggerPtr triggerToRemove
            ) = 0;

    virtual QVector<SysOvrvObjTriggerPtr> getLocalObjectTriggers() const = 0;
    virtual QVector<SysOvrvObjTriggerPtr> getGlobalObjectTriggers() const = 0;

};

Q_DECLARE_METATYPE(ISysOvrvObjPtr)

template<class Derived>
class ISystemOverviewObjectCRTPHelper :
        public ISystemOverviewObject
{
public:
    using ISystemOverviewObject::ISystemOverviewObject;

    virtual ISystemOverviewObject *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }

    // IFileParsable interface
public:
    virtual void accept(FileParser *visitor)
    {
        visitor->visit(*this);
    }
};

#endif /* ISYSTEMOVERVIEWOBJECT_H */
