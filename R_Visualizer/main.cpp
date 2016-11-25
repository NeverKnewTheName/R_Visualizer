#include "mainwindow.h"
#include <QApplication>

#include "can_packet.h"
#include "msg.h"
#include "errorlogentry.h"

// // // DEBUG // // //
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>
#include "msgparser.h"
#include "msgdatawidget.h"
#include "msgstorage.h"
#include <QJsonDocument>
#include <QJsonArray>
// // // DEBUG // // //

int MsgStorageTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM);
void MsgStorageRemoveTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM);
void MsgStorageReplaceTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM);
void MsgStorageStoreLoadTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM);

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);

    //    qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr");
    //    qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr");
    //    qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr");
    //    qRegisterMetaType <Msg>("Msg");
    //    qRegisterMetaType <MsgDataStruc>("MsgDataStruc");
    //    qRegisterMetaType <DataByteVect>("DataByteVect");
    //    qRegisterMetaType <ErrorLogEntry>("ErrorLogEntry");

    QElapsedTimer myTimer;
    const int NrMsgsToTest = 10000000;
    myTimer.start();
    MsgStorageStoreLoadTest(NrMsgsToTest,1000,3);
//    MsgStorageTest(NrMsgsToTest, 1000, 3);
//    MsgStorageRemoveTest(NrMsgsToTest, 10, 3);
//    MsgStorageReplaceTest(NrMsgsToTest, 10, 3);

    QFile isDone("DONE.NOTICE");

    isDone.open(QIODevice::WriteOnly);

    isDone.write(QString("Took: %1ms in total...").arg(myTimer.elapsed()).toLatin1());

    isDone.flush();
    isDone.close();

    return 0;

    //    MainWindow w;
    //    w.show();

    //    return a.exec();
}

void MsgStorageReplaceTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM)
{

    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    QElapsedTimer myTimer;
    quint64 elapsedTime;
    quint64 elapsedTotal = 0;

    int min = 100000;
    int max = 0;

    MsgStorage msgStore(ContainerSize, NrElemRAM);

    QFile log("MsgStorageReplaceTestLog.log");


    if(!log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error open file to save: " << log.fileName();
    }
    else
    {
        qDebug() << "File Opened";
    }

    QTextStream logString(&log);
    logString << "START time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString << "\n\nNrOfMessages: " << NrOfMessages;
    logString << "\n\nContainerSize: " << ContainerSize << " NrElementsToKeepInRAM: " << NrElemRAM;
    logString << "\n\n";

    logString.flush();
    log.flush();

    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nAppending " << NrOfMessages << " Messages";
    for(int i = 0; i < NrOfMessages; i++)
    {
        myTimer.restart();
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tMsgStorage appending "<< i <<" Time(ms): " << elapsedTime;
    }
    logString << "\nMsgStorage append total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/NrOfMessages << "ms";
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    int MsgStoreSize = msgStore.size();
    const int itemsToReplace = MsgStoreSize/100;
    int iter = itemsToReplace;
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nReplacing " << itemsToReplace << " Messages";
    while(iter--)
    {
        int randomIndex = qrand()%(MsgStoreSize);
        int randomInput = qrand()%(5000);
        Msg randomMsg(QDateTime::currentDateTime(),randomInput,randomInput,DataByteVect());

        logString << "\n\nReplacing index: " << randomIndex;
        logString << "\n\tCurrent value: " << msgStore.at(randomIndex).getId();
        logString << "\n\tReplacement: " << randomMsg.getId();
        myTimer.restart();
        msgStore.replace(randomIndex, randomMsg);
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tTime taken: " << (double)elapsedTime << " ---Total: " << (double)elapsedTotal;
        logString << "\n\tValue: " << msgStore.at(randomIndex).getId();
        logString.flush();
    }
    logString << "\nMsgStorage Replacing total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/itemsToReplace << "ms";
    logString << "\nMsgStorage Replacing min: " << min << " - max: " << max;
    logString << "\n\nEND time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));

    logString.flush();
    log.flush();
}

