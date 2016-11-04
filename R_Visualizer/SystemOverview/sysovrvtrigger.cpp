#include "sysovrvtrigger.h"

#include <QDebug>

SysOvrvTrigger::SysOvrvTrigger(SysOvrvObject *objToTrigger) :
    m_pObjToTrigger(objToTrigger)
{

}

void SysOvrvTrigger::trigger(QByteArray &canData)
{
    qDebug() << "Triggered";
}
