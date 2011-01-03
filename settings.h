#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class AppSettings
{
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

#endif // SETTINGS_H
