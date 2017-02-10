/**
  * \file datastorage.h
  * \author Christian Neuberger
  * \date 22.11.2016
  *
  * \brief Dynamic storage of huge amounts of objects with automated serializing to and from temporary files
  */
#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QVector>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "rsimpleringbuff.h"

//ToDELETE... needed because no interface yet..
#include "msg.h"
#include <QDebug>
#define  PRINT_MSGS_AS_JSON

/**
 * \brief The ContainerID is the mapping of a container to a given DataStore in the DataStorage
 */
struct ContainerID{
    size_t ContainerNR; //!< ID of the given DataStore
    size_t IndexInStore; //!< Index of the DataStore in the DataStorage

    /**
     * \brief Constructs a new ContainerID
     */
    ContainerID(const size_t index = -1, const size_t indexInStore = -1) : ContainerNR(index), IndexInStore(indexInStore){}
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
 * \brief DataStorage to store huge numbers of messages
 * 
 * Since the recording of messages is continuous, a huge number of messages need to be stored.
 * To accomplish this task without devouring most of the system ressources, only a defined 
 * portion of all messages is kept in RAM, whereas the rest of the messages is written to 
 * files.
 * 
 * Internally the DataStorage object uses QVectors to manage data that is kept in RAM.
 * For efficient use of this DataStorage declare types that are used with the DataStorage
 * the same as one would declare types that are to be used with QVector:
 * as a Q_MOVABLE_TYPE
 */
template<typename T>
class DataStorage
{
public:
    /**
     * \brief One data container
     * 
     * A DataContainer is a simple QVector that holds Msgs
     */
    typedef QVector<T> DataContainer;
    /**
     * \brief one container to store message containers
     * 
     * A DataContainerStore is a simple QVector that holds multiple #DataContainer
     */
    typedef QVector<DataContainer> DataContainerStore;

    /**
     * @brief Constructs a #DataStorage object with the given metrics
     * @param[in] ContainerSize             Size of one #DataContainer in the #DataContainerStore
     * @param[in] NrOfContainersToKeepInRAM Nr of #DataContainer to keep in RAM at a time
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
    DataStorage(const typename DataContainer::size_type ContainerSize = 1000, const typename DataContainer::size_type NrOfContainersToKeepInRAM = 3) :
        ContainerSize((!ContainerSize) ? 1 : ContainerSize),
        NrOfContainersToKeepInRAM((!NrOfContainersToKeepInRAM) ? 1 : NrOfContainersToKeepInRAM),
        ContainerInRAMIndexMapping(NrOfContainersToKeepInRAM),
        FilePrefix(QString("RDataStore_%1_").arg(DataStorageCntr++)),
        CurrentSize(0),
        CurrentNrOfContainers(0),
        CurrentFileNr(0)
    {
        QString DataStoreTempDirName(QString("RDataStoreTmp_%1").arg(DataStorageCntr));

        if(!DataStorageTempDir.exists(DataStoreTempDirName))
        {
            DataStorageTempDir.mkdir(DataStoreTempDirName);
        }
        //    else
        //    {
        //        DataStorageTempDir.setPath(DataStoreTempDirName);
        //        QFileInfoList fileInfLst = DataStorageTempDir.entryInfoList();
        //        for(auto &&fileInf : fileInfLst)
        //        {
        //            if(!fileInf.isFile())
        //                continue;
        //            DataStorageTempDir.remove(fileInf.baseName());
        //        }
        //    }

        DataStorageTempDir.setPath(DataStoreTempDirName);
        //    qDebug() << DataStorageTempDir.path();

        //DataContainerStore is reserved upfront to get rid of fragmentation and unneccessary allocations
        DataStore.reserve(NrOfContainersToKeepInRAM);
        LastContainer.reserve(ContainerSize);
    }

    ~DataStorage()
    {

    }

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
    T at(const typename DataContainer::size_type index)
    {
        const typename DataContainer::size_type containerIndex = index / ContainerSize;
        const typename DataContainer::size_type indexInContainer = index % ContainerSize;

        if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
            return Msg();

        if( containerIndex == CurrentNrOfContainers )
        {
            //ShortCut to LastContainer
            return LastContainer.value(indexInContainer);
        }

        ContainerID fetchedContainerID( containerIndex );
        fetchContainerIDHelper(fetchedContainerID);

        if(fetchedContainerID.IndexInStore == -1)
            return Msg();

        const DataContainer &RelatedContainer = DataStore.at(fetchedContainerID.IndexInStore);

        return RelatedContainer.at(indexInContainer);
    }
    /**
     * \brief Operator wrapper for #at
     */
    T operator[](const typename DataContainer::size_type index)
    {
     return at(index);
    }

