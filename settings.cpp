#include "settings.h"
#include <QDir>
#include <QDebug>

AppSettings::AppSettings()
{    
}

AppSettings::~AppSettings()
{
}


QString AppSettings::ffmpegFolder(){
#ifdef QT_NO_DEBUG
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
    settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
    return settings.value("My Video").toString();
#else
    return "C:/Projetos/";
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

