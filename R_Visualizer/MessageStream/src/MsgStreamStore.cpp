#include "MsgStreamStore.h"

MsgStreamStore::MsgStreamStore(const int bufferSize, QObject *parent) :
    QObject(parent),
    bufferSize(bufferSize),
    msgStorage(bufferSize)
{
}

MsgStreamStore::~MsgStreamStore()
{
}

IPrettyTimestampedMsg &MsgStreamStore::appendMsg(
        const IPrettyTimestampedMsg &msgToAppend
        )
{
    bool bufferOverflowing = msgStorage.size() >= bufferSize;

    if(bufferOverflowing)
    {
        emit sgnl_storeAboutToOverflow();
    }
    else
    {
        emit sgnl_msgAboutToBeAppended();
    }

    msgStorage.append(msgToAppend);

    if(bufferOverflowing)
    {
        emit sgnl_storeOverflow();
    }
    else
    {
        emit sgnl_msgAppended();
    }

    return msgStorage.last();
}

IPrettyTimestampedMsg &MsgStreamStore::appendMsg(
        const ITimestampedMsg &msgToAppend
        )
{
    return appendMsg(PrettyTimestampedMsg<TimestampedMsg>(msgToAppend));
}

IPrettyTimestampedMsg &MsgStreamStore::prependMsg(
        const IPrettyTimestampedMsg &msgToPrepend
        )
{
    bool bufferOverflowing = msgStorage.size() >= bufferSize;

    if(bufferOverflowing)
    {
        emit sgnl_storeAboutToUnderflow();
    }
    else
    {
        emit sgnl_msgAboutToBePrepended();
    }

    msgStorage.prepend(msgToPrepend);

    if(bufferOverflowing)
    {
        emit sgnl_storeUnderflow();
    }
    else
    {
        emit sgnl_msgPrepended();
    }
    return msgStorage.first();
}

IPrettyTimestampedMsg &MsgStreamStore::prependMsg(
        const ITimestampedMsg &msgToPrepend
        )
{
    return prependMsg(PrettyTimestampedMsg<TimestampedMsg>(msgToPrepend));
}


IPretty &MsgStreamStore::at(const int index) const
{
    return msgStorage.at(index);
}

IPretty &MsgStreamStore::at(const int index)
{
    return msgStorage.at(index);
}

int size() const
{
    return msgStorage.size();
}

void MsgStreamStore::clear()
{
    emit sgnl_storeAboutToBeCleared();
    msgStorage.clear();
    emit sgnl_storeCleared();
}

void MsgStreamStore::slt_appendMsg(const IPrettyTimestampedMsg &msgToAppend)
{
    appendMsg(msgToAppend);
}

void MsgStreamStore::slt_prependMsg(const IPrettyTimestampedMsg &msgToPrepend)
{
    prependMsg(msgToPrepend);
}

void MsgStreamStore::slt_clearStore()
{
    clear();
}

