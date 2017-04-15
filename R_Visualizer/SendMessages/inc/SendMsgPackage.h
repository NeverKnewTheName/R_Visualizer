/**
 * @file SendMsgPackage.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation of #ISendMsgPackage
 */
#ifndef SENDMSGPACKAGE_H
#define SENDMSGPACKAGE_H

#include <QObject>

#include "ISendMsgPackage.h"
#include "ISendMsgPackageStore.h"
#include "IMessageConfig.h"
#include "Msg.h"

/**
 * @brief The SendMsgPackage
 */
class SendMsgPackage : public QObject, public ISendMsgPackage
{
    Q_OBJECT
public:
    SendMsgPackage(
            ISendMsgPackageStore *sendMsgPackageStore,
            IMessageConfig *msgConfig,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackage();

    void appendMsg(const IMsg &msgToAppend);
    void removeMsgFirstMatch(const IMsg &msgToRemove);
    void removeMsgLastMatch(const IMsg &msgToRemove);
    void removeMsgsAllmatches(const IMsg &msgToRemove);

signals:
    void sgnl_sendMsg(const IMsg &msgToSend);
    void sgnl_msgAppended();
    void sgnl_msgRemoved();

public slots:
    void slt_appendMsg(const IMsg &msgToAppend);
    void slt_removeMsgFirstMatch(const IMsg &msgToRemove);
    void slt_removeMsgLastMatch(const IMsg &msgToRemove);
    void slt_removeMsgsAllMatches(const IMsg &msgToRemove);

private:
    ISendMsgPackageStore *sendMsgPackageStore;
    IMessageConfig *msgConfig;

};

#endif /* SENDMSGPACKAGE_H */
