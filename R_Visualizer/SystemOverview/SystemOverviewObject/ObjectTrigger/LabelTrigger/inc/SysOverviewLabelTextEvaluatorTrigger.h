#ifndef SYSOVERVIEWLABELTEXTEVALUATORTRIGGER_H
#define SYSOVERVIEWLABELTEXTEVALUATORTRIGGER_H

#include "ISysOverviewLabelTrigger.h"


class SysOverviewLabelTextEvaluatorTrigger :
        public ISysOverviewLabelTriggerCRTPHelper<SysOverviewLabelTextEvaluatorTrigger>
{
public:
    SysOverviewLabelTextEvaluatorTrigger(
            SysOverviewTextLabel *textLabel,
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator = Q_NULLPTR
            );

    SysOverviewLabelTextEvaluatorTrigger(
            const SysOverviewLabelTextEvaluatorTrigger &copy
            );

    virtual ~SysOverviewLabelTextEvaluatorTrigger();

private:
    SysOverviewTextLabel *textLabel;
    SysOvrvObjTriggerEvaluatorPtr triggerEvaluator;
    bool triggered;


    // ISysOverviewLabelTrigger interface
public:
    virtual TriggerType getTriggerType() const;
    virtual void trigger(const IMsg &msg);
    virtual SysOvrvObjTriggerEvaluatorPtr getTriggerEvaluator() const;
    virtual void setTriggerEvaluator(SysOvrvObjTriggerEvaluatorPtr triggerEvaluator);
    virtual void setSysOverviewLabel(SysOverviewTextLabel *textLabel);
    virtual bool isTriggered() const;
};

#endif // SYSOVERVIEWLABELTEXTEVALUATORTRIGGER_H
