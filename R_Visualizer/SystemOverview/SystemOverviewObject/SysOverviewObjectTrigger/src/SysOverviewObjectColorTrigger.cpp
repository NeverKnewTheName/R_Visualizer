#include "SysOverviewObjectColorTrigger.h"

#include "ISystemOverviewObject.h"
#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectColorManager.h"

#include "IMsg.h"

#include <QDebug>

SysOverviewObjectColorTrigger::SysOverviewObjectColorTrigger(
        ISystemOverviewObject *objectToTrigger,
        const QColor &colorToChangeTo,
        const MessageTypeIdentifier &msgTypeTrigger
        ) :
    objectToTrigger(objectToTrigger),
    originalColor(Qt::lightGray),
    triggerColor(colorToChangeTo),
    msgTypeTrigger(msgTypeTrigger),
    isTriggered(false)
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

SysOverviewObjectColorTrigger::~SysOverviewObjectColorTrigger()
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
        colorManager->setFillColor(originalColor);
        objManager->setColorManager(std::move(colorManager));
        objectToTrigger->setShapeManager(std::move(objManager));
    }
}

QColor SysOverviewObjectColorTrigger::getTriggerColor() const
{
    return triggerColor;
}

void SysOverviewObjectColorTrigger::setTriggerColor(const QColor &triggerColor)
{
    this->triggerColor = triggerColor;
    if(isTriggered)
    {
        applyColorTrigger();
    }
}

bool SysOverviewObjectColorTrigger::triggers(const MessageTypeIdentifier &msgType) const
{
    return msgTypeTrigger == msgType;
}

void SysOverviewObjectColorTrigger::trigger(const IMsg &msg)
{
    if(triggers(msg.getMsgType()))
    {
        qDebug() << "TRIGGER: " << objectToTrigger->getObjectName();
        isTriggered = true;
        applyColorTrigger();
    }
    else
    {
        isTriggered = false;
    }
}

void SysOverviewObjectColorTrigger::setSysOverviewObject(
        ISystemOverviewObject *sysOverviewObject
        )
{
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
        colorManager->setFillColor(originalColor);
        objManager->setColorManager(std::move(colorManager));
        objectToTrigger->setShapeManager(std::move(objManager));
    }
}
