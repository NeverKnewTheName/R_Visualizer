#include "mainwindow.h"
#include <QApplication>

#include "can_packet.h"
#include "msg.h"
#include "errorlogentry.h"

// // // DEBUG // // //
#include <QDebug>
#include "msgparser.h"
#include "msgdatawidget.h"
#include "msgstorage.h"
// // // DEBUG // // //

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

    QVector<Msg> msgs(30);
    MsgStorage msgStore(5,3);

    int one = 0;
    int mask = 3;
    qDebug() << (one-1 + mask) % mask;

    for(Msg &msg : msgs)
        msgStore.append(msg);

    int sizeOfMsgStore = msgStore.size();
    qDebug() << "MsgStoreSize" << sizeOfMsgStore;

    for(int i = 0; i < sizeOfMsgStore; i++)
    {
        qDebug() << msgStore.at(i).getTimestamp();
    }
    return 0;

//    MainWindow w;
//    w.show();

//    return a.exec();
}
