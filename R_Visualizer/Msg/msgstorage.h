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
    bool isValid() const { return ( ( ContainerNR >= 0 ) && ( IndexInStore >= 0 ) ); }
};

template<typename T> class RSimpleDestructiveRingBuff
{
public:
    RSimpleDestructiveRingBuff(const int size) :
        RBufBuffer(size),
        RBufSize(size),
        RBufCurSize(0),
        RBufStartIndex(0),
        RBufEndIndex(size-1)
    {
    }

    void append(const T &value)
    {
        RBufEndIndex = ( RBufEndIndex +1 ) % RBufSize;

        if(RBufCurSize == RBufSize)
        {
            RBufStartIndex = (RBufStartIndex + 1) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }

        RBufBuffer.replace(RBufEndIndex, value);
    }

    void prepend(const T &value)
    {
        RBufStartIndex = (RBufStartIndex - 1+RBufSize) % RBufSize; //Negative modulo...

        if(RBufCurSize == RBufSize)
        {
            RBufEndIndex = (RBufEndIndex - 1+RBufSize) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }

        RBufBuffer.replace(RBufStartIndex, value);
    }

    void replace(const int index, const T &value)
    {
        RBufBuffer.replace((index + RBufStartIndex ) % RBufSize, value);
    }

    const T &first() const
    {
        return RBufBuffer.at(RBufStartIndex);
    }
    const T &last() const
    {
        return RBufBuffer.at(RBufEndIndex);
    }

    const T &at(const int index) const
    {
        const int calcdIndex = ( index + RBufStartIndex ) % RBufSize;
//        qDebug() << __PRETTY_FUNCTION__ << "CalcdIndex: " << calcdIndex;
        return RBufBuffer.at(calcdIndex);
    }

    bool contains(const T &value) const
    {
        return RBufBuffer.contains(value);
    }

    T find(const T&value) const
    {
        int curIndex = RBufCurSize;
        while(curIndex--)
        {
            const T&found = at(curIndex);
            if(value == found)
                return found;
        }
        return T();
    }

    int size() const
    {
        return RBufCurSize;
    }

    int capacity() const
    {
        return RBufBuffer.capacity();
    }

    void clear()
    {
        RBufBuffer = QVector<T>(RBufSize);
        RBufCurSize = 0;
        RBufStartIndex = 0;
        RBufEndIndex = RBufSize-1;
    }

private:
    QVector<T> RBufBuffer;
    const int RBufSize;
    int RBufCurSize;
    int RBufStartIndex;
    int RBufEndIndex;
};

class MsgStorage
{
public:
    typedef QVector<Msg> MsgContainer;
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

    void append(Msg &&value);
    void append( const Msg &value );
    void replace( const int index, const Msg &value );
    void remove( const int index );

    void clear();

    int size() const;
    bool isEmpty() const;
    int MemUsage() const;

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
    void fetchContainerFromFile(ContainerID &ContainerIDToFetch);
    void fetchContainerIDHelper(ContainerID &ContainerIDToFetch);

private:
    MsgContainerStore MsgStore;
    MsgContainer LastContainer; //!< LastContaine is kept in memory permanently because of append method!
    QVector<QString> ContainerFileNames;
    const int ContainerSize;               //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    const int NrOfContainersToKeepInRAM;        //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    RSimpleDestructiveRingBuff<ContainerID> ContainerInRAMIndexMapping;
    const QString FilePrefix;
    QDir MsgStorageTempDir;
    int CurrentSize;
    int CurrentNrOfContainers;
    int CurrentFileNr;

    static int MsgStorageCntr;
};

#endif // MSGSTORAGE_H
