#ifndef MSGIDFILTERSTORE_H
#define MSGIDFILTERSTORE_H

#include <QVector>
#include "IMsgIDFilterStore.h"

class MsgIDFilterStore : public IMsgIDFilterStore
{
public:
    MsgIDFilterStore();
    virtual ~MsgIDFilterStore();

    void addMsgID(const MsgIDType &msgIDToAdd);
    void removeMsgID(const MsgIDType &msgIDToRemove);

    bool containsMsgID(const MsgIDType &msgID) const;

    void clear();

private:
    QVector<MsgIDType> msgIDVector;

};

#endif /* MSGIDFILTERSTORE_H */
