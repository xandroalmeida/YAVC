#include <QtGui/QApplication>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "videoprofile.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("SonicIT");
    QCoreApplication::setOrganizationDomain("sonicit.com.br");
    QCoreApplication::setApplicationName("YAVC");
    QCoreApplication::setApplicationVersion("0.1.0-beta");

    QSettings::setDefaultFormat(QSettings::IniFormat);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

