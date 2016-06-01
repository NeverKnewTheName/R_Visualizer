#include "sendmessages.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendMessages w;
    w.show();

    return a.exec();
}
