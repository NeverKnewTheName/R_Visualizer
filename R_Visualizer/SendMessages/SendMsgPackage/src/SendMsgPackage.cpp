#include "SendMsgPackage.h"

#include <QTimer>

SendMsgPackage::SendMsgPackage(
        ISendMsgPackageStore *sendMsgPackageStore,
        QObject *parent
        ) :
    ISendMsgPackage(parent),
    sendMsgPackageStore(sendMsgPackageStore),
    sendMsgsWorkerThread(new QThread()),
    sendDelay(5),
    senderWorker(
            new SendMsgPackageSendingWorker(
                sendMsgWorkerMutex,
                sendDelay
                )
            )
{
    senderWorker->moveToThread(sendMsgsWorkerThread);
    connect(
            this,
            &SendMsgPackage::sgnl_setMsgPackage,
            senderWorker,
            &SendMsgPackageSendingWorker::slt_SetMessages,
            Qt::QueuedConnection
           );
    connect(
            this,
            &SendMsgPackage::sgnl_setSendingDelay,
            senderWorker,
            &SendMsgPackageSendingWorker::slt_SetSendingDelay,
            Qt::QueuedConnection
           );
    connect(
            this,
            &SendMsgPackage::sgnl_StartSending,
            senderWorker,
            &SendMsgPackageSendingWorker::slt_StartSending,
            Qt::QueuedConnection
           );
    connect(
            this,
            &SendMsgPackage::sgnl_AbortSending,
            senderWorker,
            &SendMsgPackageSendingWorker::slt_AbortSending,
            Qt::DirectConnection
           );

    connect(
            senderWorker,
            &SendMsgPackageSendingWorker::sgnl_SendMessage,
            this,
            &SendMsgPackage::sgnl_SendStdMsg,
            Qt::DirectConnection
           );
    connect(
            senderWorker,
            &SendMsgPackageSendingWorker::sgnl_SendingStarted,
            this,
            &ISendMsgPackage::sgnl_SendingStarted
           );
    connect(
            senderWorker,
            &SendMsgPackageSendingWorker::sgnl_SendingFinished,
            this,
            &ISendMsgPackage::sgnl_SendingFinished
           );

    sendMsgsWorkerThread->start();

}

SendMsgPackage::~SendMsgPackage()
{
    emit sgnl_AbortSending();
    sendMsgsWorkerThread->quit();
    sendMsgsWorkerThread->wait();
    delete senderWorker;
}

void SendMsgPackage::appendMsg(const IMsg &msgToAppend)
{
    IMsg &msg = sendMsgPackageStore->appendMsg(msgToAppend);
}

void SendMsgPackage::prependMsg(const IMsg &msgToPrepend)
{
    IMsg &msg = sendMsgPackageStore->prependMsg(
                msgToPrepend
                );
}

void SendMsgPackage::insertMsg(
        const int index,
        const IMsg &msgToAppend
        )
{
    IMsg &msg = sendMsgPackageStore->insertMsg(
            index, msgToAppend
                );
}

void SendMsgPackage::removeAt(const int index)
{
    sendMsgPackageStore->removeAt(index);
}

void SendMsgPackage::removeMsgs(const int index, int count)
{
    sendMsgPackageStore->removeMsgs(index,count);
}

ISendMsgPackageStore *SendMsgPackage::getStore() const
{
    return sendMsgPackageStore;
}

void SendMsgPackage::sendMessages()
{
    emit sgnl_setMsgPackage(
            sendMsgPackageStore->getMessagesAsVector()
            );
    emit sgnl_StartSending();

    /* for(int i = 0; i < size; ++i) */
    /* { */
    /*     const IMsg &msg = sendMsgPackageStore->at(i); */
    /*     QTimer::singleShot( */
    /*             sendDelay, */
    /*             [&](){ */
    /*                 emit sgnl_sendMsg(msg); */
    /*             } */
    /*             ); */

    /* } */

}

int SendMsgPackage::getSendDelay() const
{
    return sendDelay;
}

void SendMsgPackage::setSendDelay(const int sendDelay)
{
    this->sendDelay = sendDelay;
    emit sgnl_setSendingDelay(sendDelay);
}
