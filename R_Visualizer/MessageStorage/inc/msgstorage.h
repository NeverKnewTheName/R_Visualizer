/**
  * \file msgstorage.h
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

#include "rsimpleringbuff.h"

/**
 * \brief The ContainerID is the mapping of a container to a given MsgStore in the MsgStorage
 */
struct ContainerID{
    int ContainerNR; //!< ID of the given MsgStore
    int IndexInStore; //!< Index of the MsgStore in the MsgStorage

    /**
     * \brief Constructs a new ContainerID
     */
    ContainerID(const int index = -1, const int indexInStore = -1) : ContainerNR(index), IndexInStore(indexInStore){}
    /**
     * \brief compares the ContainerNR of two containers for equal
     * 
     * \note Two ContainerID are equal if their ContainerNR is equal.
     */
    bool operator ==(const ContainerID &other) const { return (ContainerNR == other.ContainerNR); }
    /**
     * \brief Compares a ContainerID to this containr if its ContainerNR is lower
     */
    bool operator >(const ContainerID &other) const { return (ContainerNR > other.ContainerNR); }
    /**
     * \brief Compares a ContainerID to this containr if its ContainerNR is greater
     */
    bool operator <(const ContainerID &other) const { return (ContainerNR < other.ContainerNR); }
    /**
     * \brief Returns whether a ContainerID is valid in general
     * 
     * A ContainerID is valid in general if it has a ContainerNR that is greater than zero, 
     * because a ContainerNR of -1 is used to signal an invlaid ContainerID.
     */
    bool isValidIndex() const { return (ContainerNR >=0); }
    /**
     * \brief Returns whether a ContainerID is valid and has valid a valid mapping
     */
    bool isValid() const { return ( ( ContainerNR >= 0 ) && ( IndexInStore >= 0 ) ); }
};


/**
 * \brief MsgStorage to store huge numbers of messages
 * 
 * Since the recording of messages is continuous, a huge number of messages need to be stored.
 * To accomplish this task without devouring most of the system ressources, only a defined 
 * portion of all messages is kept in RAM, whereas the rest of the messages is written to 
 * files.
 */
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
     * \brief one container to store message containers
     * 
     * A MsgContainerStore is a simple vector that holds MsgContainers
     */
    typedef QVector<MsgContainer> MsgContainerStore;

    /**
     * @brief Constructs a MsgStorage object with the given metrics
     * @param[in] ContainerSize             Size of one container in the MsgStore
     * @param[in] NrOfContainersToKeepInRAM Nr of containers to keep in RAM at a time
     *
     * \note If 0 is entered for either parameter, the respective parameter is set to 1
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
    Msg at(const size_t index);

    Msg operator[](const size_t index);

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

    /**
     * \brief Maintenance of containers before appending an element to the #MsgStorage
     * 
     * The appendHelper evaluates whether the element to append will exceed the size boundaries of 
     * the current #LastContainer and calculates the index for the element.
     * 
     * If the element does not fit into the current #LastContainer, the current #LastContainer is saved
     * according to the following scheme and a new #LastContainer is created.
     * 
     * If the #CurrentNrOfContainers does not exceed the #NrOfContainersToKeepInRAM, the current #LastContainer
     * is appended to the #MsgStore.
     * Else if the current #LastContainer is the next successor to the last container in RAM, the first container
     * in RAM is saved to disk and removed from the #MsgStore and the current #LastContainer is append to the 
     * #MsgStore.
     * Else if none of the above applies, the current #LastContainer is saved to disk and no further
     * actions are taken.
     */
    void appendHelper();
    /**
     * \brief Load a previously saved container from its file into the #MsgStore
     * 
     * the fetchContainerFromFileToRAM method loads a container that was previously saved by
     * writing it to a file back into the #MsgStore. The #MsgStore is adjusted accordingly.
     * 
     * If the ContainerID of the fetched container is greater than the ContainerID of the current
     * last container in the #MsgStore, the first container in the #MsgStore is saved to a file
     * and removed from teh #MsgStore. The newly fetched container is then appended to the #MsgStore.
     * 
     * Else if the ContainerID of the fetched container is lower than the ContainerID of the current
     * first container in the #MsgStore, the last container in the #MsgStore is saved to a file
     * and removed from the #MsgStore. The newly fetched container is then prepended to the #MsgStore.
     * 
     * Else if none of the above applies, the ContainerID of the fetched container is compared against
     * all containers' ContainerID in the #MsgStore. Starting from the last container, the first ContainerID
     * of a container that is lower than the fetched container's ContainerID determines the container 
     * to save to file and remove from the #MsgStore to make space for the fetched container.
     */
    void fetchContainerFromFileToRAM(ContainerID &ContainerIDToFetch);
    /**
     * \brief Determines wheter the container with the given ContainerID is alread in the #MsgStore or needs to be fetched.
     * 
     * \param[inout] ContainerIDToFetch     Must contain the ContainerNR of the container to fetch. Will contain the IndexInStore
     *                                      that the container has in the #MsgStore.
     *                                      
     * \pre The given ContainerID must contain a valid ContainerNR
     * \post The given ContainerID contains the IndexInStore of the queried container
     * \post If the container with the given ContainerNR was not already loaded into the #MsgStore
     * it is loaded into the #MsgStore during this method. All rules of #fetchContainerFromFileToRAM then apply!
     * 
     * If the container with the ContainerNR contained in the given ContainerID is in the #MsgStore, the IndexInStore is
     * inserted into the ContainerID.
     * If the container with the ContainerNr contained in the given ContainerID is not the #MsgStore, it is fetched
     * from the file it was written to previously with the #fetchContainerFromFileToRAM method.
     */
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
