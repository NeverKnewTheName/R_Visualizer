/**
 * @file IMsgStreamStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief Provides the interface for MessageStream stores
 */
#ifndef IMSGSTREAMSTORE_H
#define IMSGSTREAMSTORE_H

/* #include <QMetaObject> */
#include <QObject>
#include "ITimestampedMsg.h"

class IPrettyTimestampedMsg;

/**
 * @brief The IMsgStreamStore interface
 */
class IMsgStreamStore : public QObject
{
    Q_OBJECT
public:
    IMsgStreamStore(QObject *parent = Q_NULLPTR) : QObject(parent){}
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
    void sgnl_msgAboutToBeAppended(
            /* const IPrettyTimestampedMsg &msgToAppend */
            );

    /**
     * @brief This signal is emitted when a pretty message was appended to the
     * store
     */
    void sgnl_msgAppended(
            /* const IPrettyTimestampedMsg &msgToAppend */
            );

    /**
     * @brief Emitted before a pretty message is prepended to the store
     * 
     * This signal tells related models that a message has passed the filter
     * and is now about to be appended to the store.
     */
    void sgnl_msgAboutToBePrepended(
            /* const IPrettyTimestampedMsg &msgToAppend */
            );

    /**
     * @brief This signal is emitted when a pretty message was prepended to the
     * store
     */
    void sgnl_msgPrepended(
            /* const IPrettyTimestampedMsg &msgToAppend */
            );

    /**
     * @brief Emitted when a message will be appended to the store that causes
     * the store to overflow
     * 
     * When the store overflows the first message is discarded
     */
    void sgnl_storeAboutToOverflow();

    /**
     * @brief Emitted when a message was appended to the store that caused
     * the store to overflow
     * 
     * When the store overflows the first message is discarded
     */
    void sgnl_storeOverflow();

    /**
     * @brief Emitted when a message will be appended to the store that causes
     * the store to underflow
     * 
     * When the store underflows the last message is discarded
     */
    void sgnl_storeAboutToUnderflow();

    /**
     * @brief Emitted when a message was appended to the store that caused
     * the store to underflow
     * 
     * When the store underflows the last message is discarded
     */
    void sgnl_storeUnderflow();

    /**
     * @brief Emitted before the store is cleared
     * 
     * This signals tells related models that all data is about to be removed
     * from the store
     */
    void sgnl_storeAboutToBeCleared();

    /**
     * @brief This signal is emitted when the store is cleared
     */
    void sgnl_storeCleared();

public slots:
    /**
     * @brief Slot to append the given pretty messages
     * 
     * @note Calls #appendMsg
     */
    virtual void slt_appendMsg(const IPrettyTimestampedMsg &msgToAppend)
    {
        appendMsg(msgToAppend);
    }

    /**
     * @brief Slot to prepend the given pretty messages
     * 
     * @note Calls #prependMsg
     */
    virtual void slt_prependMsg(const IPrettyTimestampedMsg &msgToPrepend)
    {
        prependMsg(msgToPrepend);
    }

    /**
     * @brief Slot to clear the store removing all contained messsages
     * 
     * @note Calls #clear
     */
    virtual void slt_clearStore()
    {
        clear();
    }
};

/* Q_DECLARE_INTERFACE(IMsgStreamStore, "IMsgStreamStore") */

#endif /* IMSGSTREAMSTORE_H */
