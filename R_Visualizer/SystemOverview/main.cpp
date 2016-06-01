#include "systemoverview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SystemOverview w;
    w.show();

    return a.exec();
}
