/**
 * @file IMessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-08
 * 
 * @brief The interface for the Message Stream Module
 */
#ifndef IMESSAGESTREAM_H
#define IMESSAGESTREAM_H

#include <QObject>

class ITimestampedMsg;

class IMsgMappingManager;

class IMsgFilter;
class ITimestampedMsgFilter;

class IPrettyTimestampedMsg;

/**
 * @brief The #IMessageStream interface
 */
class IMessageStream : public QObject
{
    Q_OBJECT
public:

    explicit IMessageStream(QObject *parent = Q_NULLPTR) : QObject(parent)
    {}

    virtual ~IMessageStream(){}

    /**
     * @brief Appends the specified message to the stream
     */
    virtual bool appendMsg(const ITimestampedMsg &msgToAppend) = 0;

    /**
     * @brief Prepends the specified messages to the stream
     */
    virtual bool prependMsg(const ITimestampedMsg &msgToPrepend) = 0;

    /**
     * @brief Clears the stream
     */
    virtual void clear() = 0;

    virtual void setCurrentEndIndex(const int newEndIndex) = 0;

    /**
     * @brief Updates the stream by the mappingToUpdate #IMsgDataMappingManager
     */
    virtual void updateMsgMapping(
            const IMsgMappingManager &mappingToUpdate
            ) = 0;

    /**
     * @brief Updates the stream by the filterToUpdate #IMsgFilter
     */
    virtual void updateMsgFilter(
            const IMsgFilter &filterToUpdate
            ) = 0;

    /**
     * @brief Updates the stream by the filterToUpdate #ITimestampedMsgFilter
     */
    virtual void updateTimestampFilter(
            const ITimestampedMsgFilter &filterToUpdate
            ) = 0;

signals:
    void sgnl_AppendMsg(const IPrettyTimestampedMsg &msgToAppend);

public slots:
    /**
     * @brief Slot that shall be called to receive messages to add to the
     * #IMessageStream
     * 
     * @param[in] receivedMsg Received #ITimestampedMsg to add to the stream
     *
     * @note This default implementation calls #appendMsg
     */
    virtual void slt_receiveMessage(
            const ITimestampedMsg &receivedMsg,
            const int index
            )
    {
        if(appendMsg(receivedMsg))
        {
            setCurrentEndIndex(index);
        }
    }

    /**
     * @brief Slot that updates the #IMessageStream by the given
     * #IMsgDataMappingManager
     * 
     * @note Calls #updateMsgMapping
     */
    virtual void slt_UpdateMsgMapping(
            const IMsgMappingManager &mappingToUpdate
            )
    {
        updateMsgMapping(mappingToUpdate);
    }

    /**
     * @brief Slot that updates the #IMessageStream by the given #IMsgFilter
     * 
     * @note Calls #updateMsgFilter
     */
    virtual void slt_UpdateMsgFilter(
            const IMsgFilter &filterToUpdate
            )
    {
        updateMsgFilter(filterToUpdate);
    }

    /**
     * @brief Slot that updates the #IMessageStream by the given
     * #ITimestampedMsgFilter
     * 
     * @note Calls #updateTimestampFilter
     */
    virtual void slt_UpdateTimestampFilter(
            const ITimestampedMsgFilter &filterToUpdate
            )
    {
        updateTimestampFilter(filterToUpdate);
    }
};

#endif /* IMESSAGESTREAM_H */
