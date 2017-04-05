#ifndef MSGCODEFILTERSTORE_H
#define MSGCODEFILTERSTORE_H

#include <QVector>
#include "IMsgCodeFilterStore.h"

class MsgCodeFilterStore : public IMsgCodeFilterStore
{
public:
    MsgCodeFilterStore();
    virtual ~MsgCodeFilterStore();

    void addMsgCode(const MsgCodeType &msgCodeToAdd);
    void removeMsgCode(const MsgCodeType &msgCodeToRemove);

    bool containsMsgCode(const MsgCodeType &msgCode) const;

    void clear();

private:
    QVector<MsgCodeType> msgCodeVector;
};

#endif /* MSGCODEFILTERSTORE_H */
