#ifndef SYSOVERVIEWOBJECTCOLORTRIGGER_H
#define SYSOVERVIEWOBJECTCOLORTRIGGER_H

#include "ISysOverviewObjectTrigger.h"

#include <QColor>

class SysOverviewObjectColorTrigger :
        public ISysOverviewObjectTriggerCRTPHelper<SysOverviewObjectColorTrigger>
{
public:
    SysOverviewObjectColorTrigger(
            ISystemOverviewObject *objectToTrigger,
            const QColor &colorToChangeTo,
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            );
    SysOverviewObjectColorTrigger(
            const SysOverviewObjectColorTrigger &copy
            );
    virtual ~SysOverviewObjectColorTrigger();

    virtual QColor getTriggerColor() const;
    virtual void setTriggerColor(const QColor &triggerColor);

    // ISysOverviewObjectTrigger interface
public:
    virtual void trigger(const IMsg &msg);

    virtual SysOvrvObjTriggerEvaluatorPtr getTriggerEvaluator() const;

    virtual void setTriggerEvaluator(
            SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
            );

    virtual void setSysOverviewObject(
            ISystemOverviewObject *sysOverviewObject
            );

    virtual bool isTriggered() const;

private:
    void applyColorTrigger();

private:
    ISystemOverviewObject *objectToTrigger;
    SysOvrvObjTriggerEvaluatorPtr triggerEvaluator;
    QColor originalColor;
    QColor triggerColor;
    bool triggered;
};

#endif // SYSOVERVIEWOBJECTCOLORTRIGGER_H
