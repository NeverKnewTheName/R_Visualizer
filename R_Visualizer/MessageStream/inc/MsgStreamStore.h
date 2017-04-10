/**
 * @file MsgStreamStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The store that keeps track of messages for the MessageStream
 */
#ifndef MSGSTREAMSTORE_H
#define MSGSTREAMSTORE_H

#include "IMsgStreamStore.h"

#include "msgstorage.h"

/**
 * @brief The MsgStreamStore
 */
class MsgStreamStore : public IMsgStreamStore
{
public:
    MsgStreamStore(TimestampedMsgStorage &msgStorage);
    virtual ~MsgStreamStore();

private:
    /**
     * @brief Storage for timestamped messages
     */
    TimestampedMsgStorage &msgStorage;
};

#endif /* MSGSTREAMSTORE_H */
