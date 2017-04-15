/**
 * @file ISendMsgPackageStore.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for message package stores
 */
#ifndef ISENDMSGPACKAGESTORE_H
#define ISENDMSGPACKAGESTORE_H

#include "IPrettyMsg.h"

/**
 * @brief The ISendMsgPackageStore interface
 */
class ISendMsgPackageStore
{
public:
    virtual ~ISendMsgPackageStore();

    virtual void appendMsg(const IPrettyMsg &msgToAppend) = 0;
};

#endif /* ISENDMSGPACKAGESTORE_H */
