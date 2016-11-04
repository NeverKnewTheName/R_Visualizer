#ifndef SYSOVRVTRIGGER_H
#define SYSOVRVTRIGGER_H

#include <QByteArray>

class SysOvrvObject;

class SysOvrvTrigger
{
public:
    SysOvrvTrigger();
    SysOvrvTrigger(SysOvrvObject *objToTrigger);
    void trigger(QByteArray &canData);
    QString &printToString();
    enum TriggerType {
        StandardTrigger,
        ColorChangeTrigger,
        TextChangeTrigger,
        NrOfTriggers
    };

private:
    SysOvrvObject *m_pObjToTrigger;
    TriggerType type;
};

//Q_DECLARE_METATYPE(SysOvrvTrigger);

#endif // SYSOVRVTRIGGER_H
