#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class AppSettings
{
private:
    AppSettings();

public:
    ~AppSettings();

    static QString outputFolder();
    static void setOutputFolder(const QString &value);

    static QString defaultInputFolder();
    static void setDefaultInputFolder(const QString &value);

};

#endif // SETTINGS_H