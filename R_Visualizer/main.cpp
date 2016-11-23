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
    MsgStorageTest();


//    QFile log("MsgStorageTestLog.log");
//    QFile logTrans("Translated__MsgStorageTestLog.log");

//    log.open(QIODevice::ReadOnly);
//    logTrans.open(QIODevice::WriteOnly);

//    QDataStream logString(&log);

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


int MsgStorageTest()
{
    QElapsedTimer myTimer;
    quint16 elapsedTime;

    const int NrOfMessages = 100000500;//100000500; //10000000;
    const double sizeDivisor = 10000.0;//10000.0;

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


    MsgStorage msgStore(1000,4);

    myTimer.restart();
//    for(Msg &msg : msgs)
//        msgStore.append(msg);
    for(int i = 0; i < NrOfMessages; i++)
    {
        msgStore.append(Msg(QDateTime::fromMSecsSinceEpoch(i),i,i,DataByteVect()));
//        if(!(i % (int)100))
//        {
//            logString << "\n\t Append at: " << i;
//            logString.flush();
//        }
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage append "<< NrOfMessages <<" Msgs -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << elapsedTime/NrOfMessages << "ms";


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
    while(sizeOfMsgStore--)
    {
        int Index = sizeOfMsgStore;
        Msg msg(msgStore.at(Index));
//        qDebug() << "Index: " << Index << " retrieved: " << msg.getId() << " : " << msg.getTimestamp();
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages <<" Msgs BACKWARD -> Time(ms): " << elapsedTime;
    logString << "\n\t\tTimePerMsg: " << elapsedTime/NrOfMessages << "ms";
    logString.flush();
    log.flush();

    sizeOfMsgStore = NrOfMessages;
    myTimer.restart();
    while(sizeOfMsgStore--)
    {
        int RandomIndex = qrand()%NrOfMessages;
        Msg msg(msgStore.at(RandomIndex));
//        qDebug() << "RandomIndex: " << RandomIndex << " retrieved: " << msg.getId() << " : " << msg.getTimestamp();
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages <<" Msgs RANDOM ACCESS -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << elapsedTime/NrOfMessages << "ms";
    logString.flush();
    log.flush();
    sizeOfMsgStore = NrOfMessages/(int)sizeDivisor;

    myTimer.restart();
    while(sizeOfMsgStore--)
    {
        int RandomIndex = qrand()%NrOfMessages;
        Msg msg(msgStore.at(RandomIndex));
        logString << "\n\tRandomIndex: " << RandomIndex << " retrieved: " << msg.getId() << " __ time: " << myTimer.elapsed();
        if(!(sizeOfMsgStore % (int)sizeDivisor))
        {
            logString.flush();
        }
    }
    elapsedTime = myTimer.elapsed();
    logString << "\nMsgStorage retrieve "<< NrOfMessages/sizeDivisor <<" Msgs and print with RANDOM ACCESS -> Time(ms): " << elapsedTime;
    logString << "\n\t\t TimePerMsg: " << elapsedTime/(NrOfMessages/sizeDivisor) << "ms";

    logString << "\n\nEND time: " << QDateTime::currentDateTime().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    logString.flush();
    log.flush();
    log.close();

    return 0;
}
