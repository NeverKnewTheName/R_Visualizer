#include "MessageStream.h"

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
    msgConfig(msgConfig),
    msgFilter(msgFilter),
    msgStreamStore(msgStreamStore),
    msgStorage(msgStorage),
    indexStore(msgStreamStore->getBufferSize()),
    continuousFlag(true)
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

bool MessageStream::appendMsg(
        const ITimestampedMsg &msgToAppend,
        const int indexInStore
        )
{
    if(continuousFlag)
    {
        return appendHelper(msgToAppend,indexInStore);
    }
    else
    {
        return false;
    }
}

bool MessageStream::prependMsg(
        const ITimestampedMsg &msgToPrepend,
        const int indexInStore
        )
{
    if(continuousFlag)
    {
        return prependHelper(msgToPrepend,indexInStore);
    }
    else
    {
        return false;
    }
}

void MessageStream::clear()
{
    msgStorage.clear();
    msgStreamStore->clear();
    indexStore.clear();
}

void MessageStream::setCurrentStartIndex(const int newStartIndex)
{
    indexStore.prepend(newStartIndex);
}

int MessageStream::getCurrentStartIndex() const
{
    if(indexStore.size())
    {
        return indexStore.first();
    }
    else
    {
        return 0;
    }
}

void MessageStream::setCurrentEndIndex(const int newEndIndex)
{
    indexStore.append(newEndIndex);
}

int MessageStream::getCurrentEndIndex() const
{
    if(indexStore.size())
    {
        return indexStore.last();
    }
    else
    {
        return 0;
    }
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
    msgStreamStore->clear();
    int currentEndIndex = getCurrentEndIndex();
    indexStore.clear();

    const int msgStreamStoreBufferSize =
            msgStreamStore->getBufferSize();

    /*
     * Filter from the current end index downward
     */
    while(msgStreamStore->size() != msgStreamStoreBufferSize)
    {
        const ITimestampedMsg &msgToAdd =
                msgStorage.at(currentEndIndex);

        prependHelper(msgToAdd,currentEndIndex);

        if(currentEndIndex == 0)
        {
            break;
        }

        currentEndIndex--;
    }

    /*
     * IF there are not enough messages in the msgStreamStore AND
     * there are more messages available in the msgStorage, then
     * search upward to find more messages
     */
    if(msgStreamStore->size() != msgStreamStoreBufferSize)
    {
        int newCurrentEndIndex = getCurrentEndIndex();
        newCurrentEndIndex++;
        /*
         * Search upward
         */
        while(newCurrentEndIndex < msgStorage.size())
        {
            const ITimestampedMsg &msgToAdd =
                    msgStorage.at(newCurrentEndIndex);
            appendHelper(msgToAdd,newCurrentEndIndex);

            newCurrentEndIndex++;

            if(msgStreamStore->size() == msgStreamStore->getBufferSize())
            {
                break;
            }
        }
    }
}

void MessageStream::updateTimestampFilter(
        const ITimestampedMsgFilter &filterToUpdate
        )
{
    msgStreamStore->clear();
    int currentEndIndex = getCurrentEndIndex();
    indexStore.clear();

    const int msgStreamStoreBufferSize =
            msgStreamStore->getBufferSize();

    /*
     * Filter from the current end index downward
     */
    while(msgStreamStore->size() != msgStreamStoreBufferSize)
    {
        const ITimestampedMsg &msgToAdd =
                msgStorage.at(currentEndIndex);

        prependHelper(msgToAdd,currentEndIndex);

        if(currentEndIndex == 0)
        {
            break;
        }

        currentEndIndex--;
    }

    /*
     * IF there are not enough messages in the msgStreamStore AND
     * there are more messages available in the msgStorage, then
     * search upward to find more messages
     */
    if(msgStreamStore->size() != msgStreamStoreBufferSize)
    {
        int newCurrentEndIndex = getCurrentEndIndex();
        newCurrentEndIndex++;
        /*
         * Search upward
         */
        while(newCurrentEndIndex < msgStorage.size())
        {
            const ITimestampedMsg &msgToAdd =
                    msgStorage.at(newCurrentEndIndex);
            appendHelper(msgToAdd,newCurrentEndIndex);

            newCurrentEndIndex++;

            if(msgStreamStore->size() == msgStreamStore->getBufferSize())
            {
                break;
            }
        }
    }
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
    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_msgAppended, */
    /*         this, */
    /*         &IMessageStream::sgnl_messageAdded */
    /*        ); */

    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_msgPrepended, */
    /*         this, */
    /*         &IMessageStream::sgnl_messageAdded */
    /*        ); */

    /* connect( */
    /*         msgStreamStore, */
    /*         &IMsgStreamStore::sgnl_storeCleared, */
    /*         this, */
    /*         &IMessageStream::sgnl_streamCleared */
    /*        ); */
}

