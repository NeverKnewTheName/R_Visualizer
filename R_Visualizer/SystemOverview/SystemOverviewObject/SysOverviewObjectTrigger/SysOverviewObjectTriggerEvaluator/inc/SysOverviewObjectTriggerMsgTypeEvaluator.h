#ifndef SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATOR_H
#define SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATOR_H

#include "ISysOverviewObjectTriggerEvaluator.h"
#include "MessageTypeIdentifier.h"

class SysOverviewObjectTriggerMsgTypeEvaluator :
        public ISysOverviewObjectTriggerEvaluatorCRTPHelper<SysOverviewObjectTriggerMsgTypeEvaluator>
{
public:
    SysOverviewObjectTriggerMsgTypeEvaluator(
            const MessageTypeIdentifier &msgType
            );

    virtual ~SysOverviewObjectTriggerMsgTypeEvaluator();

    // ISysOverviewObjectTriggerEvaluator interface
public:
    virtual ISysOverviewObjectTriggerEvaluator::EvaluatorType getType() const;
    virtual MessageTypeIdentifier getMsgType() const;
    virtual void setMsgType(const MessageTypeIdentifier &msgType);
    virtual bool evaluate(const IMsg &msgToEvaluate) const;

private:
    MessageTypeIdentifier msgType;
};

#endif // SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATOR_H
