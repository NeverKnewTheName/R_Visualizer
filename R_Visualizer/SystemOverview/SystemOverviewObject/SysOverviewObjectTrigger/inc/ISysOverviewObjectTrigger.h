#ifndef ISYSOVERVIEWOBJECTTRIGGER_H
#define ISYSOVERVIEWOBJECTTRIGGER_H

class ISystemOverviewObject;
class IMsg;

#include "MessageTypeIdentifier.h"
#include "ISysOverviewObjectTriggerEvaluator.h"

#include <QSharedPointer>

class ISysOverviewObjectTrigger
{
public:
    virtual ~ISysOverviewObjectTrigger(){}

    virtual QColor getTriggerColor() const = 0;
    virtual void setTriggerColor(const QColor &triggerColor) = 0;

    virtual void trigger(
            const IMsg &msg
            ) = 0;

    virtual SysOvrvObjTriggerEvaluatorPtr getTriggerEvaluator() const = 0;

    virtual void setTriggerEvaluator(
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            ) = 0;

    virtual void setSysOverviewObject(
            ISystemOverviewObject *sysOverviewObject
            ) = 0;

    virtual bool isTriggered() const = 0;
};

typedef QSharedPointer<ISysOverviewObjectTrigger> SysOvrvObjTriggerPtr;

#endif // ISYSOVERVIEWOBJECTTRIGGER_H
