#include "mainwindow.h"
#include <QApplication>

#include "can_packet.h"
#include "msg.h"
#include "errorlogentry.h"

// // // DEBUG // // //
#include <QDebug>
#include "msgparser.h"
#include "msgdatawidget.h"

// // // DEBUG // // //

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr");
    qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr");
    qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr");
    qRegisterMetaType <Msg>("Msg");
    qRegisterMetaType <MsgDataStruc>("MsgDataStruc");
    qRegisterMetaType <DataByteVect>("DataByteVect");
    qRegisterMetaType <ErrorLogEntry>("ErrorLogEntry");

    MainWindow w;
    w.show();

    return a.exec();
}
