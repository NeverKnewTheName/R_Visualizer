#ifndef TRIGGERABLESYSOVRVOBJ_H
#define TRIGGERABLESYSOVRVOBJ_H

//#include "sysovrvobject.h"

//class TriggerableSysOvrvObj
//{
//public:
//    explicit TriggerableSysOvrvObj(QGraphicsItem *parent = Q_NULLPTR);
//    TriggerableSysOvrvObj(const TriggerableSysOvrvObj &ToCopy);
//    TriggerableSysOvrvObj(TriggerableSysOvrvObj &&ToMove);
//    ~TriggerableSysOvrvObj();

//    void addTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newTrigger);
//    void addChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newChildTrigger);
//    void removeTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove);
//    void removeChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove);
//    void msgReceived(const MsgIDType id, const MsgCodeType code, QByteArray &canData);
//    QList<MsgIDType> getTriggerIDs() const;
//    QList<MsgCodeType> getTriggerCodesToID(const MsgIDType id) const;
//    QVector<SysOvrvTrigger *> getTriggersToIDandCode(const MsgIDType id, const MsgCodeType code);

//    QHash<MsgIDType, QHash<MsgCodeType, QVector<SysOvrvTrigger*>>> GlobalTriggerStore;
//    QHash<MsgIDType, QHash<MsgCodeType, QVector<SysOvrvTrigger*>>> LocalTriggerStore;
//};

#endif // TRIGGERABLESYSOVRVOBJ_H
