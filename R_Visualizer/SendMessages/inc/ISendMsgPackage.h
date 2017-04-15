/**
 * @file ISendMsgPackage.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for sending message packages
 */
#ifndef ISENDMSGPACKAGE_H
#define ISENDMSGPACKAGE_H

#include "IMsg.h"

/**
 * @brief The ISendMsgPackage interface
 */
class ISendMsgPackage
{
public:
    virtual ~ISendMsgPackage();

    virtual void appendMsg(const IMsg &msgToAppend) = 0;

    virtual void removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    virtual void removeMsgsAllmatches(const IMsg &msgToRemove) = 0;

signals:
    void sgnl_sendMsg(const IMsg &msgToSend) = 0;
    void sgnl_msgAppended() = 0;
    void sgnl_msgRemoved() = 0;

public slots:
    void slt_appendMsg(const IMsg &msgToAppend) = 0;
    void slt_removeMsgFirstMatch(const IMsg &msgToRemove) = 0;
    void slt_removeMsgLastMatch(const IMsg &msgToRemove) = 0;
    void slt_removeMsgsAllMatches(const IMsg &msgToRemove) = 0;

};

#endif /* ISENDMSGPACKAGE_H */
