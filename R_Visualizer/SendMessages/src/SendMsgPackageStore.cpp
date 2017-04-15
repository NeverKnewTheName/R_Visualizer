#include "SendMsgPackageStore.h"

SendMsgPackageStore::SendMsgPackageStore()
{
}

SendMsgPackageStore::~SendMsgPackageStore()
{
}

IPrettyMsg &SendMsgPackageStore::appendMsg(const IPrettyMsg &msgToAppend)
{
    emit sgnl_msgAboutToBeAppended();

    msgStorage.append(msgToAppend);

    emit sgnl_msgAppended();

    return msgStorage.last();
}

IPrettyMsg &SendMsgPackageStore::appendMsg(const IMsg &msgToAppend)
{
    return appendMsg(PrettyMsg<Msg>(msgToAppend));
}

IPrettyMsg &SendMsgPackageStore::prependMsg(const IPrettyMsg &msgToPrepend)
{
    emit sgnl_msgAboutToBePrepended();

    msgStorage.prepend(msgToPrepend);

    emit sgnl_msgPrepended();

    return msgStorage.first();
}

IPrettyMsg &SendMsgPackageStore::prependMsg(const IMsg &msgToPrepend)
{
    return prependMsg(PrettyMsg<Msg>(msgToPrepend));
}

IPrettyMsg &SendMsgPackageStore::insertMsg(
        const int index,
        const IPrettyMsg &msgToInsert
        )
{
    if(index >= msgStorage.size())
    {
        return appendMsg(msgToInsert);
    }
    else
    {
        emit sgnl_msgAboutToBeInserted(index);

        msgStorage.insert(index, msgToInsert);

        emit sgnl_msgInserted();

        return msgStorage[index];
    }
}

IPrettyMsg &SendMsgPackageStore::insertMsg(
        const int index,
        const IMsg &msgToInsert
        )
{
    return insertMsg(index, PrettyMsg<Msg>(msgToInsert));
}

void SendMsgPackageStore::removeMsgFirstMatch(const IPrettyMsg &msgToRemove)
{
}

void SendMsgPackageStore::removeMsgLastMatch(const IPrettyMsg &msgToRemove)
{
}

void SendMsgPackageStore::removeMsgsAllMatches(const IPrettyMsg &msgToRemove)
{
}

SendMsgPackageStore::

SendMsgPackageStore::
