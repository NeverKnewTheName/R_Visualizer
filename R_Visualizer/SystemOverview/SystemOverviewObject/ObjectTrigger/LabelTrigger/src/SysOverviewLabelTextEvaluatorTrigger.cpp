#include "SysOverviewLabelTextEvaluatorTrigger.h"
#include "SysOverviewObjectTriggerDSLEvaluator.h"

#include "IMsg.h"
#include "SysOverviewTextLabel.h"

SysOverviewLabelTextEvaluatorTrigger::SysOverviewLabelTextEvaluatorTrigger(
        SysOverviewTextLabel *textLabel,
        SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
        ) :
    textLabel(textLabel),
    triggerEvaluator(std::move(triggerEvaluator)),
    triggered(false)
{
}

SysOverviewLabelTextEvaluatorTrigger::SysOverviewLabelTextEvaluatorTrigger(
        const SysOverviewLabelTextEvaluatorTrigger &copy
        ) :
    textLabel(copy.textLabel),
    triggerEvaluator(copy.triggerEvaluator->clone()),
    triggered(copy.triggered)
{
}

SysOverviewLabelTextEvaluatorTrigger::~SysOverviewLabelTextEvaluatorTrigger()
{

}

ISysOverviewLabelTrigger::TriggerType SysOverviewLabelTextEvaluatorTrigger::getTriggerType() const
{
    return ISysOverviewLabelTrigger::TriggerType_TextEvaluatorTrigger;
}

void SysOverviewLabelTextEvaluatorTrigger::trigger(const IMsg &msg)
{
    if(triggerEvaluator->getMsgType() == msg.getMsgType())
    {
        SysOverviewObjectTriggerDSLEvaluator *dslEvaluator =
                dynamic_cast<SysOverviewObjectTriggerDSLEvaluator *>(
                    triggerEvaluator.get()
                    );
        if(dslEvaluator == Q_NULLPTR)
        {
            return;
        }

        const QString &newLabelText =
                dslEvaluator->evaluateToString(msg);
        if(newLabelText.isEmpty())
        {
            return;
        }

        this->textLabel->setLabelText(newLabelText);
    }
}

SysOvrvObjTriggerEvaluatorPtr SysOverviewLabelTextEvaluatorTrigger::getTriggerEvaluator() const
{
    return SysOvrvObjTriggerEvaluatorPtr(triggerEvaluator->clone());
}

void SysOverviewLabelTextEvaluatorTrigger::setTriggerEvaluator(SysOvrvObjTriggerEvaluatorPtr triggerEvaluator)
{
    this->triggerEvaluator = std::move(triggerEvaluator);
}

void SysOverviewLabelTextEvaluatorTrigger::setSysOverviewLabel(SysOverviewTextLabel *textLabel)
{
    this->textLabel = textLabel;
}

bool SysOverviewLabelTextEvaluatorTrigger::isTriggered() const
{
    return triggered;
}
