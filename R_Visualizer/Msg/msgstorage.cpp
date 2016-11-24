#include "msgstorage.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>



#include <QDebug>

int MsgStorage::MsgStorageCntr = 0;

MsgStorage::MsgStorage(const int ContainerSize, const int NrOfContainersToKeepInRAM) :
    ContainerSize((!ContainerSize) ? 1 : ContainerSize),
    NrOfContainersToKeepInRAM((!NrOfContainersToKeepInRAM) ? 1 : NrOfContainersToKeepInRAM),
    ContainerInRAMIndexMapping(NrOfContainersToKeepInRAM),
    FilePrefix(QString("RMsgStore_%1_").arg(MsgStorageCntr++)),
    CurrentSize(0),
    CurrentNrOfContainers(0),
    CurrentFileNr(0)
{
    QString MsgStoreTempDirName(QString("RMsgStoreTmp_%1").arg(MsgStorageCntr));

    if(!MsgStorageTempDir.exists(MsgStoreTempDirName))
    {
        MsgStorageTempDir.mkdir(MsgStoreTempDirName);
    }

    MsgStorageTempDir.setPath(MsgStoreTempDirName);
    //    qDebug() << MsgStorageTempDir.path();

    //MsgContainerStore is reserved upfront to get rid of fragmentation and unneccessary alocations
    MsgStore.reserve(NrOfContainersToKeepInRAM);
    LastContainer.reserve(ContainerSize);
}

Msg MsgStorage::at(const int index)
{
    const int containerIndex = index / ContainerSize;
    const int indexInContainer = index % ContainerSize;

    if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
        return Msg();

    if( containerIndex == ( CurrentNrOfContainers ) )
    {
        //ShortCut to LastContainer
        return LastContainer.value(indexInContainer);
    }

    ContainerID fetchedContainerID( containerIndex );
    fetchContainerIDHelper(fetchedContainerID);

    if(fetchedContainerID.IndexInStore == -1)
        return Msg();

    const MsgContainer &RelatedContainer = MsgStore.at(fetchedContainerID.IndexInStore);

    return RelatedContainer.at(indexInContainer);
}

void MsgStorage::append(Msg &&value)
{
    appendHelper();
    LastContainer.append(std::move(value));
}

void MsgStorage::append(const Msg &value)
{
    appendHelper();
    LastContainer.append(value);
}

void MsgStorage::replace(const int index, const Msg &value)
{
    const int containerIndex = index / ContainerSize;
    const int indexInContainer = index % ContainerSize;

    if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
        return;

    if( containerIndex == CurrentNrOfContainers )
    {
        //ShortCut to LastContainer
        LastContainer.replace(indexInContainer, value);
    }

    ContainerID fetchedContainerID( containerIndex );
    fetchContainerIDHelper(fetchedContainerID);

    if(fetchedContainerID.IndexInStore == -1)
        return;

    MsgStore[fetchedContainerID.IndexInStore].replace(indexInContainer, value);
}

