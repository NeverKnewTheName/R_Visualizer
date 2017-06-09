#include "SendMsgPackageSendingWorker.h"

#include <QThread>
#include <QMutexLocker>

SendMsgPackageSendingWorker::SendMsgPackageSendingWorker(
        QMutex &sendingMutex,
        const int sendingDelay
        ) :
    QObject(Q_NULLPTR),
    sendingMutex(sendingMutex),
    sendingDelay(sendingDelay),
    sendingActive(false)
 {
 }

SendMsgPackageSendingWorker::~SendMsgPackageSendingWorker()
{
}

void SendMsgPackageSendingWorker::sendMessages()
{
    for(const IMsg &msg : messagesToSend)
    {
        QThread::msleep(sendingDelay);
        emit sgnl_SendMessage(msg);
        QMutexLocker mutexLock(&sendingMutex);
        if(!sendingActive)
        {
            break;
        }
    }
}

void SendMsgPackageSendingWorker::slt_SetMessages(const QVector<Msg> &messages)
{
    QMutexLocker mutexLock(&sendingMutex);
    messagesToSend = messages;
}

void SendMsgPackageSendingWorker::slt_SetSendingDelay(const int sendingDelay)
{
    QMutexLocker mutexLock(&sendingMutex);
    this->sendingDelay = sendingDelay;
}

void SendMsgPackageSendingWorker::slt_StartSending()
{
    {
        QMutexLocker mutexLock(&sendingMutex);
        sendingActive = true;
    }
    sendMessages();
}

void SendMsgPackageSendingWorker::slt_AbortSending()
{
    QMutexLocker mutexLock(&sendingMutex);
    sendingActive = false;
}
