#include "msgstorage.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>



#include <QDebug>

int MsgStorage::MsgStorageCntr = 0;

MsgStorage::MsgStorage(const int ContainerSize, const int NrOfContainersToKeepInRAM) :
    ContainerSize(!ContainerSize ? 1 : ContainerSize),
    NrOfContainersToKeepInRAM(!NrOfContainersToKeepInRAM ? 1 : NrOfContainersToKeepInRAM),
    ContainerInRAMIndexMapping(this->NrOfContainersToKeepInRAM),
    FilePrefix(QString("./RMsgStTmp/RMsgStore_%1_").arg(MsgStorageCntr++)),
    CurrentSize(0),
    CurrentNrOfContainers(0),
    CurrentFileNr(0)
{
    //MsgContainerStore is reserved upfront to get rid of fragmentation and unneccessary alocations
    MsgStore.reserve(NrOfContainersToKeepInRAM);
//    MsgStore.append(MsgContainer());
//    MsgStore.append(MsgContainer());
//    MsgStore.append(MsgContainer());
//    for(auto &Container : MsgStore)
//    {
//        //the contained MsgContainers are also reserved upfront to get rid of fragmentation and unneccessary alocations
//        Container.reserve(ContainerSize);
//    }

//    ContainerInRAMIndexMapping.append(ContainerID(0,0));
//    ContainerInRAMIndexMapping.append(ContainerID(1,1));
//    ContainerInRAMIndexMapping.append(ContainerID(2,2));

    LastContainer.reserve(ContainerSize);
}

Msg MsgStorage::at(const int index)
{
    int containerIndex = index / ContainerSize;
    int indexInContainer = index % ContainerSize;

    if( ( index > CurrentSize ) || ( containerIndex > CurrentNrOfContainers ) )
        return Msg();

    if( containerIndex == ( CurrentNrOfContainers-1 ) )
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

            SerializeToFile(ContainerIDToFlush.IndexInStore); // Save old
            SerializeFromFile(fetchedContainerID.IndexInStore); // Retrieve new

            ContainerInRAMIndexMapping.append(fetchedContainerID);
        }
        else if(containerIndex < ContainerInRAMIndexMapping.first().ContainerNR)
        {
            //ContainerIndex exceeds currently lowest loaded container index
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.last();
            fetchedContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush.IndexInStore); // Save old
            SerializeFromFile(fetchedContainerID.IndexInStore); // Retrieve new

            ContainerInRAMIndexMapping.prepend(fetchedContainerID);
        }
        else
        {
            //ContainerIndex is somewhere in the middle
        }
    }

    const MsgContainer &RelatedContainer = MsgStore.at(fetchedContainerID.IndexInStore);

    return RelatedContainer.value(indexInContainer);
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
            qDebug() << __PRETTY_FUNCTION__ << " " << LastContainer.size();
        }
        else if( containerIndex == ( ContainerInRAMIndexMapping.last().ContainerNR + 1 ) )
        {
            //LastContainer is next successor to current last container... append!
            ContainerID ContainerIDToFlush = ContainerInRAMIndexMapping.first();
            LastContainerID.IndexInStore = ContainerIDToFlush.IndexInStore;

            SerializeToFile(ContainerIDToFlush.IndexInStore); // Save old

            MsgStore.replace(LastContainerID.IndexInStore, LastContainer);

            ContainerInRAMIndexMapping.append(LastContainerID);
        }
        else
        {
            SerializeToFile(containerIndex, LastContainer); // Save old LastContainer
        }

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

void MsgStorage::SerializeToFile(const ContainerID &containerID) const
{
    SerializeToFile(containerID.ContainerNR, MsgStore.at(containerID.IndexInStore));
}

void MsgStorage::SerializeToFile(const int ContainerNr, const MsgStorage::MsgContainer &ContainerToSerialize) const
{
    qDebug() << "Serialize to file --- Container nr. " << ContainerNr;
    QJsonArray jsonMsgsArr;
    for(auto &&msg : ContainerToSerialize)
    {
        jsonMsgsArr.append(msg.parseOUT());
    }

    QString FileName(QString(FilePrefix).append(QString::number(ContainerNr)));

    QFile MsgDataTempFile(FileName);
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
    qDebug() << "Serialize from file --- Container nr. " << IndexInStoreToInsertIn.ContainerNR;
    MsgContainer NewMsgContainer;
    QString FileName(ContainerFileNames.at(IndexInStoreToInsertIn.ContainerNR));
    QFile MsgDataTempFile(FileName);
    QJsonArray jsonMsgsArr;

    MsgDataTempFile.open(QIODevice::ReadOnly | QIODevice::Text);

    jsonMsgsArr = QJsonDocument::fromBinaryData(MsgDataTempFile.readAll()).array();

    for(auto&& item : jsonMsgsArr)
    {
        NewMsgContainer.append(Msg(item.toObject()));
    }

    MsgDataTempFile.close();

    MsgStore.replace(IndexInStoreToInsertIn.IndexInStore, NewMsgContainer);
}

MsgStorage::MsgContainer &MsgStorage::appendNewContainer()
{
    CurrentNrOfContainers++;
}
