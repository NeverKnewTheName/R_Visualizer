#include "SysOverviewLabelTextChangeTrigger.h"
#include "SysOverviewObjectTriggerDSLEvaluator.h"

#include "IMsg.h"
#include "SysOverviewTextLabel.h"

SysOverviewLabelTextChangeTrigger::SysOverviewLabelTextChangeTrigger(
        SysOverviewTextLabel *textLabel,
        SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
        ) :
    textLabel(textLabel),
    triggerEvaluator(std::move(triggerEvaluator)),
    triggered(false)
{
}

SysOverviewLabelTextChangeTrigger::SysOverviewLabelTextChangeTrigger(
        const SysOverviewLabelTextChangeTrigger &copy
        ) :
    textLabel(copy.textLabel),
    triggerEvaluator(copy.triggerEvaluator->clone()),
    triggered(copy.triggered)
{

}

SysOverviewLabelTextChangeTrigger::~SysOverviewLabelTextChangeTrigger()
{
}

void SysOverviewLabelTextChangeTrigger::trigger(const IMsg &msg)
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

SysOvrvObjTriggerEvaluatorPtr SysOverviewLabelTextChangeTrigger::getTriggerEvaluator() const
{
    return SysOvrvObjTriggerEvaluatorPtr(triggerEvaluator->clone());
}

void SysOverviewLabelTextChangeTrigger::setTriggerEvaluator(
        SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
        )
{
    this->triggerEvaluator = std::move(triggerEvaluator);
}

void SysOverviewLabelTextChangeTrigger::setSysOverviewLabel(
        SysOverviewTextLabel *textLabel
        )
{
    this->textLabel = textLabel;
}

bool SysOverviewLabelTextChangeTrigger::isTriggered() const
{
    return triggered;
}


ISysOverviewLabelTrigger::TriggerType SysOverviewLabelTextChangeTrigger::getTriggerType() const
{
    return ISysOverviewLabelTrigger::TriggerType_TextChangeTrigger;
}
