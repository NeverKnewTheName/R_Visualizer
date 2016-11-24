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
// // // DEBUG // // //

int MsgStorageTest();
void MsgStorageRemoveTest();

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
    myTimer.start();
    MsgStorageRemoveTest();

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

void MsgStorageRemoveTest()
{
    QElapsedTimer myTimer;
    QElapsedTimer perDeleteTimer;
    quint16 elapsedTime;

    const int NrOfMessages = 100;//100000500; //10000000;
//    const double sizeDivisor = 100.0;//10000.0;

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

    logString.flush();
    log.flush();


    MsgStorage msgStore(10,3);

    myTimer.restart();
    for(int i = 0; i < NrOfMessages; i++)
    {
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage append "<< NrOfMessages <<" Msgs -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << (double)elapsedTime/NrOfMessages << "ms";
    logString.flush();

    logString << "\nDelete last element";
    myTimer.restart();
    msgStore.remove(NrOfMessages-1);
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage remove "<< NrOfMessages-1 <<" nTh Element -> Time(ms): " << elapsedTime;

    logString << "\nDelete first element";
    myTimer.restart();
    msgStore.remove(0);
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage remove "<< 0 <<" nTh Element -> Time(ms): " << elapsedTime;


    int RandomIndex;
    int MsgStoreSize = msgStore.size();
    while(MsgStoreSize)
    {
//        RandomIndex = qrand()%(MsgStoreSize);
        RandomIndex = MsgStoreSize-1;
        logString << "\nDelete random element: " << RandomIndex;
        myTimer.restart();
        msgStore.remove(RandomIndex);
        elapsedTime = myTimer.elapsed();
        logString << "\nMsgStorage removed "<< RandomIndex <<" nTh Element -> Time(ms): " << elapsedTime;
        MsgStoreSize = msgStore.size();
        logString << "\n\tMsgStorage size: " << MsgStoreSize;
        logString.flush();
        log.flush();
    }
    logString.flush();
    log.flush();

    int sizeOfMsgStore = msgStore.size();
    while(sizeOfMsgStore--)
    {
        int Index = sizeOfMsgStore;
        Msg msg(msgStore.at(Index));
        logString << "\nIndex: " << Index << " retrieved: " << msg.getId();
    }

    logString.flush();
    log.flush();
    log.close();
}


int MsgStorageTest()
{
    QElapsedTimer myTimer;
    QElapsedTimer perMsgTimer;
    quint16 elapsedTime;

    const int NrOfMessages = 5000;//100000500; //10000000;
    const double sizeDivisor = 100.0;//10000.0;

    QFile log("MsgStorageTestLog.log");


    if(!log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error open file to save: " << log.fileName();
    }
    else
    {
        qDebug() << "File Opened";
    }

    QTextStream logString(&log);
    //    QVector<Msg> msgs;
    //    QVector<Msg> TestVect;
    //    myTimer.start();
    //    for(int i = 0; i < NrOfMessages; i++)
    //    {
    //        msgs.append(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect()));
    //    }
    //    qDebug() << "QVector append "<<NrOfMessages<<" Msgs -> Time(ms): " << myTimer.elapsed();
    logString << "START time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString << "\n\nNrOfMessages: " << NrOfMessages;

    logString.flush();
    log.flush();
    //    myTimer.start();
    //    for(Msg &msg : msgs)
    //        TestVect.append(msg);

    //    qDebug() << "QVector append 5000 Msgs -> Time(ms): " << myTimer.elapsed();

    //    int SizeOfTestVect = TestVect.size();

    //    myTimer.restart();
    //    while(SizeOfTestVect--)
    //    {
    //        /*Msg msg =*/ TestVect.at(SizeOfTestVect);
    //    }
    //    qDebug() << "QVector retrieve 5000 Msgs backward -> Time(ms): " << myTimer.elapsed();

    //    myTimer.restart();
    //    for(int i = 0; i < 5000; i++)
    //    {
    //        /*Msg msg =*/ TestVect.at(i);
    //        qDebug() << msg.getId() << " : " << msg.getTimestamp();
    //    }
    //    qDebug() << "QVector retrieve 5000 Msgs forward -> Time(ms): " << myTimer.elapsed();


    MsgStorage msgStore(1000,3);

    myTimer.restart();
    //    for(Msg &msg : msgs)
    //        msgStore.append(msg);
    for(int i = 0; i < NrOfMessages; i++)
    {
        msgStore.append(std::move(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect())));
        //        if(!(i % (int)100))
        //        {
        //            logString << "\n\t Append at: " << i;
        //            logString.flush();
        //        }
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage append "<< NrOfMessages <<" Msgs -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << (double)elapsedTime/NrOfMessages << "ms";


    //    qDebug() << "MemUsage (msgs): " << msgs.capacity() * sizeof(Msg);
    logString << "\nMemUsage (msgStore): " << msgStore.MemUsage();

    int sizeOfMsgStore = msgStore.size();
    logString << "\nMsgStoreSize: " << sizeOfMsgStore;

    logString.flush();
    log.flush();
    //    myTimer.restart();
    //    for(int i = 0; i < NrOfMessages; i++)
    //    {
    //        Msg msg = msgStore.at(i);
    ////        qDebug() << msg.getId() << " : " << msg.getTimestamp();
    //    }
    //    qDebug() << "MsgStorage retrieve "<< NrOfMessages <<" Msgs forward -> Time(ms): " << myTimer.elapsed();

    //    sizeOfMsgStore /= 1000;

    sizeOfMsgStore = NrOfMessages;
    myTimer.restart();
    perMsgTimer.restart();
    while(sizeOfMsgStore--)
    {
        int Index = sizeOfMsgStore;
        Msg msg(msgStore.at(Index));
        if(!(Index % (int)sizeDivisor))
        {
            logString << "\nBackwards: tempRes: " << (perMsgTimer.elapsed()/(double)sizeDivisor);
            perMsgTimer.restart();
            logString.flush();
            log.flush();
        }
        //        qDebug() << "Index: " << Index << " retrieved: " << msg.getId() << " : " << msg.getTimestamp();
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages <<" Msgs BACKWARD -> Time(ms): " << elapsedTime;
    logString << "\n\t\tTimePerMsg: " << (double)elapsedTime/NrOfMessages << "ms";
    logString.flush();
    log.flush();

    sizeOfMsgStore = NrOfMessages;
    myTimer.restart();
    perMsgTimer.restart();
    while(sizeOfMsgStore--)
    {
        int RandomIndex = qrand()%NrOfMessages;
        Msg msg(msgStore.at(RandomIndex));
        if(!(sizeOfMsgStore % (int)sizeDivisor))
        {
            logString << "\n\t RandomIndex: " << RandomIndex << " -> ID: " << msg.getId();
            logString << "\nRandomIndex: tempRes: " << perMsgTimer.elapsed()/(double)sizeDivisor;
            perMsgTimer.restart();
            logString.flush();
            log.flush();
        }
        //        qDebug() << "RandomIndex: " << RandomIndex << " retrieved: " << msg.getId() << " : " << msg.getTimestamp();
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages <<" Msgs RANDOM ACCESS -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << (double)elapsedTime/NrOfMessages << "ms";
    logString.flush();
    log.flush();
    sizeOfMsgStore = NrOfMessages/(int)sizeDivisor;

    myTimer.restart();
    perMsgTimer.start();
    perMsgTimer.restart();
    while(sizeOfMsgStore--)
    {
        int RandomIndex = qrand()%NrOfMessages;
        Msg msg(msgStore.at(RandomIndex));
        logString << "\n\tRandomIndex: " << RandomIndex << " retrieved: " << msg.getId() << " __ time: " << perMsgTimer.elapsed();
        perMsgTimer.restart();
        if(!(sizeOfMsgStore % (int)sizeDivisor))
        {
            logString.flush();
            log.flush();
        }
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages/sizeDivisor <<" Msgs and print with RANDOM ACCESS -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << (double)elapsedTime/(NrOfMessages/sizeDivisor) << "ms";

    logString << "\n\nEND time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString.flush();
    log.flush();
    log.close();

    return 0;
}
