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

class IPrettyTimestampedMsg;

/**
 * @brief The IMsgStreamStore interface
 */
class IMsgStreamStore
{
public:
    virtual ~IMsgStreamStore(){}

    /**
     * @brief Appends a copy of the passed pretty message to the store
     */
    virtual bool appendMsg(const IPrettyTimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Prepends a copy of the passed pretty message to the store
     */
    virtual bool prependMsg(const IPrettyTimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Returns a constant reference to the pretty message in the store at
     * index
     */
    virtual IPrettyTimestampedMsg &at(const int index) const = 0;

    /**
     * @brief Returns a modifiable reference to the pretty message in the store
     * at index
     */
    virtual IPrettyTimestampedMsg &at(const int index) = 0;

    /**
     * @brief Returns the current size of the store
     */
    virtual int size() const = 0;

    /**
     * @brief Clears the store removing all messages
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief This signal is emitted when a pretty message was appended to the
     * store
     */
    virtual void sgnl_msgAppended() = 0;

    /**
     * @brief This signal is emitted when a pretty message was prepended to the
     * store
     */
    virtual void sgnl_msgPrepended() = 0;

    /**
     * @brief This signal is emitted when the store is cleared
     */
    virtual void sgnl_storeCleared() = 0;

public slots:
    /**
     * @brief Slot to append the given pretty messages
     */
    virtual void slt_appendMsg(const IPrettyTimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Slot to prepend the given pretty messages
     */
    virtual void slt_prependMsg(const IPrettyTimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Slot to clear the store removing all contained messsages
     */
    virtual void slt_clearStore() = 0;
};

#endif /* IMSGSTREAMSTORE_H */
