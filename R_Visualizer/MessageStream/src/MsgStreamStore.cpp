#include "MsgStreamStore.h"

#include <QDebug>

MsgStreamStore::MsgStreamStore(const int bufferSize, QObject *parent) :
    IMsgStreamStore(parent),
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
    /* qDebug() << static_cast<QString>(msgToAppend); */

    const bool bufferOverflowing = msgStorage.size() >= bufferSize;

    if(bufferOverflowing)
    {
        emit sgnl_storeAboutToOverflow();
    }
    else
    {
        emit sgnl_msgAboutToBeAppended();
    }

    /*
     * ToDO Dynamic cast on references throws exception if gone wrong! include
     * exception handling!
     */
    msgStorage.append(
            dynamic_cast<const PrettyTimestampedMsg<TimestampedMsg>&>(
                msgToAppend
                )
            );

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
    /*
     * ToDO Dynamic cast on references throws exception if gone wrong! include
     * exception handling!
     */
    return appendMsg(
            PrettyTimestampedMsg<TimestampedMsg>(
                dynamic_cast<const TimestampedMsg&>(msgToAppend)
                )
            );
}

IPrettyTimestampedMsg &MsgStreamStore::prependMsg(
        const IPrettyTimestampedMsg &msgToPrepend
        )
{
    const bool bufferOverflowing = msgStorage.size() >= bufferSize;

    if(bufferOverflowing)
    {
        emit sgnl_storeAboutToUnderflow();
    }
    else
    {
        emit sgnl_msgAboutToBePrepended();
    }

    /*
     * ToDO Dynamic cast on references throws exception if gone wrong! include
     * exception handling!
     */
    msgStorage.prepend(
            dynamic_cast<const PrettyTimestampedMsg<TimestampedMsg>&>(
                msgToPrepend)
            );

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
    /*
     * ToDO Dynamic cast on references throws exception if gone wrong! include
     * exception handling!
     */
    return prependMsg(
            PrettyTimestampedMsg<TimestampedMsg>(
                dynamic_cast<const TimestampedMsg&>(msgToPrepend)
                )
            );
}


const IPrettyTimestampedMsg &MsgStreamStore::at(const int index) const
{
    return msgStorage.at(index);
}

IPrettyTimestampedMsg &MsgStreamStore::at(const int index)
{
    return msgStorage.at(index);
}

int MsgStreamStore::size() const
{
    return msgStorage.size();
}

void MsgStreamStore::clear()
{
    emit sgnl_storeAboutToBeCleared();
    msgStorage.clear();
    emit sgnl_storeCleared();
}

int MsgStreamStore::getBufferSize() const
{
    return bufferSize;
}