    /**
     * \brief appends a messages to the DataStorage with a move operation
     */
    void append(T &&value)
    {
        appendHelper();
        LastContainer.append(std::move(value));
    }

    /**
     * \brief appends a message to the DataStorage with a copy operation
     */
    void append( const T &value )
    {
        appendHelper();
        LastContainer.append(value);
    }

    /**
     * \brief replaces the message at the given index with the new message
     */
    void replace( const typename DataContainer::size_type index, const T &value )
    {
        const typename DataContainer::size_type containerIndex = index / ContainerSize;
        const typename DataContainer::size_type indexInContainer = index % ContainerSize;

        //    qDebug() << "index: " << index << " ContainerIndex " << containerIndex 
        //             << " IndexInContainer " << indexInContainer;

        if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
            return;

        if( containerIndex == CurrentNrOfContainers )
        {
            //ShortCut to LastContainer
            LastContainer.replace(indexInContainer, value);
            return;
        }

        ContainerID fetchedContainerID( containerIndex );
        fetchContainerIDHelper(fetchedContainerID);

        //    qDebug() << "Fetched ContainerID container " << fetchedContainerID.ContainerNR 
        //             << " IndexInStore " << fetchedContainerID.IndexInStore;

        if(!fetchedContainerID.isValid())
            return;

        DataStore[fetchedContainerID.IndexInStore].replace(indexInContainer, value);
    }

