#include <QtGui/QApplication>
#include "mainwindow.h"
#include "videoprofile.h"

int main(int argc, char *argv[])
{
    VideoProfile::getList();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
