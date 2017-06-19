#ifndef ISYSOVERVIEWLABELTRIGGER_H
#define ISYSOVERVIEWLABELTRIGGER_H

class SysOverviewTextLabel;
class IMsg;

#include "MessageTypeIdentifier.h"
#include "ISysOverviewObjectTriggerEvaluator.h"

#include <QSharedPointer>

class ISysOverviewLabelTrigger
{
public:
    enum TriggerType
    {
        TriggerType_TextChangeTrigger,
        TriggerType_NR_OF_TRIGGER_TYPES
    };

    virtual ~ISysOverviewLabelTrigger(){}

    virtual ISysOverviewLabelTrigger *clone() const = 0;

    virtual TriggerType getTriggerType() const = 0;

    virtual void trigger(
            const IMsg &msg
            ) = 0;

    virtual SysOvrvObjTriggerEvaluatorPtr getTriggerEvaluator() const = 0;
    virtual void setTriggerEvaluator(
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            ) = 0;

    virtual void setSysOverviewLabel(
            SysOverviewTextLabel *textLabel
            ) = 0;

    virtual bool isTriggered() const = 0;
};

typedef QSharedPointer<ISysOverviewLabelTrigger> SysOvrvLabelTriggerPtr;

template<class Derived>
class ISysOverviewLabelTriggerCRTPHelper :
        public ISysOverviewLabelTrigger
{
public:
    virtual ISysOverviewLabelTrigger *clone() const
    {
        new Derived(static_cast<const Derived &>(*this));
    }
};

#endif // ISYSOVERVIEWLABELTRIGGER_H
