/**
 * @file IMsgCodeFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Interface for #MsgCodeType storages
 */
#ifndef IMSGCODEFILTERSTORE_H
#define IMSGCODEFILTERSTORE_H

#include "MsgCodeType.h"

/**
 * @brief The IMsgCodeFilterStore interface
 */
class IMsgCodeFilterStore
{
public:
    virtual ~IMsgCodeFilterStore(){}

    virtual void addMsgCode(const MsgCodeType &msgCodeToAdd) = 0;
    virtual void removeMsgCode(const MsgCodeType &msgCodeToRemove) = 0;

    virtual bool containsMsgCode(const MsgCodeType &msgCode) const = 0;

    virtual MsgCodeType at(int index) const = 0;

    virtual void clear() = 0;
};

#endif /* IMSGCODEFILTERSTORE_H */
