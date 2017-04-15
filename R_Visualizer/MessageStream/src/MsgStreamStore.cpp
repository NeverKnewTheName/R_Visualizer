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
    }
    else
    {
        emit sgnl_msgAboutToBeAppended();
    }

    msgStorage.append(msgToAppend);

    if(bufferOverflowing)
    {
    }
    else
    {
        emit sgnl_msgAppended();
    }

    return msgStorage.last();
}

IPrettyTimestampedMsg &MsgStreamStore::prependMsg(
        const IPrettyTimestampedMsg &msgToPrepend
        )
{
    emit sgnl_msgAboutToBePrepended();

    msgStorage.prepend(msgToPrepend);

    emit sgnl_msgPrepended();
    return msgStorage.first();
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

