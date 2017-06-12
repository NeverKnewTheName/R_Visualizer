#include "SysOverviewObjectTriggerMsgTypeEvaluator.h"

#include "IMsg.h"
#include "MessageTypeIdentifier.h"

SysOverviewObjectTriggerMsgTypeEvaluator::SysOverviewObjectTriggerMsgTypeEvaluator(
            const MessageTypeIdentifier &msgType
        ) :
    msgType(msgType)
{

}

SysOverviewObjectTriggerMsgTypeEvaluator::~SysOverviewObjectTriggerMsgTypeEvaluator()
{

}


ISysOverviewObjectTriggerEvaluator::EvaluatorType SysOverviewObjectTriggerMsgTypeEvaluator::getType() const
{
    return ISysOverviewObjectTriggerEvaluator::EvaluatorType_MsgTypeEvaluator;
}

MessageTypeIdentifier SysOverviewObjectTriggerMsgTypeEvaluator::getMsgType() const
{
    return msgType;
}

void SysOverviewObjectTriggerMsgTypeEvaluator::setMsgType(
        const MessageTypeIdentifier &msgType
        )
{
    this->msgType = msgType;
}

bool SysOverviewObjectTriggerMsgTypeEvaluator::evaluate(const IMsg &msgToEvaluate) const
{
    return msgToEvaluate.getMsgType() == this->msgType;
}
