/**
 * @file ISendMsgPackage.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for sending message packages
 */
#ifndef ISENDMSGPACKAGE_H
#define ISENDMSGPACKAGE_H

class IMsg;

/**
 * @brief The ISendMsgPackage interface
 */
class ISendMsgPackage
{
public:
    virtual ~ISendMsgPackage();

    virtual void appendMsg(const IMsg &msgToAppend) = 0;
    virtual void prependMsg(const IMsg &msgToAppend) = 0;
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual void insertMsg(const int index, const IMsg &msgToAppend) = 0;

    virtual void removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgsAllMatches(const IMsg &msgToRemove) = 0;

    virtual void sendMessages() = 0;

signals:
    virtual void sgnl_sendMsg(const IMsg &msgToSend) = 0;
    virtual void sgnl_msgAppended() = 0;
    virtual void sgnl_msgPrepended() = 0;
    virtual void sgnl_msgRemoved() = 0;

public slots:
    virtual void slt_appendMsg(const IMsg &msgToAppend) = 0;
    virtual void slt_prependMsg(const IMsg &msgToPrepend) = 0;
    virtual void slt_insertMsg(const int index, const IMsg &msgToInsert) = 0;
    virtual void slt_removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    virtual void slt_removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    virtual void slt_removeMsgsAllMatches(const IMsg &msgToRemove) = 0;

};

#endif /* ISENDMSGPACKAGE_H */
