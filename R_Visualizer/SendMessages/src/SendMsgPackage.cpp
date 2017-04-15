#include "SendMsgPackage.h"

SendMsgPackage::SendMsgPackage(
        ISendMsgPackageStore *sendMsgPackageStore,
        IMessageConfig *msgConfig,
        QObject *parent) :
    QObject(parent),
    sendMsgPackageStore(sendMsgPackageStore),
    msgConfig(msgConfig)
{
}

SendMsgPackage::~SendMsgPackage()
{
}

void SendMsgPackage::appendMsg(const IMsg &msgToAppend)
{
    IPrettyMsg &prettifiedMsg = sendMsgPackageStore->appendMsg();
    msgConfig->prettifyMsg(prettifiedMsg);
}

void SendMsgPackage::removeMsgFirstMatch(const IMsg &msgToRemove)
{
}

void SendMsgPackage::removeMsgLastMatch(const IMsg &msgToRemove)
{
}

void SendMsgPackage::removeMsgsAllmatches(const IMsg &msgToRemove)
{
}

void SendMsgPackage::slt_appendMsg(const IMsg &msgToAppend)
{
    appendMsg(msgToAppend);
}

void SendMsgPackage::slt_removeMsgFirstMatch(const IMsg &msgToRemove)
{

}

void SendMsgPackage::slt_removeMsgLastMatch(const IMsg &msgToRemove)
{

}

void SendMsgPackage::slt_removeMsgAllMatches(const IMsg &msgToRemove)
{

}
