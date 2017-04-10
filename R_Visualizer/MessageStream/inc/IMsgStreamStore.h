/**
 * @file IMsgStreamStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief Provides the interface for MessageStream stores
 */
#ifndef IMSGSTREAMSTORE_H
#define IMSGSTREAMSTORE_H

#include "ITimestampedMsg.h"

/**
 * @brief The IMsgStreamStore interface
 */
class IMsgStreamStore
{
public:
    virtual ~IMsgStreamStore();

    /**
     * @brief Appends a copy of the passed message to the store
     */
    virtual void appendMessage(const ITimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Returns a constant reference to the message in the store at index
     */
    virtual ITimestampedMsg &at(const int index) const = 0;
};

#endif /* IMSGSTREAMSTORE_H */
