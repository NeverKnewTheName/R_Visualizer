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
#include <QObject>

#include "rsimpleringbuff.h"
#include "PrettyTimestampedMsg.h"

/**
 * @brief The MsgStreamStore
 */
class MsgStreamStore : public QObject, public IMsgStreamStore
{
    Q_OBJECT
public:
    MsgStreamStore(const int bufferSize, QObject *parent = Q_NULLPTR);
    virtual ~MsgStreamStore();

    /**
     * @brief Appends a copy of the passed pretty message to the store
     * 
     * \note constructs an empty #PrettyTimestampedMsg<TimestampedMsg> if none
     * is given
     * 
     * \returns A reference to the appended IPrettyTimestampedMsg
     */
    virtual IPrettyTimestampedMsg &appendMsg(
            const IPrettyTimestampedMsg &msgToAppend =
            PrettyTimestampedMsg<TimestampedMsg>()
            );

    /**
     * @brief Prepends a copy of the passed pretty message to the store
     */
    virtual IPrettyTimestampedMsg &prependMsg(
            const IPrettyTimestampedMsg &msgToPrepend =
            PrettyTimestampedMsg<TimestampedMsg>()

    /**
     * @brief Returns a constant reference to the pretty message in the store at
     * index
     */
    virtual IPrettyTimestampedMsg &at(const int index) const;

    /**
     * @brief Returns a modifiable reference to the pretty message in the store
     * at index
     */
    virtual IPrettyTimestampedMsg &at(const int index);

    /**
     * @brief Returns the current size of the store
     */
    virtual int size() const;

    /**
     * @brief Clears the store removing all messages
     */
    virtual void clear();

signals:
    /**
     * @brief This signal is emitted when a pretty message was appended to the
     * store
     */
    virtual void sgnl_msgAppended();

    /**
     * @brief This signal is emitted when a pretty message was prepended to the
     * store
     */
    virtual void sgnl_msgPrepended();

    /**
     * @brief This signal is emitted when the store is cleared
     */
    virtual void sgnl_storeCleared();

public slots:
    /**
     * @brief Slot to append the given pretty messages
     */
    virtual void slt_appendMsg(const IPrettyTimestampedMsg &msgToAppend);

    /**
     * @brief Slot to prepend the given pretty messages
     */
    virtual void slt_prependMsg(const IPrettyTimestampedMsg &msgToAppend);

    /**
     * @brief Slot to clear the store removing all contained messsages
     */
    virtual void slt_clearStore();

private:
    /**
     * @brief The ring buffer that stores the pretty messages
     * 
     * A ring buffer is chosen to limit the number of displayed pretty messages
     * and to allow for easy shifting pretty messages in and out
     */
    RSimpleDestructiveRingBuff<PrettyTimestampedMsg<TimestampedMsg>> msgStorage;
};

#endif /* MSGSTREAMSTORE_H */
