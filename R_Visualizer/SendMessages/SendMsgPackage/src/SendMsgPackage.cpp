#include "SendMsgPackage.h"

#include <QTimer>

SendMsgPackage::SendMsgPackage(
        ISendMsgPackageStore *sendMsgPackageStore,
        QObject *parent
        ) :
    ISendMsgPackage(parent),
    sendMsgPackageStore(sendMsgPackageStore),
    sendDelay(5)
{
}

SendMsgPackage::~SendMsgPackage()
{
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
    const int size = sendMsgPackageStore->size();

    for(int i = 0; i < size; ++i)
    {
        const IMsg &msg = sendMsgPackageStore->at(i);
        QTimer::singleShot(
                sendDelay,
                [&](){
                    emit sgnl_sendMsg(msg);
                }
                );

    }

}

int SendMsgPackage::getSendDelay() const
{
    return sendDelay;
}

void SendMsgPackage::setSendDelay(const int sendDelay)
{
    this->sendDelay = sendDelay;
}
