#ifndef SYSOVERVIEWLABELTEXTCHANGETRIGGER_H
#define SYSOVERVIEWLABELTEXTCHANGETRIGGER_H

#include "ISysOverviewLabelTrigger.h"

class SysOverviewLabelTextChangeTrigger :
        public ISysOverviewLabelTriggerCRTPHelper<SysOverviewLabelTextChangeTrigger>
{
public:
    SysOverviewLabelTextChangeTrigger(
            SysOverviewTextLabel *textLabel,
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            );
    SysOverviewLabelTextChangeTrigger(
            const SysOverviewLabelTextChangeTrigger &copy
            );

    virtual ~SysOverviewLabelTextChangeTrigger();

    // ISysOverviewLabelTrigger interface
public:
    virtual void trigger(const IMsg &msg);
    virtual SysOvrvObjTriggerEvaluatorPtr getTriggerEvaluator() const;
    virtual void setTriggerEvaluator(
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            );
    virtual void setSysOverviewLabel(
            SysOverviewTextLabel *textLabel
            );
    virtual bool isTriggered() const;

private:
    SysOverviewTextLabel *textLabel;
    SysOvrvObjTriggerEvaluatorPtr triggerEvaluator;
    bool triggered;
};

#endif // SYSOVERVIEWLABELTEXTCHANGETRIGGER_H
