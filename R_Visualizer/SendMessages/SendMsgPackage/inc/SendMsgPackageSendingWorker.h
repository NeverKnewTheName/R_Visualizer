/**
 * @file SendMsgPackageSendingWorker.h
 * @author Christian Neuberger
 * @date 2017-05-29
 * 
 * @brief Worker thread helper for sending messages
 */
#ifndef SENDMSGPACKAGESENDINGWORKER_H
#define SENDMSGPACKAGESENDINGWORKER_H

#include <QObject>
#include <QMutex>
#include <QVector>

#include "Msg.h"

class SendMsgPackageSendingWorker : public QObject
{
    Q_OBJECT
public:
    SendMsgPackageSendingWorker(
            QMutex &sendingMutex,
            const int sendingDelay
            );
    virtual ~SendMsgPackageSendingWorker();

signals:
    void sgnl_SendMessage(const IMsg &msg);

public slots:
    void slt_SetMessages(const QVector<Msg> &messages);
    void slt_SetSendingDelay(const int sendingDelay);
    void slt_StartSending();
    void slt_AbortSending();

private:
    void sendMessages();

private:
    QMutex &sendingMutex;
    QVector<Msg> messagesToSend;
    int sendingDelay;
    bool sendingActive;

};

#endif /* SENDMSGPACKAGESENDINGWORKER_H */