bool MessageStream::appendHelper(const ITimestampedMsg &msgToAppend, const int indexInStore)
{
    if(msgFilter->filterMessage(msgToAppend))
    {
        IPrettyMsg &prettifiedMsg = msgStreamStore->appendMsg(msgToAppend);

        msgConfig->prettifyMsg(prettifiedMsg);

        setCurrentEndIndex(indexInStore);

        return true;
    }
    else
    {
        return false;
    }
}

bool MessageStream::prependHelper(const ITimestampedMsg &msgToPrepend, const int indexInStore)
{
    if(msgFilter->filterMessage(msgToPrepend))
    {
        IPrettyMsg &prettifiedMsg = msgStreamStore->prependMsg(msgToPrepend);

        msgConfig->prettifyMsg(prettifiedMsg);

        setCurrentStartIndex(indexInStore);

        return true;
    }
    else
    {
        return false;
    }
}

bool MessageStream::getContinuousFlag() const
{
    return continuousFlag;
}

void MessageStream::setContinuousFlag(bool value)
{
    continuousFlag = value;
}

void MessageStream::accept(FileParser *visitor)
{
    msgStorage.accept(visitor);
}

bool MessageStream::fetchPrevious()
{
    int currentStartIndex = getCurrentStartIndex();

    while(currentStartIndex > 0)
    {
        currentStartIndex--;

        const ITimestampedMsg &msgToFetch =
                msgStorage.at(currentStartIndex);

        if(prependHelper(msgToFetch, currentStartIndex))
        {
            return true;
        }
    }

    return false;
}

bool MessageStream::fetchNext()
{
    int currentEndIndex = getCurrentEndIndex()+1;
    const int msgStorageSize = msgStorage.size();

    while(currentEndIndex < msgStorageSize)
    {
        const ITimestampedMsg &msgToFetch =
                msgStorage.at(currentEndIndex);

        if(appendHelper(msgToFetch, currentEndIndex))
        {
            return true;
        }

        currentEndIndex++;
    }

    return false;
}


bool MessageStream::fetchTop()
{
    msgStreamStore->clear();
    indexStore.clear();
    int currentEndIndex = 0;
    const int msgStorageSize = msgStorage.size();
    const int msgStreamStoreBufferSize = msgStreamStore->getBufferSize();

    while(currentEndIndex < msgStorageSize)
    {
        const ITimestampedMsg &msgToFetch =
                msgStorage.at(currentEndIndex);

        appendHelper(msgToFetch, currentEndIndex);

        currentEndIndex++;

        if(msgStreamStore->size() == msgStreamStoreBufferSize)
        {
            break;
        }
    }
}

bool MessageStream::fetchBottom()
{
    msgStreamStore->clear();
    indexStore.clear();
    int currentStartIndex = msgStorage.size();
    const int msgStreamStoreBufferSize = msgStreamStore->getBufferSize();

    while(currentStartIndex--)
    {
        const ITimestampedMsg &msgToFetch =
                msgStorage.at(currentStartIndex);

        prependHelper(msgToFetch, currentStartIndex);

        if(msgStreamStore->size() == msgStreamStoreBufferSize)
        {
            break;
        }
    }
}
