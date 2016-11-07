#include "mainwindow.h"
#include <QApplication>

#include "can_packet.h"

// // // DEBUG // // //
#include <QDebug>
#include "msgparser.h"
// // // DEBUG // // //

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr");
    qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr");
    qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr");

    // // // DEBUG // // //
//    QString DebugFormatString = "#O0##O1##D0##V200##/O1##D1##/O0#";
//    QString DebugFormatString = "#O0##O1##D0##V200##/O1##O0##D0##D1##/O0##/O0#";
//    MsgParser parser(DebugFormatString);
//    MsgDataT msgData;
//    msgData.code = 5;
//    msgData.data0 = 0b11001010;
//    msgData.data1 = 0b00001111;
//    msgData.data2 = 0;
//    msgData.data3 = 0;
//    msgData.data4 = 0;
//    msgData.data5 = 0;
//    msgData.data6 = 0;

//    qDebug() << parser.parseToInt(msgData);
    // // // DEBUG // // //


    MainWindow w;
    w.show();

    return a.exec();
}
