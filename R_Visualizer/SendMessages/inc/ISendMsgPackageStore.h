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

    /**
     * @brief Appends the given message to the store
     * 
     * The msgToAppend can be left empty to construct a default #IPrettyMsg
     * derivate. A mofiable reference is returned to the caller. This is done
     * to not inflict the low level details about which #IPrettyMsg
     * implementation has been implemented in this store. The caller can work
     * with the returned #IPrettyMsg reference without being concerned about
     * these details.
     */
    virtual IPrettyMsg &appendMsg(const IPrettyMsg &msgToAppend) = 0;

    virtual IPrettyMsg &prependMsg(const IMsg &msgToAppend) = 0;
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual IPrettyMsg &insertMsg(const int index, const IMsg &msgToAppend) = 0;

    virtual void removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgsAllmatches(const IMsg &msgToRemove) = 0;

signals:
    void sgnl_msgAboutToBeAppended() = 0;
    void sgnl_msgAppended() = 0;

    void sgnl_msgAboutToBePrepended() = 0;
    void sgnl_msgPrepended() = 0;

    void sgnl_msgAboutToBeRemoved() = 0;
    void sgnl_msgRemoved() = 0;

public slots:
    void slt_appendMsg(const IMsg &msgToAppend) = 0;
    void slt_prependMsg(const IMsg &msgToPrepend) = 0;
    void slt_insertMsg(const int index, const IMsg &msgToInsert) = 0;
    void slt_removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    void slt_removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    void slt_removeMsgsAllMatches(const IMsg &msgToRemove) = 0;

};

#endif /* ISENDMSGPACKAGESTORE_H */
