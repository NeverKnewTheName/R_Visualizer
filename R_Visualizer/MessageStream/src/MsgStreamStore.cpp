#include "MsgStreamStore.h"

MsgStreamStore::MsgStreamStore(const int bufferSize, QObject *parent) :
    QObject(parent),
    msgStorage(bufferSize)
{
}

MsgStreamStore::~MsgStreamStore()
{
}

bool MsgStreamStore::appendMsg(const IPrettyTimestampedMsg &msgToAppend)
{
    msgStorage.append(msgToAppend);
    return true;
}

bool MsgStreamStore::prependMsg(const IPrettyTimestampedMsg &msgToPrepend)
{
    msgStorage.prepend(msgToPrepend);
    return true;
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
    msgStorage.clear();
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

