#include "messageconfig.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MessageConfig w;
    w.show();

    return a.exec();
}
