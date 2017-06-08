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
#include <QThread>

#include "ISendMsgPackage.h"
#include "ISendMsgPackageStore.h"
#include "IMessageConfig.h"
#include "Msg.h"

#include "SendMsgPackageSendingWorker.h"

/**
 * @brief The SendMsgPackage
 */
class SendMsgPackage : public ISendMsgPackage
{
    Q_OBJECT
public:
    SendMsgPackage(
            ISendMsgPackageStore *sendMsgPackageStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackage();

    virtual void appendMsg(const IMsg &msgToAppend);
    virtual void prependMsg(const IMsg &msgToAppend);
    virtual void insertMsg(const int index, const IMsg &msgToAppend);
    virtual void removeAt(const int index);
    virtual void removeMsgs(const int index, int count);

    virtual ISendMsgPackageStore *getStore() const;

    virtual void sendMessages();

    virtual int getSendDelay() const;
    virtual void setSendDelay(const int sendDelay);

signals:
    void sgnl_setMsgPackage(const QVector<Msg> &messages);
    void sgnl_setSendingDelay(const int sendingDelay);
    void sgnl_StartSending();
    void sgnl_AbortSending();

private:
    ISendMsgPackageStore *sendMsgPackageStore;
    QThread *sendMsgsWorkerThread;
    QMutex sendMsgWorkerMutex;
    int sendDelay;
    SendMsgPackageSendingWorker *senderWorker;
};

#endif /* SENDMSGPACKAGE_H */
