//#include "triggerablesysovrvobj.h"

//TriggerableSysOvrvObj::TriggerableSysOvrvObj(QGraphicsItem *parent) :
//    SysOvrvObject::SysOvrvObject(parent)
//{

//}

//TriggerableSysOvrvObj::TriggerableSysOvrvObj(const TriggerableSysOvrvObj &ToCopy) :
//    SysOvrvObject::SysOvrvObject(ToCopy)
//{

//}

//TriggerableSysOvrvObj::TriggerableSysOvrvObj(TriggerableSysOvrvObj &&ToMove) :
//    SysOvrvObject::SysOvrvObject(ToMove)
//{

//}

//TriggerableSysOvrvObj::~TriggerableSysOvrvObj()
//{

//}

//void TriggerableSysOvrvObj::addTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newTrigger)
//{
//    LocalTriggerStore[id][code].append(newTrigger);
//    addChildsTrigger(id, code, newTrigger);
//}

//void TriggerableSysOvrvObj::addChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newChildTrigger)
//{
//    GlobalTriggerStore[id][code].append(newChildTrigger);
//    TriggerableSysOvrvObj *parent = dynamic_cast<TriggerableSysOvrvObj*>(parentItem());
//    if(parent != Q_NULLPTR)
//        parent->addChildsTrigger(id, code, newChildTrigger);
//}

//void TriggerableSysOvrvObj::removeTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove)
//{
//    LocalTriggerStore[id][code].removeAll(triggerToRemove);
//    removeChildsTrigger(id, code, triggerToRemove);
//}

//void TriggerableSysOvrvObj::removeChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove)
//{
//    GlobalTriggerStore[id][code].removeAll(triggerToRemove);
//    TriggerableSysOvrvObj *parent = dynamic_cast<TriggerableSysOvrvObj*>(parentItem());
//    if(parent != Q_NULLPTR)
//        parent->removeChildsTrigger(id, code, triggerToRemove);
//}

//void TriggerableSysOvrvObj::msgReceived(const MsgIDType id, const MsgCodeType code, QByteArray &canData)
//{
//    QVector<SysOvrvTrigger*> triggers = GlobalTriggerStore[id][code];
//    for(SysOvrvTrigger *trigger : triggers)
//    {
//        trigger->trigger(canData);
//    }
//}

//QList<MsgIDType> TriggerableSysOvrvObj::getTriggerIDs() const
//{
//    return GlobalTriggerStore.uniqueKeys();
//}

//QList<MsgCodeType> TriggerableSysOvrvObj::getTriggerCodesToID(const MsgIDType id) const
//{
//    return GlobalTriggerStore.value(id).uniqueKeys();
//}

//QVector<SysOvrvTrigger *> TriggerableSysOvrvObj::getTriggersToIDandCode(const MsgIDType id, const MsgCodeType code)
//{
//    return GlobalTriggerStore.value(id).value(code);
//}
