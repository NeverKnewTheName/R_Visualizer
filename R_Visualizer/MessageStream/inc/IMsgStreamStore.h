/**
 * @file IMsgStreamStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief Provides the interface for MessageStream stores
 */
#ifndef IMSGSTREAMSTORE_H
#define IMSGSTREAMSTORE_H

#include <QMetaObject>
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
    virtual IPrettyTimestampedMsg &appendMsg(
            const IPrettyTimestampedMsg &msgToAppend
            ) = 0;

    /**
     * @brief Constructs a new #PrettyTimestampedMsg from the given
     * #ITimestampedMsg and appends this message to the store
     * 
     * \returns a modfiable reference to the new #IPrettyTimestampedMsg
     */
    virtual IPrettyTimestampedMsg &appendMsg(
            const ITimestampedMsg &msgToAppend
            ) = 0;

    /**
     * @brief Prepends a copy of the passed pretty message to the store
     */
    virtual IPrettyTimestampedMsg &prependMsg(
            const IPrettyTimestampedMsg &msgToPrepend
            ) = 0;

    /**
     * @brief Constructs a new #PrettyTimestampedMsg from the given
     * #ITimestampedMsg and prepends this message to the store
     * 
     * \returns a modfiable reference to the new #IPrettyTimestampedMsg
     */
    virtual IPrettyTimestampedMsg &prependMsg(
            const ITimestampedMsg &msgToPrepend
            ) = 0;

    /**
     * @brief Returns a constant reference to the pretty message in the store at
     * index
     */
    virtual const IPrettyTimestampedMsg &at(const int index) const = 0;

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
     * @brief Emitted before a pretty message is appended to the store
     * 
     * This signal tells related models, that a message has passed the filter
     * and is now about to be appended to the store.
     */
    virtual void sgnl_msgAboutToBeAppended() = 0;

    /**
     * @brief This signal is emitted when a pretty message was appended to the
     * store
     */
    virtual void sgnl_msgAppended() = 0;

    /**
     * @brief Emitted before a pretty message is prepended to the store
     * 
     * This signal tells related models that a message has passed the filter
     * and is now about to be appended to the store.
     */
    virtual void sgnl_msgAboutToBePrepended() = 0;

    /**
     * @brief This signal is emitted when a pretty message was prepended to the
     * store
     */
    virtual void sgnl_msgPrepended() = 0;

    /**
     * @brief Emitted when a message will be appended to the store that causes
     * the store to overflow
     * 
     * When the store overflows the first message is discarded
     */
    virtual void sgnl_storeAboutToOverflow() = 0;

    /**
     * @brief Emitted when a message was appended to the store that caused
     * the store to overflow
     * 
     * When the store overflows the first message is discarded
     */
    virtual void sgnl_storeOverflow() = 0;

    /**
     * @brief Emitted when a message will be appended to the store that causes
     * the store to underflow
     * 
     * When the store underflows the last message is discarded
     */
    virtual void sgnl_storeAboutToUnderflow() = 0;

    /**
     * @brief Emitted when a message was appended to the store that caused
     * the store to underflow
     * 
     * When the store underflows the last message is discarded
     */
    virtual void sgnl_storeUnderflow() = 0;

    /**
     * @brief Emitted before the store is cleared
     * 
     * This signals tells related models that all data is about to be removed
     * from the store
     */
    virtual void sgnl_storeAboutToBeCleared() = 0;

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

Q_DECLARE_INTERFACE(IMsgStreamStore, "IMsgStreamStore")

#endif /* IMSGSTREAMSTORE_H */
