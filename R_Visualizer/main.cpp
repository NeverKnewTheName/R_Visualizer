#include "mainwindow.h"
#include <QApplication>

#include "can_packet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr");

    MainWindow w;
    w.show();

    return a.exec();
}
