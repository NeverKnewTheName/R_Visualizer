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
    enum TriggerType
    {
        TriggerType_ColorChangeTrigger,
        TriggerType_NR_OF_TRIGGER_TYPES
    };

    virtual ~ISysOverviewObjectTrigger(){}

    virtual ISysOverviewObjectTrigger *clone() const = 0;

    virtual TriggerType getTriggerType() const = 0;

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

template<class Derived>
class ISysOverviewObjectTriggerCRTPHelper :
        public ISysOverviewObjectTrigger
{
public:
    virtual ISysOverviewObjectTrigger *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
};

#endif // ISYSOVERVIEWOBJECTTRIGGER_H
