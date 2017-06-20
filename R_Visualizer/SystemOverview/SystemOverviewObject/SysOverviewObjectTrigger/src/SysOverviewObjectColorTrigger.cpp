#include "SysOverviewObjectColorTrigger.h"

#include "ISystemOverviewObject.h"
#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectColorManager.h"

#include "IMsg.h"

#include <QDebug>

SysOverviewObjectColorTrigger::SysOverviewObjectColorTrigger(
        ISystemOverviewObject *objectToTrigger
        ) :
    objectToTrigger(objectToTrigger),
    triggerEvaluator(),
    originalColor(Qt::lightGray),
    triggerColor(Qt::gray),
    triggered(false)
{
    SysOvrvObjectShapeManagerPtr objManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    objectToTrigger->getShapeManager().release()
                    )
                );
    if(objManager.get() != nullptr)
    {
        SysOvrvObjColorManagerPtr colorManager =
                objManager->getColorManager();
        originalColor = colorManager->getFillColor();
    }
}

SysOverviewObjectColorTrigger::SysOverviewObjectColorTrigger(
        ISystemOverviewObject *objectToTrigger,
        const QColor &colorToChangeTo,
        SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
        ) :
    objectToTrigger(objectToTrigger),
    triggerEvaluator(std::move(triggerEvaluator)),
    originalColor(Qt::lightGray),
    triggerColor(colorToChangeTo),
    triggered(false)
{
    SysOvrvObjectShapeManagerPtr objManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    objectToTrigger->getShapeManager().release()
                    )
                );
    if(objManager.get() != nullptr)
    {
        SysOvrvObjColorManagerPtr colorManager =
                objManager->getColorManager();
        originalColor = colorManager->getFillColor();
    }
}

SysOverviewObjectColorTrigger::SysOverviewObjectColorTrigger(
        const SysOverviewObjectColorTrigger &copy
        ) :
    objectToTrigger(copy.objectToTrigger),
    triggerEvaluator(copy.triggerEvaluator->clone()),
    originalColor(copy.originalColor),
    triggerColor(copy.triggerColor),
    triggered(copy.triggered)
{

}

SysOverviewObjectColorTrigger::~SysOverviewObjectColorTrigger()
{
//    SysOvrvObjectShapeManagerPtr objManager(
//                dynamic_cast<SysOverviewObjectShapeManager *>(
//                    objectToTrigger->getShapeManager().release()
//                    )
//                );
//    if(objManager.get() != nullptr)
//    {
//        SysOvrvObjColorManagerPtr colorManager =
//                objManager->getColorManager();
//        colorManager->setFillColor(originalColor);
//        objManager->setColorManager(std::move(colorManager));
//        objectToTrigger->setShapeManager(std::move(objManager));
//    }
}

QColor SysOverviewObjectColorTrigger::getTriggerColor() const
{
    return triggerColor;
}

void SysOverviewObjectColorTrigger::setTriggerColor(const QColor &triggerColor)
{
    this->triggerColor = triggerColor;
    if(triggered)
    {
        applyColorTrigger();
    }
}

QColor SysOverviewObjectColorTrigger::getOriginalColor() const
{
    return originalColor;
}

void SysOverviewObjectColorTrigger::trigger(const IMsg &msg)
{
    triggered = triggerEvaluator->evaluate(msg);
    if(triggered)
    {
        qDebug() << "TRIGGER: " << objectToTrigger->getObjectName();
        applyColorTrigger();
    }
}

SysOvrvObjTriggerEvaluatorPtr SysOverviewObjectColorTrigger::getTriggerEvaluator() const
{
    return SysOvrvObjTriggerEvaluatorPtr(triggerEvaluator->clone());
}

void SysOverviewObjectColorTrigger::setTriggerEvaluator(
        SysOvrvObjTriggerEvaluatorPtr triggerEvaluator
        )
{
    this->triggerEvaluator = std::move(triggerEvaluator);
}

void SysOverviewObjectColorTrigger::setSysOverviewObject(
        ISystemOverviewObject *sysOverviewObject
        )
{
    this->objectToTrigger = sysOverviewObject;
}

bool SysOverviewObjectColorTrigger::isTriggered() const
{
    return triggered;
}

void SysOverviewObjectColorTrigger::applyColorTrigger()
{
    SysOvrvObjectShapeManagerPtr objManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    objectToTrigger->getShapeManager().release()
                    )
                );
    if(objManager.get() != nullptr)
    {
        SysOvrvObjColorManagerPtr colorManager =
                objManager->getColorManager();
        colorManager->setFillColor(
                    triggered ? triggerColor : originalColor
                                );
        objManager->setColorManager(std::move(colorManager));
        objectToTrigger->setShapeManager(std::move(objManager));
    }
}


ISysOverviewObjectTrigger::TriggerType SysOverviewObjectColorTrigger::getTriggerType() const
{
    return ISysOverviewObjectTrigger::TriggerType_ColorChangeTrigger;
}
