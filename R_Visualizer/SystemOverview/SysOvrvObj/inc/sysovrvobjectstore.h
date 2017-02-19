#ifndef SYSOVRVOBJECTSTORE_H
#define SYSOVRVOBJECTSTORE_H

#include "sysovrvobject.h"
#include "can_packet.h"

#include <QObject>
#include <QHash>

class Msg;

struct TriggerIdentifier
{
    const MsgIDType id;
    const MsgCodeType code;
    TriggerIdentifier(const MsgIDType id, const MsgCodeType code) :
        id(id),
        code(code)
    {}
    
    TriggerIdentifier(const TriggerIdentifier &other) :
        id(other.id),
        code(other.code)
    {}

    bool operator==(const TriggerIdentifier &other)
    {
        return ((id == other.id) && (code == other.code));
    }

};

inline bool operator==(const TriggerIdentifier &triggerID1, const TriggerIdentifier &triggerID2)
{
    return triggerID1 == triggerID2;
}

inline uint qHash(const TriggerIdentifier &key, uint seed)
{
    return ((key.id << (8*sizeof(MsgCodeType))) & key.code) + seed;
}



class SysOvrvObjectStore : public QObject
{
    Q_OBJECT

public:
    explicit SysOvrvObjectStore(QObject *parent = 0);

    QVector<SysOvrvObject *> getObjectStore() const;
    void addMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj);
    void removeMesageToWatch(const MsgIDType id, const MsgCodeType code, SysOvrvObject *relatedSysOvrvObj);

    void addObject(SysOvrvObject *obj);
    void removeObject(SysOvrvObject *obj);
    void updateObject(SysOvrvObject *obj);

private:
    QVector<SysOvrvObject*> objectStore;
    QHash<TriggerIdentifier, QVector<SysOvrvObject*>> objectTriggerStore;

signals:
    void sgnl_objectAddedToStore(SysOvrvObject *addedObject);
    void sgnl_objectRemovedFromStore(SysOvrvObject *removedObject);

public slots:
    void slt_receiveMessage(const Msg &newMsg);

    void slt_addObject(SysOvrvObject *objToAdd);
    void slt_removeObject(SysOvrvObject *objToRmv);
    void slt_updateObject(SysOvrvObject *objToUpdt);
};

#endif // SYSOVRVOBJECTSTORE_H
