#include "settings.h"
#include <QDir>
#include <QDebug>

AppSettings::AppSettings()
{    
}

AppSettings::~AppSettings()
{
}


QString AppSettings::outputFolder() {
    QSettings m_settings;
    QString ret = m_settings.value("outputfolder").value<QString>();
    qDebug() << "outputFolder" << ret;
    if (ret == "") {
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
        settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
        ret = settings.value("My Video").toString();
    }
    return ret;
}

void AppSettings::setOutputFolder(const QString &value) {
    QSettings m_settings;
    qDebug() << "setOutputFolder" << value;
    m_settings.setValue("outputfolder", QVariant(value));
    m_settings.sync();
}

QString AppSettings::defaultInputFolder() {
    QSettings m_settings;
    QString ret = m_settings.value("defaultInputFolder").value<QString>();
    qDebug() << "defaultInputFolder" << ret;
    if (ret == "") {
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows", QSettings::NativeFormat);
        settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
        ret = settings.value("My Video").toString() + QDir::separator() + "YAVC";
    }
    return ret;
}

void AppSettings::setDefaultInputFolder(const QString &value) {
    QSettings m_settings;
    qDebug() << "serDefaultInputFolder" << value;
    m_settings.setValue("defaultInputFolder", QVariant(value));
    m_settings.sync();
}
