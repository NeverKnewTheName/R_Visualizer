#ifndef SYSOVERVIEWOBJECTCOLORTRIGGER_H
#define SYSOVERVIEWOBJECTCOLORTRIGGER_H

#include "ISysOverviewObjectTrigger.h"

#include <QColor>

class SysOverviewObjectColorTrigger : public ISysOverviewObjectTrigger
{
public:
    SysOverviewObjectColorTrigger(
            ISystemOverviewObject *objectToTrigger,
            const QColor &colorToChangeTo,
            const MessageTypeIdentifier &msgTypeTrigger
            );
    virtual ~SysOverviewObjectColorTrigger();

    // ISysOverviewObjectTrigger interface
public:
    virtual QColor getTriggerColor() const;
    virtual void setTriggerColor(const QColor &triggerColor);
    virtual bool triggers(const MessageTypeIdentifier &msgType) const;
    virtual void trigger(const IMsg &msg);
    virtual void setSysOverviewObject(ISystemOverviewObject *sysOverviewObject);

private:
    void applyColorTrigger();

private:
    ISystemOverviewObject *objectToTrigger;
    QColor originalColor;
    QColor triggerColor;
    MessageTypeIdentifier msgTypeTrigger;
    bool isTriggered;
};

#endif // SYSOVERVIEWOBJECTCOLORTRIGGER_H
