#ifndef SYSOVRVTRIGGER_H
#define SYSOVRVTRIGGER_H

#include <QByteArray>

class SysOvrvObject;

class SysOvrvTrigger
{
public:
    SysOvrvTrigger(SysOvrvObject *objToTrigger);
    void trigger(QByteArray &canData);
    enum TriggerType {
        ColorChangeTrigger,
        TextChangeTrigger
    };

private:
    SysOvrvObject *m_pObjToTrigger;
    TriggerType type;
};

#endif // SYSOVRVTRIGGER_H
