#ifndef SYSOVERVIEWLABELTEXTCHANGETRIGGER_H
#define SYSOVERVIEWLABELTEXTCHANGETRIGGER_H

#include "ISysOverviewLabelTrigger.h"

class SysOverviewLabelTextChangeTrigger :
        public ISysOverviewLabelTriggerCRTPHelper<SysOverviewLabelTextChangeTrigger>
{
public:
    SysOverviewLabelTextChangeTrigger(
            SysOverviewTextLabel *textLabel,
            const QString &triggerText = QString("Triggered"),
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator = Q_NULLPTR
            );
    SysOverviewLabelTextChangeTrigger(
            const SysOverviewLabelTextChangeTrigger &copy
            );

    virtual ~SysOverviewLabelTextChangeTrigger();

    QString getTriggerText() const;
    void setTriggerText(const QString &value);

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
    QString triggerText;
    bool triggered;

    // ISysOverviewLabelTrigger interface
public:
    virtual ISysOverviewLabelTrigger::TriggerType getTriggerType() const;
};

#endif // SYSOVERVIEWLABELTEXTCHANGETRIGGER_H