    /**
     * \brief remove the message at the given index
     */
    void remove( const typename DataContainer::size_type index )
    {
        typename DataContainer::size_type containerIndex = index / ContainerSize;
        typename DataContainer::size_type indexInContainer = index % ContainerSize;

        if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
            return;

        if( containerIndex == CurrentNrOfContainers )
        {
            //ShortCut to LastContainer
            LastContainer.remove(indexInContainer);
            CurrentSize--;
        }
        else
        {
            ContainerID ContainerIDToRemoveValueFrom(containerIndex);
            QJsonArray  curJsonMsgsArr;
            QJsonArray  recentJsonMsgsArr;
            Msg curMsg;
            typename DataContainer::size_type recentContainerNR;
            bool recentContainerWasLoaded = false;

            //Handle container that contains the element to remove
            if(ContainerInRAMIndexMapping.contains(ContainerIDToRemoveValueFrom))
            {
                //Is in RAM
                ContainerIDToRemoveValueFrom = ContainerInRAMIndexMapping.at(
                        ContainerInRAMIndexMapping.find(ContainerIDToRemoveValueFrom)
                        );
                try {
                    DataStore[ContainerIDToRemoveValueFrom.IndexInStore].remove(indexInContainer);
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                recentContainerNR = ContainerIDToRemoveValueFrom.ContainerNR;
                recentContainerWasLoaded = false;
            }
            else
            {
                //Needs to be loaded...
                QFile MsgDataTempFile(ContainerFileNames[containerIndex]);
                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__ << __LINE__ <<": ERROR - File does not exist! Name: " 
                             << MsgDataTempFile.fileName();
                }

                if(!MsgDataTempFile.open(QIODevice::ReadOnly)) {
                    qDebug() << "error opening: " << MsgDataTempFile.fileName();
                }

#ifdef  PRINT_MSGS_AS_JSON
                curJsonMsgsArr = QJsonDocument::fromJson(
                        MsgDataTempFile.readAll()).array();
#else
                curJsonMsgsArr = QJsonDocument::fromBinaryData(
                        MsgDataTempFile.readAll(),QJsonDocument::BypassValidation
                        ).array();
#endif
                MsgDataTempFile.close();
                curJsonMsgsArr.removeAt(indexInContainer);
                recentJsonMsgsArr = std::move(curJsonMsgsArr);
                recentContainerWasLoaded = true;
            }
            recentContainerNR = containerIndex;
            containerIndex++;
            ContainerIDToRemoveValueFrom = ContainerID(containerIndex);


            //Handle all subsequent containers

            while(containerIndex < CurrentNrOfContainers)
            {
                if(ContainerInRAMIndexMapping.contains(ContainerIDToRemoveValueFrom))
                {
                    //Is in RAM
                    ContainerIDToRemoveValueFrom = ContainerInRAMIndexMapping.at(ContainerInRAMIndexMapping.find(ContainerIDToRemoveValueFrom));

                    DataContainer &curContainer = DataStore[ContainerIDToRemoveValueFrom.IndexInStore];
                    curMsg = curContainer.first();
                    curContainer.removeFirst();
                    if(curContainer.isEmpty())
                    {
                        typename DataContainer::size_type tempContainerIndex = containerIndex;
                        CurrentNrOfContainers--;
                        if(CurrentNrOfContainers > 1 )
                        {
                            //delete from ram, fetch other..
                            if( tempContainerIndex == 0)
                            {
                                //Is first container, start search from back
                                tempContainerIndex = CurrentNrOfContainers-1;
                            }
                            ContainerID ContainerIDNextToLoad(tempContainerIndex);
                            //Find nextlower container to load into ram...
                            while(ContainerInRAMIndexMapping.contains(ContainerIDNextToLoad))
                            {
                                ContainerIDNextToLoad = ContainerID(ContainerIDNextToLoad.ContainerNR-1);
                            }
                            ContainerIDNextToLoad.IndexInStore = ContainerIDToRemoveValueFrom.IndexInStore;
                            try {
                                SerializeFromFile(ContainerIDNextToLoad);
                            } catch (const std::exception& e) {
                                qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                            }
                        }
                    }
                    curJsonMsgsArr = QJsonArray();
                }
                else
                {
                    //Needs to be loaded...
                    QFile MsgDataTempFile(ContainerFileNames[containerIndex]);
                    if(!MsgDataTempFile.exists())
                    {
                        qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                    }

                    if(!MsgDataTempFile.open(QIODevice::ReadOnly)) {
                        qDebug() << "error opening: " << MsgDataTempFile.fileName();
                    }

#ifdef PRINT_MSGS_AS_JSON
                    curJsonMsgsArr = QJsonDocument::fromJson(MsgDataTempFile.readAll()).array();
#else
                    curJsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();
#endif
                    MsgDataTempFile.close();
                    curMsg = Msg(curJsonMsgsArr.first().toObject());
                    curJsonMsgsArr.removeFirst();
                }

                if(recentContainerWasLoaded)
                {
                    //Handle if the previous container was loaded
                    recentJsonMsgsArr.append(curMsg.parseOUT());
                    QFile MsgDataTempFile(ContainerFileNames[recentContainerNR]);
                    if(!MsgDataTempFile.exists())
                    {
                        qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                    }

                    if(!MsgDataTempFile.open(QIODevice::WriteOnly)) {
                        qDebug() << "error opening: " << MsgDataTempFile.fileName();
                    }
#ifdef PRINT_MSGS_AS_JSON
                    MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toJson());
#else
                    MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toBinaryData());
#endif
                    MsgDataTempFile.flush();
                    MsgDataTempFile.close();
                }
                else
                {
                    ContainerID recentContainerID(recentContainerNR);
                    int foundIndex = ContainerInRAMIndexMapping.find(recentContainerID);
                    if(foundIndex < 0)
                    {
                        qDebug() << "ERROR Returned by RSimpleDestructiveRingBuff.find(): " << foundIndex;
                        qDebug() << "Faulty ContainerID: ContainerNR: " << recentContainerID.ContainerNR 
                                << "IndexInStore: " << recentContainerID.IndexInStore;
                    }
                    recentContainerID = ContainerInRAMIndexMapping.at(foundIndex);
                    if(recentContainerID.isValid())
                    {
                        DataStore[recentContainerID.IndexInStore].append(curMsg);
                    }
                }

                if(curJsonMsgsArr.isEmpty())
                {
                    recentContainerWasLoaded = false;
                }
                else
                {
                    recentContainerWasLoaded = true;
                }
                recentJsonMsgsArr = curJsonMsgsArr;
                recentContainerNR = containerIndex;
                containerIndex++;
                ContainerIDToRemoveValueFrom = ContainerID(containerIndex);
            }

