#include "sysovrvtrigger.h"

#include <QDebug>


QString TriggerNames[SysOvrvTrigger::NrOfTriggers] =
{
    "StandardTrigger",
    "ColorChangeTrigger",
    "TextChangeTrigger"
};

SysOvrvTrigger::SysOvrvTrigger()
{
    //WHAT?
}

SysOvrvTrigger::SysOvrvTrigger(SysOvrvObject *objToTrigger) :
    m_pObjToTrigger(objToTrigger),
    type(StandardTrigger)
{

}

void SysOvrvTrigger::trigger(QByteArray &canData)
{
    qDebug() << "Triggered";
}

QString &SysOvrvTrigger::printToString()
{
    return TriggerNames[type];
}
