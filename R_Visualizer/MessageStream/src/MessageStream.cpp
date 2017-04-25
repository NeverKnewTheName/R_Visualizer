#include "MessageStream.h"

#include "MessageStreamNotifier.h"

#include "msgstorage.h"
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
    IMessageStream(parent),
    //msgStreamNotifier(new MessageStreamNotifier(this, this)),
    msgConfig(msgConfig),
    msgFilter(msgFilter),
    msgStreamStore(msgStreamStore),
    msgStorage(msgStorage),
    currentStartIndex(0),
    currentEndIndex(0)
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

    connectMsgConfig();
    connectMsgFilter();
    connectMsgStorage();
    connectMsgStreamStore();
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

void MessageStream::setCurrentEndIndex(const int newEndIndex)
{
    currentEndIndex = newEndIndex;
}

void MessageStream::updateMsgMapping(
        const IMsgMappingManager &mappingToUpdate
        )
{
    const int msgStreamStoreSize = msgStreamStore->size();
    for(int i = 0; i < msgStreamStoreSize; ++i)
    {
        msgConfig->prettifyMsgByMappingManager(
            msgStreamStore->at(i),
            mappingToUpdate
            );
    }
}

void MessageStream::updateMsgFilter(
        const IMsgFilter &filterToUpdate
        )
{
    //ToDO
}

void MessageStream::updateTimestampFilter(
        const ITimestampedMsgFilter &filterToUpdate
        )
{
    //ToDO
}

void MessageStream::connectMsgConfig()
{
    connect(
            msgConfig,
            &IMessageConfig::sgnl_MappingManagerChanged,
            this,
            &MessageStream::slt_UpdateMsgMapping
           );
}

void MessageStream::connectMsgFilter()
{
    connect(
            msgFilter,
            &IMessageFilter::sgnl_MsgFilterHasChanged,
            this,
            &MessageStream::slt_UpdateMsgFilter
           );

    connect(
            msgFilter,
            &IMessageFilter::sgnl_TimestampFilterHasChanged,
            this,
            &MessageStream::slt_UpdateTimestampFilter
           );
}

void MessageStream::connectMsgStorage()
{
    //ToDO
    
    connect(
            &msgStorage,
            &TimestampedMsgStorage::sgnl_MsgAdded,
            this,
            &MessageStream::slt_receiveMessage
           );
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

