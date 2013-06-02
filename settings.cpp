/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "settings.h"
#include <QDir>
#include <QDebug>
#include <QRect>


AppSettings::AppSettings() {
}

AppSettings::~AppSettings() {
}


QString AppSettings::ffmpegFolder() {
#ifndef QT_NO_DEBUG
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
    settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
    return settings.value("My Video").toString();
#else
    QString value;
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\YAVC", QSettings::NativeFormat);
    value = settings.value("Install_Dir").toString();
    if (value.isEmpty()) {
        QSettings settings1("HKEY_LOCAL_MACHINE\\SOFTWARE\\YAVC", QSettings::NativeFormat);
        value = settings1.value("Install_Dir").toString();
    }

    return value;
#endif
}

QString AppSettings::outputFolder() {
    QSettings m_settings;
    QString ret = m_settings.value("outputfolder").value<QString>();
    if (ret == "") {
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
        settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
        ret = settings.value("My Video").toString();
    }
    return ret;
}

void AppSettings::setOutputFolder(const QString &value) {
    QSettings m_settings;
    m_settings.setValue("outputfolder", QVariant(value));
    m_settings.sync();
}

QString AppSettings::defaultInputFolder() {
    QSettings m_settings;
    QString ret = m_settings.value("defaultInputFolder").value<QString>();
    if (ret == "") {
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
        settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
        ret = settings.value("My Video").toString() + QDir::separator() + "YAVC";
    }
    return ret;
}

void AppSettings::setDefaultInputFolder(const QString &value) {
    QSettings m_settings;
    m_settings.setValue("defaultInputFolder", QVariant(value));
    m_settings.sync();
}

QString AppSettings::defaultVideoQuality() {
    QSettings m_settings;
    QString ret = m_settings.value("defaultVideoQuality").value<QString>();
    return ret;
}

void AppSettings::setDefaultVideoQuality(const QString &value) {
    QSettings m_settings;
    m_settings.setValue("defaultVideoQuality", QVariant(value));
    m_settings.sync();
}

QRect AppSettings::windowGeometry() {
    QSettings m_settings;
    QRect ret = m_settings.value("windowSize").value<QRect>();
    return ret;
}

void AppSettings::setWindowGeometry(const QRect &value) {
    QSettings m_settings;
    m_settings.setValue("windowSize", QVariant(value));
    m_settings.sync();
}

