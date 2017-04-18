#include "SendMsgPackageStoreNotifier.h"

#include "ISendMsgPackageStore.h"

SendMsgPackageStoreNotifier::SendMsgPackageStoreNotifier(
        ISendMsgPackageStore *msgPackageStore,
        QObject *parent
        ) :
    QObject(parent),
    msgPackageStore(msgPackageStore)
{
}

SendMsgPackageStoreNotifier::~SendMsgPackageStoreNotifier()
{
}

void SendMsgPackageStoreNotifier::emitSgnlMsgAboutToBeAppended()
{
    emit sgnl_MsgAboutToBeAppended();
}

void SendMsgPackageStoreNotifier::emitSgnlMsgAppended()
{
    emit sgnl_MsgAppended();
}


void SendMsgPackageStoreNotifier::emitSgnlMsgAboutToBePrepended()
{
    emit sgnl_MsgAboutToBePrepended();
}

void SendMsgPackageStoreNotifier::emitSgnlMsgPrepended()
{
    emit sgnl_MsgPrepended();
}


void SendMsgPackageStoreNotifier::emitSgnlMsgAboutToBeInserted(
        const int index
        )
{
    emit sgnl_MsgAboutToBeInserted(index);
}

void SendMsgPackageStoreNotifier::emitSgnlMsgInserted()
{
    emit sgnl_MsgInserted();
}


void SendMsgPackageStoreNotifier::emitSgnlMsgAboutToBeRemoved(
        const int index
        )
{
    emit sgnl_MsgAboutToBeRemoved(index);
}

void SendMsgPackageStoreNotifier::emitSgnlMsgRemoved()
{
    emit sgnl_MsgRemoved();
}

void SendMsgPackageStoreNotifier::slt_appendMsg(const IMsg &msgToAdd)
{
    //ToDO
}

void SendMsgPackageStoreNotifier::slt_prependMsg(const IMsg &msgToAdd)
{
}

void SendMsgPackageStoreNotifier::slt_insertMsg(
        const int index,
        const IMsg &msgToAdd
        )
{
}

void SendMsgPackageStoreNotifier::slt_removeMsg(const int index)
{
}
