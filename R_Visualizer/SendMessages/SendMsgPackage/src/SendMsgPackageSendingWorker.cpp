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
    emit sgnl_SendingStarted();
    for(const IMsg &msg : messagesToSend)
    {
        QThread::msleep(sendingDelay);
        Msg toSend(msg.getMsgID(), msg.getMsgCode(), msg.getMsgData());
        emit sgnl_SendMessage(toSend);
        QMutexLocker mutexLock(&sendingMutex);
        if(!sendingActive)
        {
            break;
        }
    }
    emit sgnl_SendingFinished();
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
