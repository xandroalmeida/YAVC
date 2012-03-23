/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <QtGui/QApplication>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "videoprofile.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("SonicIT");
    QCoreApplication::setOrganizationDomain("sonicit.com.br");
    QCoreApplication::setApplicationName("YAVC");
    QCoreApplication::setApplicationVersion("0.1.4");

    QSettings::setDefaultFormat(QSettings::IniFormat);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
