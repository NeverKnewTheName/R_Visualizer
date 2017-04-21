/**
 * @file MsgIDFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Default implementation of #IMsgIDFilterStore
 */
#ifndef MSGIDFILTERSTORE_H
#define MSGIDFILTERSTORE_H

#include <QVector>
#include "IMsgIDFilterStore.h"

#include "MsgIDType.h"

/**
 * @brief The MsgIDFilterStore
 */
class MsgIDFilterStore : public IMsgIDFilterStore
{
public:
    MsgIDFilterStore();
    virtual ~MsgIDFilterStore();

    void addMsgID(const MsgIDType &msgIDToAdd);
    void removeMsgID(const MsgIDType &msgIDToRemove);

    bool containsMsgID(const MsgIDType &msgID) const;

    MsgIDType at(int index) const;

    int size() const;

    void clear();

private:
    QVector<MsgIDType> msgIDVector;

};

#endif /* MSGIDFILTERSTORE_H */
