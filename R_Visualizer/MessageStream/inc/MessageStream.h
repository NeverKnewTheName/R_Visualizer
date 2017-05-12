/**
 * @file MessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The MessageStream module
 */
#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QObject>

#include "IMessageStream.h"
#include "IMsgStreamStore.h"

#include "rsimpleringbuff.h"

class TimestampedMsgStorage;
class IMessageConfig;
class IMessageFilter;

class IMsgMappingManager;

class IMsgFilter;
class ITimestampedMsgFilter;

/**
 * @addtogroup MessageStreamGroup
 *
 * @{
 */

/**
 * @brief The MessageStream
 */
class MessageStream : public IMessageStream
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the #MessageStream
     * 
     * @param [in] msgStreamStore   The #IMsgStreamStore that holds the
     * messages for the #MessageStream
     * @param [in] msgConfig        The #IMessageConfig that is used to
     * customize incoming messages
     * @param [in] msgFilter        The #IMessageFilter that is used to filter
     * incoming messages
     * @param [in] msgStorage       The #TimestampedMsgStorage that contains
     * the messages to be displayed in the #MessageStream
     * @param [in] parent           The QObject that is the parent to this
     * #MessageStream
     */
    explicit MessageStream(
            IMessageConfig *msgConfig,
            IMessageFilter *msgFilter,
            IMsgStreamStore *msgStreamStore,
            TimestampedMsgStorage &msgStorage,
            QObject *parent = Q_NULLPTR
            );

    virtual ~MessageStream();

    /**
     * @brief Appends the specified message to the stream
     */
    virtual bool appendMsg(
            const ITimestampedMsg &msgToAppend,
            const int indexInStore
            );

    /**
     * @brief Prepends the specified messages to the stream
     */
    virtual bool prependMsg(
            const ITimestampedMsg &msgToPrepend,
            const int indexInStore
            );

    /**
     * @brief Clears the stream
     */
    virtual void clear();

    virtual void setCurrentStartIndex(const int newStartIndex);
    virtual int getCurrentStartIndex() const;
    virtual void setCurrentEndIndex(const int newEndIndex);
    virtual int getCurrentEndIndex() const;

    /**
     * @brief Updates the stream by the mappingToUpdate #IMsgDataMappingManager
     */
    virtual void updateMsgMapping(
            const IMsgMappingManager &mappingToUpdate
            );

    /**
     * @brief Updates the stream by the filterToUpdate #IMsgFilter
     */
    virtual void updateMsgFilter(
            const IMsgFilter &filterToUpdate
            );

    /**
     * @brief Updates the stream by the filterToUpdate #ITimestampedMsgFilter
     */
    virtual void updateTimestampFilter(
            const ITimestampedMsgFilter &filterToUpdate
            );

private:
    void connectMsgConfig();
    void connectMsgFilter();
    void connectMsgStorage();
    void connectMsgStreamStore();

    virtual bool appendHelper(
            const ITimestampedMsg &msgToAppend,
            const int indexInStore
            );
    virtual bool prependHelper(
            const ITimestampedMsg &msgToPrepend,
            const int indexInStore
            );

private:
    IMessageConfig *msgConfig;
    IMessageFilter *msgFilter;
    IMsgStreamStore *msgStreamStore;
    /**
     * @brief Reference to the #TimestampedMsgStorage that receives all
     * incoming messages to be displayed in the #MessageStream
     */
    TimestampedMsgStorage &msgStorage;
    RSimpleDestructiveRingBuff<int> indexStore;
    bool continuousFlag;

    // IFileParsable interface
public:
    virtual void accept(FileParser *visitor);

    // IMessageStream interface
public:
    virtual bool fetchPrevious();
    virtual bool fetchNext();
    virtual bool fetchTop();
    virtual bool fetchBottom();
    bool getContinuousFlag() const;
    void setContinuousFlag(bool value);
};

/**
 * @}
 */

#endif // MESSAGESTREAM_H
