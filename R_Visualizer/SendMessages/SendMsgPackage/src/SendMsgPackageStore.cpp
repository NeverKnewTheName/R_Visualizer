#include "SendMsgPackageStore.h"

SendMsgPackageStore::SendMsgPackageStore(
        QObject *parent
        ) :
    ISendMsgPackageStore(parent)
{
}

SendMsgPackageStore::~SendMsgPackageStore()
{
}

IMsg &SendMsgPackageStore::appendMsg(const IMsg &msgToAppend)
{
    Msg msg(msgToAppend.getMsgID(), msgToAppend.getMsgCode(), msgToAppend.getMsgData());

    emit sgnl_msgAboutToBeInserted(0,msg);

    msgStorage.append(msg);

    emit sgnl_msgInserted(0,msg);

    return msgStorage.last();
}

IMsg &SendMsgPackageStore::prependMsg(const IMsg &msgToPrepend)
{
    Msg msg(msgToPrepend.getMsgID(), msgToPrepend.getMsgCode(), msgToPrepend.getMsgData());
    const int curEnd = msgStorage.size();

    emit sgnl_msgAboutToBeInserted(curEnd,msg);

    msgStorage.prepend(msg);

    emit sgnl_msgInserted(curEnd,msg);

    return msgStorage.first();
}

IMsg &SendMsgPackageStore::insertMsg(
        const int index,
        const IMsg &msgToInsert
        )
{
    if(index >= msgStorage.size())
    {
        return appendMsg(msgToInsert);
    }
    else
    {
        Msg msg(msgToInsert.getMsgID(), msgToInsert.getMsgCode(), msgToInsert.getMsgData());
        emit sgnl_msgAboutToBeInserted(index,msg);

        msgStorage.insert(index, msg);

        emit sgnl_msgInserted(index,msg);

        return msgStorage[index];
    }
}

int SendMsgPackageStore::size() const
{
    return msgStorage.size();
}

const IMsg &SendMsgPackageStore::at(const int index) const
{
    return msgStorage.at(index);
}

IMsg &SendMsgPackageStore::at(const int index)
{
    return msgStorage[index];
}

void SendMsgPackageStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgStorage.clear();
    emit sgnl_Cleared();
}

QVector<Msg> SendMsgPackageStore::getMessagesAsVector() const
{
    return msgStorage;
}

void SendMsgPackageStore::accept(FileParser *visitor)
{
    visitor->visit(this);
}

void SendMsgPackageStore::removeAt(const int index)
{
    emit sgnl_msgAboutToBeRemoved(index,1);
    msgStorage.remove(index);
    emit sgnl_msgRemoved(index,1);
}

void SendMsgPackageStore::removeMsgs(const int index, int count)
{
    if(index+count > msgStorage.size())
    {
        return;
    }

    emit sgnl_msgAboutToBeRemoved(index,count);

    msgStorage.remove(index,count);

    emit sgnl_msgRemoved(index,count);
}
