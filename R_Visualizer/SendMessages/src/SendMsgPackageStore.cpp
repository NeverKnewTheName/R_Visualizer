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

IPrettyMsg &SendMsgPackageStore::prependMsg(const IPrettyMsg &msgToAppend)
{
    emit sgnl_msgAboutToBePrepended();

    msgStorage.prepend(msgToAppend);

    emit sgnl_msgPrepended();

    return msgStorage.first();
}

IPrettyMsg &SendMsgPackageStore::insertMsg(
        const int index,
        const IPrettymsg &msgToInsert
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
