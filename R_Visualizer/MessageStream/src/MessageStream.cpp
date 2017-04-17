#include "MessageStream.h"

#include "MessageStreamNotifier.h"

#include "IMessageConfig.h"
#include "IMessageFilter.h"
#include "IPrettyMsg.h"
#include "PrettyTimestampedMsg.h"

MessageStream::MessageStream(
        IMessageConfig *msgConfig,
        IMessageFilter *msgFilter,
        IMsgStreamStore *msgStreamStore,
        TimestampedMsgStorage &msgStorage,
        QObject *parent
        ) :
    QObject(parent),
    msgStreamNotifier(new MessageStreamNotifier(this, this)),
    msgConfig(msgConfig),
    msgFilter(msgFilter),
    msgStreamStore(msgStreamStore),
    msgStorage(msgStorage)
{
    if(msgConfig == Q_NULLPTR)
    {
        //ERROR
        //THROW EXCEPTION
    }

    if(msgFilter == Q_NULLPTR)
    {
        //ERROR
        //THROW EXCEPTION
    }

    if(msgStreamStore == Q_NULLPTR)
    {
        //ERROR
        //THROW EXCEPTION
    }
}

MessageStream::~MessageStream()
{
}

bool MessageStream::appendMsg(const ITimestampedMsg &msgToAppend)
{
    if(msgFilter->filterMessage(msgToAppend))
    {
        IPrettyMsg &prettifiedMsg = msgStreamStore->appendMsg(msgToAppend);

        msgConfig->prettifyMsg(prettifiedMsg);

        return true;
    }
    else
    {
        return false;
    }
}

bool MessageStream::prependMsg(const ITimestampedMsg &msgToAppend)
{
    if(msgFilter->filterMessage(msgToAppend))
    {
        IPrettyMsg &prettifiedMsg = msgStreamStore->prependMsg(msgToAppend);

        msgConfig->prettifyMsg(prettifiedMsg);

        return true;
    }
    else
    {
        return false;
    }
}

void MessageStream::clear()
{
    msgStreamStore->clear();
}

MessageStreamNotifier *MessageStream::getNotifier()
{
    return msgStreamNotifier;
}

void MessageStream::connectMsgConfig()
{
    //ToDO
}

void MessageStream::connectMsgFilter()
{
    //ToDO
}

void MessageStream::connectMsgStorage()
{
    //ToDO
}

void MessageStream::connectMsgStreamStore()
{
    /* /** */
    /*  * Connects the store signal for message appended to this object's signal */
    /*  * for message added to propagate the signal from the store */
    /*  *1/ */
    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_msgAppended, */
    /*         this, */
    /*         &IMessageStream::sgnl_messageAdded */
    /*        ); */

    /* /** */
    /*  * Connects the store signal for message prepended to this object's signal */
    /*  * for message added to propagate the signal from the store */
    /*  *1/ */
    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_msgPrepended, */
    /*         this, */
    /*         &IMessageStream::sgnl_messageAdded */
    /*        ); */

    /* /** */
    /*  * Connects the store signal for store cleared to this object's signal */
    /*  * for stream cleared to propagate the signal from the store */
    /*  *1/ */
    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_storeCleared, */
    /*         this, */
    /*         &IMessageStream::sgnl_streamCleared */
    /*        ); */
}