void MsgStorage::remove(const int index)
{
    int containerIndex = index / ContainerSize;
    int indexInContainer = index % ContainerSize;

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
        MsgContainer curContainer;
        MsgContainer recentContainer;
        QJsonArray curJsonMsgsArr;
        QJsonArray recentJsonMsgsArr;
        Msg curMsg;
        int recentContainerNR;
        bool recentContainerWasLoaded = false;

        //Handle container that contains the element to remove
        if(ContainerInRAMIndexMapping.contains(ContainerIDToRemoveValueFrom))
        {
            //Is in RAM
            ContainerIDToRemoveValueFrom = ContainerInRAMIndexMapping.find(ContainerIDToRemoveValueFrom);
            try {
                curContainer = MsgStore.at(ContainerIDToRemoveValueFrom.IndexInStore);
            } catch (const std::exception& e) {
                qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
            }
            try {
                curContainer.remove(indexInContainer);
            } catch (const std::exception& e) {
                qDebug() << __LINE__ << " a standard exception was caught, with message '"<< e.what();
            }
            recentContainer = curContainer;
            recentContainerWasLoaded = false;
        }
        else
        {
            //Needs to be loaded...
            //            QFile MsgDataTempFile(ContainerFileNames[containerIndex]);
            QString fileLoc;
            try {
                fileLoc = ContainerFileNames[containerIndex];
            } catch (const std::exception& e) {
                qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
            }
            //        QJsonArray jsonMsgsArr;
            QFile MsgDataTempFile(fileLoc);
            if(!MsgDataTempFile.exists())
            {
                qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
            }

            MsgDataTempFile.open(QIODevice::ReadOnly);

            curJsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();
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
                ContainerIDToRemoveValueFrom = ContainerInRAMIndexMapping.find(ContainerIDToRemoveValueFrom);

                try {
                    curContainer = MsgStore.at(ContainerIDToRemoveValueFrom.IndexInStore);
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                curMsg = curContainer.first();
                curContainer.removeFirst();
                if(curContainer.isEmpty())
                {
                    int tempContainerIndex = containerIndex;
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
                QString fileLoc;
                try {
                    fileLoc = ContainerFileNames[containerIndex];
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                QFile MsgDataTempFile(fileLoc);
                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                }

                MsgDataTempFile.open(QIODevice::ReadOnly);

                curJsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();
                MsgDataTempFile.close();
                curMsg = Msg(curJsonMsgsArr.first().toObject());
                curJsonMsgsArr.removeFirst();
                //            curContainer = MsgContainer();
            }

            if(recentContainerWasLoaded)
            {
                //Handle if the previous container was loaded
                recentJsonMsgsArr.append(curMsg.parseOUT());
                QString fileLoc;
                try {
                    fileLoc = ContainerFileNames[containerIndex];
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                QFile MsgDataTempFile(fileLoc);
                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                }

                MsgDataTempFile.open(QIODevice::WriteOnly);
                MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toBinaryData());
                MsgDataTempFile.flush();
                MsgDataTempFile.close();
            }
            else
            {
                //Handle if the previous container was in RAM
                try {
                    recentContainer.append(curMsg);
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
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
            recentContainer = curContainer;
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

            QString fileLoc;
            try {
                fileLoc = ContainerFileNames[containerIndex];
            } catch (const std::exception& e) {
                qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
            }
            QFile MsgDataTempFile(fileLoc);
            if(!MsgDataTempFile.exists())
            {
                qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
            }

            MsgDataTempFile.open(QIODevice::WriteOnly);
            MsgDataTempFile.write(QJsonDocument(recentJsonMsgsArr).toBinaryData());
            MsgDataTempFile.flush();
            MsgDataTempFile.close();
        }
        else
        {
            try {
                recentContainer.append(curMsg);
            } catch (const std::exception& e) {
                qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
            }
        }
        CurrentSize--;
    }

    //Handle if LastContainer is empty and needs to be adjusted
    if( LastContainer.isEmpty() && ( CurrentSize != 0 ) )
    {
        if( CurrentNrOfContainers > 1 )
        {
            //Get ContainerID of preceding container to LastContainer
            ContainerID ContainerIDNextLastContainer(CurrentNrOfContainers-1);

            if(ContainerInRAMIndexMapping.contains(ContainerIDNextLastContainer))
            {
                //Is in RAM
                ContainerIDNextLastContainer = ContainerInRAMIndexMapping.find(ContainerIDNextLastContainer);
                try {
                    LastContainer = MsgStore.at(ContainerIDNextLastContainer.IndexInStore);
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                ContainerID ContainerIDNextToLoad(ContainerIDNextLastContainer.ContainerNR-1);
                //Find nextlower container to load into ram...
                while(ContainerInRAMIndexMapping.contains(ContainerIDNextToLoad))
                {
                    ContainerIDNextToLoad = ContainerID(ContainerIDNextToLoad.ContainerNR-1);
                }
                try {
                    fetchContainerFromFile(ContainerIDNextToLoad);
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
            }
            else
            {
                //Needs to be loaded...
                QString fileLoc;
                try {
                    fileLoc = ContainerFileNames[containerIndex-1];
                } catch (const std::exception& e) {
                    qDebug() << __LINE__ << " a standard exception was caught, with message '" << e.what();
                }
                QFile MsgDataTempFile(fileLoc);
                QJsonArray jsonMsgsArr;

                if(!MsgDataTempFile.exists())
                {
                    qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
                }

                MsgDataTempFile.open(QIODevice::ReadOnly);

                jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();

                MsgDataTempFile.close();

                for(auto&& item : jsonMsgsArr)
                {
                    LastContainer.append(std::move(Msg(item.toObject())));
                }
            }
        }
        CurrentNrOfContainers--;
    }
}


void MsgStorage::clear()
{
    MsgStore.clear();
    LastContainer.clear();
    ContainerFileNames.clear();
    ContainerInRAMIndexMapping.clear();
    CurrentSize = 0;
    CurrentNrOfContainers = 0;
    CurrentFileNr = 0;

    MsgStorageTempDir.removeRecursively();

    MsgStorageCntr++;
    QString MsgStoreTempDirName(std::move(QString("RMsgStoreTmp_%1").arg(MsgStorageCntr)));

    if(!MsgStorageTempDir.exists(MsgStoreTempDirName))
    {
        MsgStorageTempDir.mkdir(MsgStoreTempDirName);
    }

    MsgStorageTempDir.setPath(MsgStoreTempDirName);
    //    qDebug() << MsgStorageTempDir.path();

    //MsgContainerStore is reserved upfront to get rid of fragmentation and unneccessary alocations
    MsgStore.reserve(NrOfContainersToKeepInRAM);
    LastContainer.reserve(ContainerSize);
}

int MsgStorage::size() const
{
    return CurrentSize;
}

bool MsgStorage::isEmpty() const
{
    return CurrentSize == 0;
}

int MsgStorage::MemUsage() const
{
    int FullMemUsage = 0;
    FullMemUsage += MsgStore.capacity() * sizeof(MsgContainer);
    for(const MsgContainer &msgContainer : MsgStore)
        FullMemUsage += msgContainer.capacity() * sizeof(Msg);
    FullMemUsage += LastContainer.capacity() * sizeof(Msg);
    FullMemUsage += ContainerFileNames.capacity() * sizeof(QFile);
    FullMemUsage += ContainerInRAMIndexMapping.capacity() * sizeof(ContainerID);

    return FullMemUsage;
}

void MsgStorage::SerializeToFile(const ContainerID &containerID)
{
    SerializeToFile(containerID.ContainerNR, MsgStore.at(containerID.IndexInStore));
}

void MsgStorage::SerializeToFile(const int ContainerNr, const MsgStorage::MsgContainer &ContainerToSerializeTo)
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
        MsgDataTempFile.write(QJsonDocument(jsonMsgsArr).toBinaryData());
    }
    MsgDataTempFile.flush(); //always flush after write!
    MsgDataTempFile.close();
}

void MsgStorage::SerializeFromFile(const ContainerID &IndexInStoreToInsertIn)
{
    //    qDebug() << "Serialize from file --- Container nr. " << IndexInStoreToInsertIn.ContainerNR;
    MsgContainer NewMsgContainer;
    QFile MsgDataTempFile(ContainerFileNames[IndexInStoreToInsertIn.ContainerNR]);
    QJsonArray jsonMsgsArr;

    if(!MsgDataTempFile.exists())
    {
        qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
    }

    MsgDataTempFile.open(QIODevice::ReadOnly);

    jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll(),QJsonDocument::BypassValidation).array();

    MsgDataTempFile.close();

    NewMsgContainer.reserve(ContainerSize);

    for(auto&& item : jsonMsgsArr)
    {
        NewMsgContainer.append(std::move(Msg(item.toObject())));
    }


    MsgStore[IndexInStoreToInsertIn.IndexInStore] = std::move(NewMsgContainer);
}

