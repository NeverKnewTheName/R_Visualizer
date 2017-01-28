/**
  * \file MsgStorage.cpp
  * \author Christian Neuberger
  * \date 22.11.2016
  *
  * \brief Dynamic storage of huge amounts of messages with automated serializing to and from temporary files
  */
#ifndef MSGSTORAGE_H
#define MSGSTORAGE_H

#include <QVector>
#include <QDir>
#include "msg.h"


struct ContainerID{
    int ContainerNR;
    int IndexInStore;

    ContainerID(const int index = -1, const int indexInStore = -1) : ContainerNR(index), IndexInStore(indexInStore){}
    bool operator ==(const ContainerID &other) const { return (ContainerNR == other.ContainerNR); }
    bool operator >(const ContainerID &other) const { return (ContainerNR > other.ContainerNR); }
    bool operator <(const ContainerID &other) const { return (ContainerNR < other.ContainerNR); }
    bool isValidIndex() const { return (ContainerNR >=0); }
    bool isValid() const { return ( ( ContainerNR >= 0 ) && ( IndexInStore >= 0 ) ); }
};

/**
 * \brief Simple RingBuffer that destroys elements on overflow
 */
template<typename T> class RSimpleDestructiveRingBuff
{
public:
    /**
     * \brief constructs the ring buffer with the given size
     * 
     * \param[in] size    Size to set for the ring buffer
     */
    RSimpleDestructiveRingBuff(const int size) :
        RBufBuffer(size),
        RBufSize(size),
        RBufCurSize(0),
        RBufStartIndex(0),
        RBufEndIndex(size-1)
    {
    }

    /**
     * \brief append an element to the current end of the ring buffer
     * 
     * if the size of the ring buffer is exceeded the first element is overriden
     * the ring buffers location pointers are adapted accordingly
     */
    void append(const T &value)
    {
        if(RBufCurSize == RBufSize)
        {
            IncrementIndex(RBufStartIndex);// = (RBufStartIndex + 1) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }
        IncrementIndex(RBufEndIndex);// = ( RBufEndIndex +1 ) % RBufSize;

        RBufBuffer.replace(RBufEndIndex, value);
    }

    /** 
     * \brief prepend an element to the current start of the ring buffer
     * if the size of the ring buffer is exceeded the last element is overriden
     * the ring buffers location pointers are adapted accordingly
     */
    void prepend(const T &value)
    {
        if(RBufCurSize == RBufSize)
        {
            DecrementIndex(RBufEndIndex);// = (RBufEndIndex - 1+RBufSize) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }
        DecrementIndex(RBufStartIndex);// = (RBufStartIndex - 1+RBufSize) % RBufSize; //Negative modulo...

        RBufBuffer.replace(RBufStartIndex, value);
    }

    /**
     * \brief replaces the element at the given index with the given value
     */
    void replace(const int index, const T &value)
    {
        RBufBuffer.replace((index + RBufStartIndex ) % RBufSize, value);
    }

    /**
     * \brief removes the element at the given index from the ring buffer
     * 
     * The ring buffer's location pointers are adapted accordindly
     */
    void remove(const int index)
    {
        int calcdIndex = ( index + RBufStartIndex ) % RBufSize;
        if(calcdIndex < RBufCurSize)
        {
            if( calcdIndex == RBufStartIndex )
            {
                //Remove first
                IncrementIndex(RBufStartIndex);
            }
            else if( calcdIndex == RBufEndIndex )
            {
                //Remove last
                DecrementIndex(RBufEndIndex);
            }
            else
            {
                //Remove somewhere between...
                while(calcdIndex != RBufEndIndex)
                {
                    T &ToReplace = RBufBuffer[calcdIndex];
                    IncrementIndex(calcdIndex);
                    ToReplace = RBufBuffer[calcdIndex];
                }

                DecrementIndex(RBufEndIndex);// = (RBufEndIndex - 1+RBufSize) % RBufSize;
            }

            RBufCurSize--;
        }
    }

    /** 
     * \brief retrieves the current first element of the ring buffer
     * 
     * The first element is the element pointed to by the ring buffer's
     * start pointer.
     */
    const T &first() const
    {
        return RBufBuffer.at(RBufStartIndex);
    }

    /**
     * \brief retrieves the current last element of the ring buffer
     * 
     * The last element is the element pointed to by the ring buffer's
     * end pointer
     */
    const T &last() const
    {
        return RBufBuffer.at(RBufEndIndex);
    }

    /**
     * \brief retrieves the current element at the given index
     */
    const T &at(const int index) const
    {
        const int calcdIndex = ( index + RBufStartIndex ) % RBufSize;
        //        qDebug() << __PRETTY_FUNCTION__ << "CalcdIndex: " << calcdIndex;
        return RBufBuffer.at(calcdIndex);
    }

    /**
     * \brief verfifies that a given value is contained in the ring buffer
     */
    bool contains(const T &value) const
    {
        return RBufBuffer.contains(value);
    }

    /**
     * \brief returns the location of a given value in the ring buffer
     * 
     * if the value is not contained in the ring buffer -1 is returned.
     */
    int find(const T&value) const
    {
        int curIndex = RBufCurSize;
        while(curIndex--)
        {
            const T&found = at(curIndex);
            if(value == found)
                return curIndex;
        }
        return -1;
    }

    /**
     * \brief returns the current size of the ring buffer
     * 
     * \note the size of the ring buffer never exceeds its set size, 
     * however the current size of the ring buffer can be smaller.
     */
    int size() const
    {
        return RBufCurSize;
    }

    int capacity() const
    {
        return RBufBuffer.capacity();
    }

    /**
     * \brief clears the ring buffer and resets its location pointers
     * 
     * \warning This does not free the contained elements!
     */
    void clear()
    {
        RBufBuffer = QVector<T>(RBufSize);
        RBufCurSize = 0;
        RBufStartIndex = 0;
        RBufEndIndex = RBufSize-1;
    }

private:
    int DecrementIndex(int &index)
    {
        index = (index - 1+RBufSize) % RBufSize; //Negative modulo...
        return index;
    }
    int IncrementIndex(int &index)
    {
        index = (index + 1) % RBufSize;
        return index;
    }

    QVector<T> RBufBuffer;
    const int RBufSize;
    int RBufCurSize;
    int RBufStartIndex;
    int RBufEndIndex;
};

class MsgStorage
{
public:
    /**
     * \brief One message container
     * 
     * A MsgContainer is a simple vector that holds Msgs
     */
    typedef QVector<Msg> MsgContainer;
    /**
     * \brief one conteiner to store message containers
     * 
     * A MsgContainerStore is a simple vector that holds MsgContainers
     */
    typedef QVector<MsgContainer> MsgContainerStore;

    /**
     * @brief Constructs a MsgStorage object with the given metrics
     * @param[in] ContainerSize             Size of one container in the MsgStore
     * @param[in] NrOfContainersToKeepInRAM Nr of containers to keep in RAM at a time
     *
     * \note If 0 is entered for either parameter, the respective paramter is set to 1
     *
     * \note The given default values are optimal for most applications.
     *       The middle container (index 1) can be used to retrieve data.
     *       If its size is exceeded or a lower index is requested
     *       the next container is already loaded
     *       (also this will trigger the container on the other side to be serialized
     *       and the next container to be loaded into RAM)
     */
    MsgStorage(const int ContainerSize = 1000, const int NrOfContainersToKeepInRAM = 3);

    /**
     * @brief at
     * @param index
     * @return
     *
     * \note This function returns a copy of the retrieved Msg because
     *       it cannot be guaranteed that the retrieved Msg is held in
     *       RAM; it can even not be guaranteed that a reference would
     *       be up to date...
     */
    Msg at(const int index);

    /**
     * \brief appends a messages to the MsgStorage with a move operation
     */
    void append(Msg &&value);
    /**
     * \brief appends a message to the MsgStorage with a copy operation
     */
    void append( const Msg &value );
    /**
     * \brief replaces the message at the given index with the new message
     */
    void replace( const int index, const Msg &value );
    /**
     * \brief remove the message at the given index
     */
    void remove( const int index );

    /**
     * \brief clears the MsgStorage
     * 
     * \warning This does not free the contained elements!
     */
    void clear();

    /**
     * \brief returns the current size of the MsgStorage
     */
    int size() const;
    /**
     * \brief returns whether the MsgStorage is empty
     */
    bool isEmpty() const;
    /**
     * \brief returns the current memory usage of the MsgStorage
     */
    int MemUsage() const;

    /**
     * \brief parses the whole MsgStorage to a JSON document
     */
    QJsonDocument parseToJson() const;
    /**
     * \brief reads in a MsgStorage from a JSON document
     */
    bool parseFromJson(const QJsonArray &jsonMsgsArray);
private:
    /**
     * @brief SerializeToFile
     * @param IndexInStore
     *
     * \note This does not invalidate the given index!
     */
    void SerializeToFile(const ContainerID &containerID);
    void SerializeToFile(const int ContainerNr, const MsgContainer &ContainerToSerializeTo);

    /**
     * @brief SerializeToFile
     * @param IndexInStore
     *
     * \note The MsgContainer at the given index is replaced with the MsgContainer that is loaded from the file!
     */
    void SerializeFromFile(const ContainerID &IndexInStoreToInsertIn);

    void appendHelper();
    void fetchContainerFromFileToRAM(ContainerID &ContainerIDToFetch);
    void fetchContainerIDHelper(ContainerID &ContainerIDToFetch);

private:
    MsgContainerStore MsgStore; //!< The storage of the MsgContainers
    MsgContainer LastContainer; //!< LastContainer is kept in memory permanently because of append method!
    QVector<QString> ContainerFileNames;
    const int ContainerSize;               //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    const int NrOfContainersToKeepInRAM;        //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    RSimpleDestructiveRingBuff<ContainerID> ContainerInRAMIndexMapping; //!< Ring buffer that stores the mapping of indices that are kept in RAM (MsgStore)
    const QString FilePrefix;
    QDir MsgStorageTempDir;
    int CurrentSize;
    int CurrentNrOfContainers;
    int CurrentFileNr;

    static int MsgStorageCntr;
};

#endif // MSGSTORAGE_H
