#ifndef IMSGIDFILTERSTORE_H
#define IMSGIDFILTERSTORE_H

#include "MsgIDType.h"

class IMsgIDFilterStore
{
public:
    virtual ~IMsgIDFilterStore(){}

    virtual void addMsgID(const MsgIDType &msgIDtoAdd) = 0;
    virtual void removeMsgID(const MsgIDType &msgIDtoRemove) = 0;

    virtual bool containsMsgID(const MsgIDType &msgID) const = 0;

    virtual MsgIDType at(int index) const = 0;

    virtual void clear() = 0;
};

#endif /* IMSGIDFILTERSTORE_H */

