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

    MsgStorageTempDir;

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
    int containerIndex = index / ContainerSize;
    int indexInContainer = index % ContainerSize;

    if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
        return Msg();

    if( containerIndex == ( CurrentNrOfContainers ) )
    {
        //ShortCut to LastContainer
        return LastContainer.value(indexInContainer);
    }

    ContainerID fetchedContainerID( containerIndex );

    if(!ContainerInRAMIndexMapping.contains(fetchedContainerID))
    {
        if(containerIndex > ContainerInRAMIndexMapping.last().ContainerNR)
        {
            //ContainerIndex exceeds currently highest loaded container index
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.first();
            fetchedContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(fetchedContainerID); // Retrieve new

            ContainerInRAMIndexMapping.append(fetchedContainerID);
        }
        else if(containerIndex < ContainerInRAMIndexMapping.first().ContainerNR)
        {
            //ContainerIndex exceeds currently lowest loaded container index
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.last();
            fetchedContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(fetchedContainerID); // Retrieve new

            ContainerInRAMIndexMapping.prepend(fetchedContainerID);
        }
        else
        {
            //ContainerIndex is somewhere in the middle
            int IndexMapBuffSize = ContainerInRAMIndexMapping.size();
            ContainerID ContainerIDToFlush;
            while(IndexMapBuffSize--)
            {
                ContainerIDToFlush = ContainerInRAMIndexMapping.at(IndexMapBuffSize);
                if(ContainerIDToFlush.ContainerNR < fetchedContainerID.ContainerNR)
                {
                    break;
                }
            }
            fetchedContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush); // Save old
            SerializeFromFile(fetchedContainerID); // Retrieve new

            ContainerInRAMIndexMapping.replace(IndexMapBuffSize, fetchedContainerID);
        }
    }
    else
    {
        fetchedContainerID = ContainerInRAMIndexMapping.find(fetchedContainerID);
    }

    const MsgContainer &RelatedContainer = MsgStore.at(fetchedContainerID.IndexInStore);

    return RelatedContainer.at(indexInContainer);
}

void MsgStorage::append(const Msg &value)
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

        ContainerFileNames.append(QString(FilePrefix).append(QString::number(containerIndex)));
        LastContainer = MsgContainer(); // Create new LastContainer
        LastContainer.reserve(ContainerSize);
        CurrentNrOfContainers++;
    }

    LastContainer.append(value);
    CurrentSize++;
}

int MsgStorage::size() const
{
    return CurrentSize;
}

bool MsgStorage::isEmpty() const
{
    return static_cast<bool>(CurrentSize);
}

int MsgStorage::MemUsage() const
{
    int FullMemUsage = 0;
    FullMemUsage += MsgStore.capacity() * sizeof(MsgContainer);
    for(const MsgContainer &msgContainer : MsgStore)
        FullMemUsage += msgContainer.capacity() * sizeof(Msg);
    FullMemUsage += LastContainer.capacity() * sizeof(Msg);
    FullMemUsage += ContainerFileNames.capacity() * sizeof(QString);
    FullMemUsage += ContainerInRAMIndexMapping.capacity() * sizeof(ContainerID);

    return FullMemUsage;
}

void MsgStorage::SerializeToFile(const ContainerID &containerID)
{
    SerializeToFile(containerID.ContainerNR, MsgStore.at(containerID.IndexInStore));
}

void MsgStorage::SerializeToFile(const int ContainerNr, const MsgStorage::MsgContainer &ContainerToSerialize)
{
//    qDebug() << "Serialize to file --- Container nr. " << ContainerNr;
    QJsonArray jsonMsgsArr;
    for(auto &&msg : ContainerToSerialize)
    {
        jsonMsgsArr.append(msg.parseOUT());
    }

    QFile MsgDataTempFile(MsgStorageTempDir.filePath(QString(FilePrefix).append(QString::number(ContainerNr))));

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
    QFile MsgDataTempFile(MsgStorageTempDir.filePath(ContainerFileNames.at(IndexInStoreToInsertIn.ContainerNR)));
    QJsonArray jsonMsgsArr;

    if(!MsgDataTempFile.exists())
    {
        qDebug() << __PRETTY_FUNCTION__<<": ERROR - File does not exist! Name: " << MsgDataTempFile.fileName();
    }

    MsgDataTempFile.open(QIODevice::ReadOnly);

    jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll()).array();

    NewMsgContainer.reserve(ContainerSize);

    for(auto&& item : jsonMsgsArr)
    {
        NewMsgContainer.append(Msg(item.toObject()));
    }

    MsgDataTempFile.close();

    MsgStore.replace(IndexInStoreToInsertIn.IndexInStore, NewMsgContainer);
}