void MsgStorageRemoveTest( const int NrOfMessages, const int ContainerSize, const int NrElemRAM)
{
    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    QElapsedTimer myTimer;
    quint64 elapsedTime;
    quint64 elapsedTotal = 0;

    int min = 100000;
    int max = 0;

    MsgStorage msgStore(ContainerSize, NrElemRAM);

    QFile log("MsgStorageDeleteTestLog.log");


    if(!log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error open file to save: " << log.fileName();
    }
    else
    {
        qDebug() << "File Opened";
    }

    QTextStream logString(&log);
    logString << "START time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString << "\n\nNrOfMessages: " << NrOfMessages;
    logString << "\n\nContainerSize: " << ContainerSize << " NrElementsToKeepInRAM: " << NrElemRAM;
    logString << "\n\n";

    logString.flush();
    log.flush();

    logString << "\n\nAppending " << NrOfMessages << " Messages";
    for(int i = 0; i < NrOfMessages; i++)
    {
        myTimer.restart();
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tMsgStorage appending "<< i <<" Time(ms): " << elapsedTime;
    }
    logString << "\nMsgStorage append total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/NrOfMessages << "ms";
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    int IndexToRemove = msgStore.size()-1;
    logString << "\nDelete last element";
    myTimer.restart();
    msgStore.remove(IndexToRemove);
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage remove "<< IndexToRemove <<" nTh Element -> Time(ms): " << elapsedTime;

    logString << "\nDelete first element";
    myTimer.restart();
    msgStore.remove(0);
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage remove "<< 0 <<" nTh Element -> Time(ms): " << elapsedTime;

    logString.flush();
    log.flush();

    int MsgStoreSize = msgStore.size();
    const int NrElemetnsToRemove = MsgStoreSize/100;
    int removeIter = NrElemetnsToRemove;
    logString << "\nRemoving: " << NrElemetnsToRemove << " Elements";
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    while(removeIter--)
    {
#define RANDOM_DELETE
#ifdef RANDOM_DELETE
        IndexToRemove = qrand()%(MsgStoreSize);
#else
        IndexToRemove = MsgStoreSize-1;
#endif
        int MsgIDToRemove = msgStore.at(IndexToRemove).getId();
        logString << "\n\tDelete random element: " << IndexToRemove << " with its current value: " << MsgIDToRemove;

        myTimer.restart();
        msgStore.remove(IndexToRemove);
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tMsgStorage removed " << IndexToRemove << " nTh Element -> Time(ms): " << elapsedTime;

        MsgIDToRemove = msgStore.at(IndexToRemove).getId();
        logString << "\n\t\tElement at index: " << IndexToRemove << " is now: " << MsgIDToRemove;

        MsgStoreSize = msgStore.size();
#ifdef PRINT_MSGSTORE_PER_ITERATION
        int sizeOfMsgStore = MsgStoreSize;
        logString << "\n\nMsgStore with size: " << sizeOfMsgStore;
        while(sizeOfMsgStore--)
        {
            int Index = sizeOfMsgStore;
            Msg msg(msgStore.at(Index));
            logString << "\n\t\tIndex: " << Index << " retrieved: " << msg.getId();
        }
#endif
        logString << "\n\tMsgStorage size: " << MsgStoreSize;
#ifdef PRINT_MSGSTORE_PER_ITERATION
        logString.flush();
        log.flush();
#endif
    }
    logString << "\n\tMsgStorage Remove total: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/NrElemetnsToRemove;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nAppending " << NrOfMessages << " Messages";
    for(int i = 0; i < NrOfMessages; i++)
    {
        myTimer.restart();
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tMsgStorage appending "<< i <<" Time(ms): " << elapsedTime;
    }
    logString << "\nMsgStorage append total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/NrOfMessages << "ms";
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    removeIter = NrElemetnsToRemove;
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nDeleting " << NrElemetnsToRemove << " Messages RANDOMLY without shrinking";
    while(removeIter--)
    {
        IndexToRemove = qrand()%(MsgStoreSize);
        int MsgIDToRemove = msgStore.at(IndexToRemove).getId();
        logString << "\n\tDelete random element: " << IndexToRemove << " with its current value: " << MsgIDToRemove;

        myTimer.restart();
        msgStore.remove(IndexToRemove);
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tMsgStorage removed " << IndexToRemove << " nTh Element -> Time(ms): " << elapsedTime;

        MsgIDToRemove = msgStore.at(IndexToRemove).getId();
        logString << "\n\t\tElement at index: " << IndexToRemove << " is now: " << MsgIDToRemove;
        msgStore.append(Msg(QDateTime::currentDateTime(), qrand()%(5000),5,DataByteVect()));
        MsgStoreSize = msgStore.size();
    }
    logString << "\nTOTAL time for removing without shrinking the MsgStorage: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/NrElemetnsToRemove;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();


    logString << "\n\nEND time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString.flush();
    log.flush();
    log.close();
}


int MsgStorageTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM)
{
    QElapsedTimer myTimer;
    quint64 elapsedTime;
    quint64 elapsedTotal = 0;

    int min = 100000;
    int max = 0;

    QFile log("MsgStorageTestLog.log");
    MsgStorage msgStore(ContainerSize, NrElemRAM);

    if(!log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error open file to save: " << log.fileName();
    }
    else
    {
        qDebug() << "File Opened";
    }

    QTextStream logString(&log);
    logString << "START time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString << "\n\nNrOfMessages: " << NrOfMessages;
    logString << "\n\nContainerSize: " << ContainerSize << " NrElementsToKeepInRAM: " << NrElemRAM;
    logString << "\n\n";

    logString.flush();
    log.flush();

    logString << "\n\nAppending " << NrOfMessages << " Messages";
    for(int i = 0; i < NrOfMessages; i++)
    {
        myTimer.restart();
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tMsgStorage appending "<< i <<" Time(ms): " << elapsedTime;
    }
    logString << "\nMsgStorage append total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/NrOfMessages << "ms";
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    logString << "\nMemUsage (msgStore): " << msgStore.MemUsage();

    const int sizeOfMsgStore = msgStore.size();
    logString << "\nMsgStoreSize: " << sizeOfMsgStore;

    logString.flush();
    log.flush();

    const int ElementsToRetrieve = sizeOfMsgStore/100;
    int retrieveIter = ElementsToRetrieve;
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nRetrieving " << ElementsToRetrieve << " Messages from the BACK";
    while(retrieveIter--)
    {
        int curIndex = sizeOfMsgStore - retrieveIter;
        logString << "\n\tCurrent index: " << curIndex;
        myTimer.restart();
        Msg msg(msgStore.at(curIndex));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tValue: " << msg.getId() << " time taken: " << elapsedTime;
    }
    logString << "\n\tMsgStorage retrieve BACKWARD total: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/ElementsToRetrieve;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nRetrieving " << ElementsToRetrieve << " Messages from the FRONT";
    for(int i = 0; i < ElementsToRetrieve; i++)
    {
        logString << "\n\tCurrent index: " << i;
        myTimer.restart();
        Msg msg(msgStore.at(i));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tValue: " << msg.getId() << " time taken: " << elapsedTime;
    }
    logString << "\n\tMsgStorage retrieve FORWARD total: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/ElementsToRetrieve;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    retrieveIter = ElementsToRetrieve;
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nRetrieving " << ElementsToRetrieve << " Messages RANDOMLY";
    while(retrieveIter--)
    {
        int RandomIndex = qrand()%NrOfMessages;
        logString << "\n\tCurrent index: " << RandomIndex;
        myTimer.restart();
        Msg msg(msgStore.at(RandomIndex));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tValue: " << msg.getId() << " time taken: " << elapsedTime;
    }
    logString << "\n\tMsgStorage retrieve RANDOMLY total: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/ElementsToRetrieve;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    logString << "\n\nEND time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString.flush();
    log.flush();
    log.close();

    return 0;
}

