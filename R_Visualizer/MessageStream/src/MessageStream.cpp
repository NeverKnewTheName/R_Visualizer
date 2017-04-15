#include "MessageStream.h"

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

void MessageStream::slt_appendMessage(const ITimestampedMsg &msgToAppend)
{
    appendMsg(msgToAppend);
}

void MessageStream::slt_prependMessage(const ITimestampedMsg &msgToPrepend)
{
    prependMsg(msgToPrepend);
}

void MessageStream::slt_clearStream()
{
    clear();
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

