#ifndef MSGIDMAPPINGSTORE_H
#define MSGIDMAPPINGSTORE_H

#include "IMsgIDMappingStore.h"
#include "IMsgIDRep.h"

#include <QHash>

class MsgIDMappingStore
{
public:
    MsgIDMappingStore();
    virtual ~MsgIDMappingStore();

    /* MsgIDType getMsgIDToName(const QString &name) const; */
    /* QString getNameToMsgID(const MsgIDType msgID) const; */
    /* QColor getColorToMsgID(const MsgIDType msgID) const; */
    /* QColor getColorToName(const QString &name) const; */

    IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID) const;
    IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID);

    bool contains(const MsgIDType msgID) const;
    bool contains(const IMsgIDRep &msgIDRep) const;

    void addMsgIDMapping(const IMsgIDRep &msgIDRepToAdd);
    void removeMsgIDMapping(const MsgIDType relatedMsgID);

    void clear();

private:
    QHash<MsgIDType, IMsgIDRep> msgIDRepStore;
};

#endif /* MSGIDMAPPINGSTORE_H */