void MsgStorageStoreLoadTest(const int NrOfMessages, const int ContainerSize, const int NrElemRAM)
{
    QElapsedTimer myTimer;
    quint64 elapsedTime;
    quint64 elapsedTotal = 0;

    int min = 100000;
    int max = 0;

    QFile log("MsgStorageStoreLoadTestLog.log");
    MsgStorage msgStore(ContainerSize, NrElemRAM);

    if(!log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error open file to save: " << log.fileName();
    }
    else
    {
        qDebug() << "File Opened";
    }

    QTextStream logString(&log);
    logString << "START time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString << "\n\nNrOfMessages: " << NrOfMessages;
    logString << "\n\nContainerSize: " << ContainerSize << " NrElementsToKeepInRAM: " << NrElemRAM;
    logString << "\n\n";

    logString.flush();
    log.flush();

    logString << "\n\nAppending " << NrOfMessages << " Messages";
    for(int i = 0; i < NrOfMessages; i++)
    {
        myTimer.restart();
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\tMsgStorage appending "<< i <<" Time(ms): " << elapsedTime;
    }
    logString << "\nMsgStorage append total: " << elapsedTotal << " - Time/Msg: " << (double)elapsedTotal/NrOfMessages << "ms";
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();

    logString << "\nMemUsage (msgStore): " << msgStore.MemUsage();

    const int sizeOfMsgStore = msgStore.size();
    logString << "\nMsgStoreSize: " << sizeOfMsgStore;

    logString.flush();
    log.flush();

    QFile MsgStoreSave(QString("MsgStoreSaveFile"));
    if(!MsgStoreSave.open(QIODevice::ReadWrite))
    {
        qWarning() << "Failed to open file: " << MsgStoreSave.fileName();
    }
    else
    {
        qDebug() << "Opened file to save msgStore to: " << MsgStoreSave.fileName();
    }

    QJsonDocument docToSave;
    logString << "\nSaving MsgStore to file";
    myTimer.restart();
    docToSave = msgStore.parseToJson();
    elapsedTime = myTimer.elapsed();

    logString << "\n\tMsgStorage save total: " << elapsedTime;
    logString << "\n\tTime/Message: " << (double)elapsedTime/NrOfMessages;
    logString.flush();
    log.flush();

    MsgStoreSave.write(docToSave.toJson());
    MsgStoreSave.flush();
    MsgStoreSave.close();

    logString << "\nSaving MsgStore to file";
    myTimer.restart();
    msgStore.parseFromJson(docToSave.array());
    elapsedTime = myTimer.elapsed();

    logString << "\n\tMsgStorage load total: " << elapsedTime;
    logString << "\n\tTime/Message: " << (double)elapsedTime/NrOfMessages;
    logString.flush();
    log.flush();

    const int ElementsToRetrieve = sizeOfMsgStore;
    int retrieveIter = ElementsToRetrieve;
    elapsedTotal = 0;
    min = 1000000;
    max = 0;
    logString << "\n\nRetrieving " << ElementsToRetrieve << " Messages from the BACK";
    while(retrieveIter--)
    {
        int curIndex = sizeOfMsgStore - retrieveIter;
        logString << "\n\tCurrent index: " << curIndex;
        myTimer.restart();
        Msg msg(msgStore.at(curIndex));
        elapsedTime = myTimer.elapsed();
        elapsedTotal += elapsedTime;
        min = (min < elapsedTime) ? min : elapsedTime;
        max = (max > elapsedTime) ? max : elapsedTime;
        logString << "\n\t\tValue: " << msg.getId() << " time taken: " << elapsedTime;
    }
    logString << "\n\tMsgStorage retrieve BACKWARD total: " << elapsedTotal;
    logString << "\n\tTime/Message: " << (double)elapsedTotal/ElementsToRetrieve;
    logString << "\nMsgStorage append min: " << min << " - max: " << max;
    logString.flush();
    log.flush();
}
