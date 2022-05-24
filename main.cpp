#include "mainwindowtargets.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowTargets w;
    w.show();
    return a.exec();
}
