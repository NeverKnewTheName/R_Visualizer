#ifndef ISYSOVERVIEWOBJECTTRIGGER_H
#define ISYSOVERVIEWOBJECTTRIGGER_H

class ISystemOverviewObject;
class IMsg;

#include "MessageTypeIdentifier.h"

class ISysOverviewObjectTrigger
{
public:
    virtual ~ISysOverviewObjectTrigger(){}

    virtual QColor getTriggerColor() const = 0;
    virtual void setTriggerColor(const QColor &triggerColor) = 0;

    virtual bool triggers(
            const MessageTypeIdentifier &msgType
            ) const = 0;

    virtual void trigger(
            const IMsg &msg
            ) = 0;

    virtual void setSysOverviewObject(
            ISystemOverviewObject *sysOverviewObject
            ) = 0;
};

#endif // ISYSOVERVIEWOBJECTTRIGGER_H
