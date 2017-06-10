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

class ISysOverviewObjectResizeManager;
class ISysOverviewObjectManager;

class SysOverviewTextLabel;

#include <memory>

typedef std::unique_ptr<SysOverviewTextLabel> SysOvrvTextLabelPtr;
typedef std::unique_ptr<ISysOverviewObjectResizeManager> SysOvrvObjectResizeManagerPtr;
typedef std::unique_ptr<ISysOverviewObjectManager> SysOvrvObjectManagerPtr;

class ISystemOverviewObject;
typedef QSharedPointer<ISystemOverviewObject> ISysOvrvObjPtr;

/**
 * @brief The ISystemOverviewObject interface
 */
class ISystemOverviewObject : public QGraphicsItem
{
public:
    ISystemOverviewObject(
            QGraphicsItem *parent = Q_NULLPTR
            ) :
        QGraphicsItem(parent)
    {}
    virtual ~ISystemOverviewObject(){}

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

    virtual void setSize(const QSizeF &size) = 0;
    virtual QSizeF getSize() const = 0;

    virtual void setColor(const QColor &color) = 0;
    virtual QColor getColor() const = 0;
    virtual QColor getCurObjColor() const = 0;

    /* virtual SysOverviewTextLabel *addLabel() = 0; */
    virtual SysOvrvTextLabelPtr addLabel(SysOvrvTextLabelPtr label) = 0;
    virtual SysOvrvTextLabelPtr addLabel(
            const QString &text,
            const qreal x,
            const qreal y
            ) = 0;

    virtual void removeLabel(SysOvrvTextLabelPtr label) = 0;

    virtual QVector<SysOvrvTextLabelPtr > getLabels() const = 0;

    virtual void addChildObject(ISysOvrvObjPtr child) = 0;
    virtual QVector<ISysOvrvObjPtr > getChildObjects() const = 0;

    virtual void enableResizing(const bool enabled) = 0;
    virtual bool isResizingEnabled() const = 0;

    virtual void enableMoving(const bool enabled) = 0;
    virtual bool isMovingEnabled() const = 0;
};


Q_DECLARE_METATYPE(ISysOvrvObjPtr)

#endif /* ISYSTEMOVERVIEWOBJECT_H */
