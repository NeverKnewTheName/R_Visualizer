#ifndef IMSGCODEFILTERSTORE_H
#define IMSGCODEFILTERSTORE_H

#include "MsgCodeType.h"

class IMsgCodeFilterStore
{
public:
    virtual ~IMsgCodeFilterStore(){}

    virtual void addMsgCode(const MsgCodeType &msgCodeToAdd) = 0;
    virtual void removeMsgCode(const MsgCodeType &msgCodeToRemove) = 0;

    virtual bool containsMsgCode(const MsgCodeType &msgCode) const = 0;

    virtual void clear() = 0;
};

#endif /* IMSGCODEFILTERSTORE_H */