            //Handle LastContainer
            curMsg = LastContainer.first();
            LastContainer.removeFirst();
            if(recentContainerWasLoaded)
            {
                recentJsonMsgsArr.append(curMsg.parseOUT());

                QFile MsgDataTempFile(ContainerFileNames[recentContainerNR]);
                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                }

                if(!MsgDataTempFile.open(QIODevice::WriteOnly)) {
                    qDebug() << "error opening: " << MsgDataTempFile.fileName();
                }
#ifdef PRINT_MSGS_AS_JSON
                MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toJson());
#else
                MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toBinaryData());
#endif
                MsgDataTempFile.flush();
                MsgDataTempFile.close();
            }
            else
            {
                ContainerID recentContainerID(recentContainerNR);

                recentContainerID = ContainerInRAMIndexMapping.at(ContainerInRAMIndexMapping.find(recentContainerID));
                if(recentContainerID.isValid())
                {
                    DataStore[recentContainerID.IndexInStore].append(curMsg);
                }
            }
            CurrentSize--;
        }

        //Handle if LastContainer is empty and needs to be adjusted
        if( LastContainer.isEmpty() && ( CurrentSize != 0 ) )
        {
            //Get ContainerID of the container preceding LastContainer
            ContainerID ContainerIDNextLastContainer(CurrentNrOfContainers-1);

            if(!ContainerIDNextLastContainer.isValidIndex())
            {
                qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "FAILURE: INVALID ContainerID";
            }

            //Check wether the next container to load is in the RAM mapping
            if(ContainerInRAMIndexMapping.contains(ContainerIDNextLastContainer))
            {
                //The next container to load is in RAM
                //Retrieve the corresponding container, assign it to last container and remove it from the RAM mapping
                const typename DataContainer::size_type indexInRamMapping = ContainerInRAMIndexMapping.find(ContainerIDNextLastContainer);
                ContainerIDNextLastContainer = ContainerInRAMIndexMapping.at(indexInRamMapping);
                LastContainer = DataStore.at(ContainerIDNextLastContainer.IndexInStore);
                ContainerInRAMIndexMapping.remove(indexInRamMapping);

                //Load the next lower container (if any) into RAM
                ContainerID ContainerIDNextToLoad(ContainerIDNextLastContainer.ContainerNR-1);
                if(ContainerIDNextToLoad.isValidIndex())
                {
                    //Find nextlower container, which is not already in RAM, to load into ram...
                    while(ContainerInRAMIndexMapping.contains(ContainerIDNextToLoad))
                    {
                        ContainerIDNextToLoad = ContainerID(ContainerIDNextToLoad.ContainerNR-1);
                        if(!ContainerIDNextToLoad.isValidIndex())
                        {
                            //There is no container to load into RAM...
                            break;
                        }
                    }
                    if(ContainerIDNextToLoad.isValidIndex())
                    {
                        //Found a container to load -> load into RAM
                        fetchContainerFromFileToRAM(ContainerIDNextToLoad);
                    }
                }
            }
            else
            {
                QFile MsgDataTempFile(ContainerFileNames[ContainerIDNextLastContainer.ContainerNR]);
                QJsonArray jsonMsgsArr;

                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " 
                             << MsgDataTempFile.fileName();
                }

                if(!MsgDataTempFile.open(QIODevice::ReadOnly)) {
                    qDebug() << "error opening: " << MsgDataTempFile.fileName();
                }

#ifdef PRINT_MSGS_AS_JSON
                jsonMsgsArr = QJsonDocument::fromJson(MsgDataTempFile.readAll()).array();
#else
                jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();
#endif

                MsgDataTempFile.close();

                for(auto&& item : jsonMsgsArr)
                {
                    LastContainer.append(std::move(Msg(item.toObject())));
                }
            }
            CurrentNrOfContainers--;
        }

        return;
    }

    /**
     * \brief clears the DataStorage
     * 
     * \warning This does not free the contained elements!
     */
    void clear()
    {
        DataStore.clear();
        LastContainer.clear();
        ContainerFileNames.clear();
        ContainerInRAMIndexMapping.clear();
        CurrentSize = 0;
        CurrentNrOfContainers = 0;
        CurrentFileNr = 0;
        QFileInfoList fileInfLst = DataStorageTempDir.entryInfoList();
        for(auto &&fileInf : fileInfLst)
        {
            if(!fileInf.isFile())
                continue;
            DataStorageTempDir.remove(fileInf.baseName());
        }
        QString curDirName = DataStorageTempDir.dirName();
        DataStorageTempDir.cdUp();
        DataStorageTempDir.rmdir(curDirName);

        DataStorageCntr++;
        QString DataStoreTempDirName(std::move(QString("RDataStoreTmp_%1").arg(DataStorageCntr)));

        if(!DataStorageTempDir.exists(DataStoreTempDirName))
        {
            DataStorageTempDir.mkdir(DataStoreTempDirName);
        }

        DataStorageTempDir.setPath(DataStoreTempDirName);
        //    qDebug() << DataStorageTempDir.path();

        //DataContainerStore is reserved upfront to get rid of fragmentation and unneccessary alocations
        DataStore.reserve(NrOfContainersToKeepInRAM);
        LastContainer.reserve(ContainerSize);
    }

    /**
     * \brief returns the current size of the DataStorage
     */
    typename DataContainer::size_type size() const
    {
        return CurrentSize;
    }

    /**
     * \brief returns whether the DataStorage is empty
     */
    bool isEmpty() const
    {
        return CurrentSize == 0;
    }

    /**
     * \brief returns the current memory usage of the DataStorage
     */
    typename DataContainer::size_type MemUsage() const
    {
        typename DataContainer::size_type FullMemUsage = 0;
        FullMemUsage += DataStore.capacity() * sizeof(DataContainer);
        for(const DataContainer &msgContainer : DataStore)
            FullMemUsage += msgContainer.capacity() * sizeof(Msg);
        FullMemUsage += LastContainer.capacity() * sizeof(Msg);
        FullMemUsage += ContainerFileNames.capacity() * sizeof(QFile);
        FullMemUsage += ContainerInRAMIndexMapping.capacity() * sizeof(ContainerID);

        return FullMemUsage;
    }

    /**
     * \brief parses the whole DataStorage to a JSON document
     */
    QJsonDocument ParseToJson() const
    {
        typename DataContainer::size_type curContainerNr = 0;
        const typename DataContainer::size_type NrOfLastContainer = CurrentNrOfContainers-1;
        QJsonArray msgsAsJsonObjsArray;

        // parse all containers either in file or RAM
        while(curContainerNr < NrOfLastContainer)
        {
            ContainerID curContainerIDToParse(curContainerNr);
            if(ContainerInRAMIndexMapping.contains(curContainerIDToParse))
            {
                //Is in RAM
                curContainerIDToParse = ContainerInRAMIndexMapping.at(ContainerInRAMIndexMapping.find(curContainerIDToParse));
                const DataContainer &curContainerToParse = DataStore.at(curContainerIDToParse.IndexInStore);
                for(const Msg &msg : curContainerToParse)
                {
                    msgsAsJsonObjsArray.append(msg.parseOUT());
                }
            }
            else
            {
                //Is a file
                QFile CurFileToParse(ContainerFileNames[curContainerNr]);
                if(!CurFileToParse.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " 
                             << CurFileToParse.fileName();
                }

                if(!CurFileToParse.open(QIODevice::ReadOnly)) {
                    qDebug() << "error opening: " << CurFileToParse.fileName();
                }

#ifdef PRINT_MSGS_AS_JSON
                QJsonArray tempArray = QJsonDocument::fromJson(
                        CurFileToParse.readAll()).array();
#else
                QJsonArray tempArray = QJsonDocument::fromBinaryData(
                        CurFileToParse.readAll(),QJsonDocument::BypassValidation
                        ).array();
#endif
                CurFileToParse.close();

                for(auto &&tmpElement : tempArray)
                {
                    msgsAsJsonObjsArray.append(tmpElement);
                }
            }
            curContainerNr++;
        }

        //parse last container
        for(const Msg &msg : LastContainer)
        {
            msgsAsJsonObjsArray.append(msg.parseOUT());
        }

        return QJsonDocument(msgsAsJsonObjsArray);
    }

    /**
     * \brief reads in a DataStorage from a JSON document
     */
    bool ParseFromJson(const QJsonArray &jsonMsgsArray)
    {
        clear();
        const typename DataContainer::size_type NrOfMessagesInTotal = jsonMsgsArray.size();
        const typename DataContainer::size_type NrMessagesInLastContainer = NrOfMessagesInTotal & ContainerSize;
        const typename DataContainer::size_type ContainersToCreate = NrOfMessagesInTotal / ContainerSize;
        const typename DataContainer::size_type ContainersToCreateAsFiles = ( ContainersToCreate > NrOfContainersToKeepInRAM ) ?
            ContainersToCreate - NrOfContainersToKeepInRAM : 0;

        typename DataContainer::size_type CurContainerNr = 0;

        while(CurContainerNr < ContainersToCreateAsFiles)
        {
            QString fileName = DataStorageTempDir.filePath(QString(FilePrefix).append(QString::number(CurContainerNr)));
            ContainerFileNames.append(fileName);
            QFile fileToCreate(fileName);
            if(!fileToCreate.open(QIODevice::WriteOnly))
            {
                qWarning() << "Error opening file: " << fileToCreate.fileName();
            }

            QJsonArray arrayToParseToFile;
            typename DataContainer::size_type i = CurContainerNr * ContainerSize;
            const typename DataContainer::size_type end = i + ContainerSize;
            while(i < end)
            {
                arrayToParseToFile.append(jsonMsgsArray.at(i));
                i++;
                this->CurrentSize++;
            }

#ifdef PRINT_MSGS_AS_JSON
            fileToCreate.write(QJsonDocument(arrayToParseToFile).toJson());
#else
            fileToCreate.write(QJsonDocument(arrayToParseToFile).toBinaryData());
#endif

            fileToCreate.flush();
            fileToCreate.close();

            CurContainerNr++;
        }

        while( CurContainerNr < ContainersToCreate )
        {
            QString fileName = DataStorageTempDir.filePath(QString(FilePrefix).append(QString::number(CurContainerNr)));
            ContainerFileNames.append(fileName);
            const typename DataContainer::size_type CurIndexInStore = CurContainerNr - ContainersToCreateAsFiles;
            ContainerID CurContainerID(CurContainerNr, CurIndexInStore);
            ContainerInRAMIndexMapping.append(CurContainerID);

            typename DataContainer::size_type i = CurContainerNr * ContainerSize;
            const typename DataContainer::size_type end = i + ContainerSize;
            DataContainer CurContainerInRam;
            while(i < end)
            {
                CurContainerInRam.append(Msg(jsonMsgsArray.at(i).toObject()));
                i++;
                this->CurrentSize++;
            }
            DataStore.append(CurContainerInRam);
            CurContainerNr++;
        }

        typename DataContainer::size_type CurIndex = NrOfMessagesInTotal - NrMessagesInLastContainer;
        while(CurIndex < NrMessagesInLastContainer)
        {
            LastContainer.append(Msg(jsonMsgsArray.at(CurIndex).toObject()));
            CurIndex++;
            this->CurrentSize++;
        }

        return true;
    }

