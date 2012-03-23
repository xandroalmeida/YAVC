/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QSettings>

class AppSettings {
 private:
    AppSettings();

 public:
    ~AppSettings();

    static QString ffmpegFolder();

    static QString outputFolder();
    static void setOutputFolder(const QString &value);

    static QString defaultInputFolder();
    static void setDefaultInputFolder(const QString &value);

    static QString defaultVideoQuality();
    static void setDefaultVideoQuality(const QString &value);
};

#endif  // SETTINGS_H_