void MsgStorage::appendHelper()
{
    int containerIndex = CurrentSize / ContainerSize;
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
            MsgStore.append(std::move(LastContainer));
            //            qDebug() << __PRETTY_FUNCTION__ << " " << LastContainer.size();
        }
        else if( containerIndex == ( ContainerInRAMIndexMapping.last().ContainerNR + 1 ) )
        {
            //LastContainer is next successor to current last container... append!
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.first();
            LastContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old

            MsgStore.replace(LastContainerID.IndexInStore, LastContainer);

            ContainerInRAMIndexMapping.append(LastContainerID);
        }
        else
        {
            SerializeToFile(containerIndex, LastContainer); // Save old LastContainer
        }

        ContainerFileNames.append(MsgStorageTempDir.filePath(QString(FilePrefix).append(QString::number(containerIndex))));
        LastContainer = std::move(MsgContainer()); // Create new LastContainer
        LastContainer.reserve(ContainerSize);
        CurrentNrOfContainers++;
    }

    CurrentSize++;
}

void MsgStorage::fetchContainerFromFile(ContainerID &ContainerIDToFetch)
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
        int IndexMapBuffSize = ContainerInRAMIndexMapping.size();
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

void MsgStorage::fetchContainerIDHelper(ContainerID &ContainerIDToFetch)
{
    if(!ContainerInRAMIndexMapping.contains(ContainerIDToFetch))
    {
        fetchContainerFromFile(ContainerIDToFetch);
    }
    else
    {
        ContainerIDToFetch = ContainerInRAMIndexMapping.find(ContainerIDToFetch);
    }
}