private:
    /**
     * @brief SerializeToFile
     * @param IndexInStore
     *
     * \note This does not invalidate the given index!
     * 
     * wrapper function for SerializeToFile with ContainerNr and ContainerToSerializeTo
     */
    void SerializeToFile(const ContainerID &containerID)
    {
        SerializeToFile(containerID.ContainerNR, DataStore.at(containerID.IndexInStore));
    }

    /**
     * \brief Serializes the contents of a container to a file for later retrieval
     */
    void SerializeToFile(const typename DataContainer::size_type ContainerNr, const DataContainer &ContainerToSerializeTo)
    {
        //    qDebug() << "Serialize to file --- Container nr. " << ContainerNr;
        QJsonArray jsonMsgsArr;
        for(auto &&msg : ContainerToSerializeTo)
        {
            jsonMsgsArr.append(msg.parseOUT());
        }

        QFile MsgDataTempFile(ContainerFileNames[ContainerNr]);

        //    QFile MsgDataTempFile(FileName);
        if(!MsgDataTempFile.open(QIODevice::WriteOnly)) {
            qDebug() << "error open file to save: " << MsgDataTempFile.fileName();
        }
        else
        {
#ifdef PRINT_MSGS_AS_JSON
            MsgDataTempFile.write(QJsonDocument(jsonMsgsArr).toJson());
#else
            MsgDataTempFile.write(QJsonDocument(jsonMsgsArr).toBinaryData());
#endif
        }
        MsgDataTempFile.flush(); //always flush after write!
        MsgDataTempFile.close();
    }

    /**
     * @brief SerializeToFile
     * @param IndexInStore
     *
     * \note The DataContainer at the given index is replaced with the DataContainer that is loaded from the file!
     */
    void SerializeFromFile(const ContainerID &IndexInStoreToInsertIn)
    {
        //    qDebug() << "Serialize from file --- Container nr. " << IndexInStoreToInsertIn.ContainerNR;
        DataContainer NewDataContainer;
        QFile MsgDataTempFile(ContainerFileNames[IndexInStoreToInsertIn.ContainerNR]);
        QJsonArray jsonMsgsArr;

        if(!MsgDataTempFile.exists())
        {
            qDebug() << __PRETTY_FUNCTION__<< __LINE__ <<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
        }

        if(!MsgDataTempFile.open(QIODevice::ReadOnly)) {
            qDebug() << "error opening: " << MsgDataTempFile.fileName();
        }

#ifdef PRINT_MSGS_AS_JSON
        jsonMsgsArr = QJsonDocument::fromJson(MsgDataTempFile.readAll()).array();
#else
        jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();
#endif

        MsgDataTempFile.close();

        NewDataContainer.reserve(ContainerSize);

        for(auto&& item : jsonMsgsArr)
        {
            NewDataContainer.append(std::move(Msg(item.toObject())));
        }


        DataStore[IndexInStoreToInsertIn.IndexInStore] = std::move(NewDataContainer);
    }

    /**
     * \brief Maintenance of containers before appending an element to the #DataStorage
     * 
     * The appendHelper evaluates whether the element to append will exceed the size boundaries of 
     * the current #LastContainer and calculates the index for the element.
     * 
     * If the element does not fit into the current #LastContainer, the current #LastContainer is saved
     * according to the following scheme and a new #LastContainer is created.
     * 
     * If the #CurrentNrOfContainers does not exceed the #NrOfContainersToKeepInRAM, the current #LastContainer
     * is appended to the #DataStore.
     * Else if the current #LastContainer is the next successor to the last container in RAM, the first container
     * in RAM is saved to disk and removed from the #DataStore and the current #LastContainer is append to the 
     * #DataStore.
     * Else if none of the above applies, the current #LastContainer is saved to disk and no further
     * actions are taken.
     */
    void appendHelper()
    {
        typename DataContainer::size_type containerIndex = CurrentSize / ContainerSize;
        ContainerID LastContainerID(containerIndex);

        if( containerIndex > CurrentNrOfContainers )
        {
            containerIndex--;
            LastContainerID.ContainerNR = containerIndex;
            //There is no more space in LastContainer
            //Insert LastContainer to list
            //New LastContainer
            if( CurrentNrOfContainers < NrOfContainersToKeepInRAM )
            {
                LastContainerID.IndexInStore = containerIndex;
                ContainerInRAMIndexMapping.append(LastContainerID);
                DataStore.append(std::move(LastContainer));
                //            qDebug() << __PRETTY_FUNCTION__ << " " << LastContainer.size();
            }
            else if( containerIndex == ( ContainerInRAMIndexMapping.last().ContainerNR + 1 ) )
            {
                //LastContainer is next successor to current last container... append!
                ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.first();
                LastContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

                SerializeToFile(ContainerIDToFlush); // Save old

                DataStore.replace(LastContainerID.IndexInStore, LastContainer);

                ContainerInRAMIndexMapping.append(LastContainerID);
            }
            else
            {
                SerializeToFile(containerIndex, LastContainer); // Save old LastContainer
            }

            ContainerFileNames.append(DataStorageTempDir.filePath(QString(FilePrefix).append(QString::number(containerIndex))));
            LastContainer = std::move(DataContainer()); // Create new LastContainer
            LastContainer.reserve(ContainerSize);
            CurrentNrOfContainers++;
        }

        CurrentSize++;
    }

    /**
     * \brief Load a previously saved container from its file into the #DataStore
     * 
     * the fetchContainerFromFileToRAM method loads a container that was previously saved by
     * writing it to a file back into the #DataStore. The #DataStore is adjusted accordingly.
     * 
     * If the ContainerID of the fetched container is greater than the ContainerID of the current
     * last container in the #DataStore, the first container in the #DataStore is saved to a file
     * and removed from teh #DataStore. The newly fetched container is then appended to the #DataStore.
     * 
     * Else if the ContainerID of the fetched container is lower than the ContainerID of the current
     * first container in the #DataStore, the last container in the #DataStore is saved to a file
     * and removed from the #DataStore. The newly fetched container is then prepended to the #DataStore.
     * 
     * Else if none of the above applies, the ContainerID of the fetched container is compared against
     * all containers' ContainerID in the #DataStore. Starting from the last container, the first ContainerID
     * of a container that is lower than the fetched container's ContainerID determines the container 
     * to save to file and remove from the #DataStore to make space for the fetched container.
     */
    void fetchContainerFromFileToRAM(ContainerID &ContainerIDToFetch)
    {
        if(ContainerIDToFetch > ContainerInRAMIndexMapping.last())
        {
            //ContainerIndex exceeds currently highest loaded container index
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.first();
            ContainerIDToFetch.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(ContainerIDToFetch); // Retrieve new

            ContainerInRAMIndexMapping.append(ContainerIDToFetch);
        }
        else if(ContainerIDToFetch < ContainerInRAMIndexMapping.first())
        {
            //ContainerIndex exceeds currently lowest loaded container index
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.last();
            ContainerIDToFetch.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(ContainerIDToFetch); // Retrieve new

            ContainerInRAMIndexMapping.prepend(ContainerIDToFetch);
        }
        else
        {
            //ContainerIndex is somewhere in the middle
            typename DataContainer::size_type IndexMapBuffSize = ContainerInRAMIndexMapping.size();
            ContainerID ContainerIDToFlush;
            while(IndexMapBuffSize--)
            {
                ContainerIDToFlush = ContainerInRAMIndexMapping.at(IndexMapBuffSize);
                if(ContainerIDToFlush.ContainerNR < ContainerIDToFetch.ContainerNR)
                {
                    break;
                }
            }
            ContainerIDToFetch.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(ContainerIDToFetch); // Retrieve new

            ContainerInRAMIndexMapping.replace(IndexMapBuffSize, ContainerIDToFetch);
        }
    }

    /**
     * \brief Determines wheter the container with the given ContainerID is alread in the #DataStore or needs to be fetched.
     * 
     * \param[inout] ContainerIDToFetch     Must contain the ContainerNR of the container to fetch. Will contain the IndexInStore
     *                                      that the container has in the #DataStore.
     *                                      
     * \pre The given ContainerID must contain a valid ContainerNR
     * \post The given ContainerID contains the IndexInStore of the queried container
     * \post If the container with the given ContainerNR was not already loaded into the #DataStore
     * it is loaded into the #DataStore during this method. All rules of #fetchContainerFromFileToRAM then apply!
     * 
     * If the container with the ContainerNR contained in the given ContainerID is in the #DataStore, the IndexInStore is
     * inserted into the ContainerID.
     * If the container with the ContainerNr contained in the given ContainerID is not the #DataStore, it is fetched
     * from the file it was written to previously with the #fetchContainerFromFileToRAM method.
     */
    void fetchContainerIDHelper(ContainerID &ContainerIDToFetch)
    {
        if(!ContainerInRAMIndexMapping.contains(ContainerIDToFetch))
        {
            fetchContainerFromFileToRAM(ContainerIDToFetch);
        }
        else
        {
            ContainerIDToFetch = ContainerInRAMIndexMapping.at(ContainerInRAMIndexMapping.find(ContainerIDToFetch));
        }
    }

private:
    DataContainerStore DataStore; //!< The storage of the DataContainers
    DataContainer LastContainer; //!< LastContainer is kept in memory permanently because of append method!
    QVector<QString> ContainerFileNames;
    const typename DataContainer::size_type ContainerSize;  //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    const typename DataContainer::size_type NrOfContainersToKeepInRAM; //CONST BECAUSE THIS SHOULD NOT BE CHANGEABLE AT RUNTIME ONCE THE OBJECT WAS CREATED!
    RSimpleDestructiveRingBuff<ContainerID> ContainerInRAMIndexMapping; //!< Ring buffer that stores the mapping of indices that are kept in RAM (DataStore)
    const QString FilePrefix;
    QDir DataStorageTempDir;
    typename DataContainer::size_type CurrentSize;
    typename DataContainer::size_type CurrentNrOfContainers;
    size_t CurrentFileNr;

    static unsigned int DataStorageCntr;
};

template<typename T>
unsigned int  DataStorage<T>::DataStorageCntr = 0;
#endif // DATASTORAGE_H
