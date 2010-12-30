#include "movieinfo.h"
#include <QProcess>
#include <QRegExp>
#include <QDebug>

MovieInfo::MovieInfo(const QString & fileName)
{
    QString prg("C:\\MinGW\\msys\\1.0\\home\\saoadalm\\ffmpeg-0.6.1\\ffprobe.exe");
    QStringList args = QStringList() << fileName;
    QProcess proc;
    proc.start(prg, args, QProcess::ReadOnly);
    proc.waitForStarted();
    proc.waitForFinished();
    QString txt = proc.readAllStandardError();

    int idx = -1;
    if ((idx = txt.indexOf("Input #0")) > 0) {
        txt = txt.mid(idx);
    }
    this->infoText = txt;
    QRegExp re("Duration:\\s([^,]*)");
    if (re.indexIn(txt) > 0) {
        QStringList fields = re.cap(1).split(":");
        if (fields.size() == 3) {
            qDebug() << fields;
            this->m_duration = fields.at(2).toInt();
            this->m_duration += fields.at(1).toInt() * 60;
            this->m_duration += fields.at(0).toInt() * 60 * 60;
            qDebug() << m_duration;
        }
    }
}

MovieInfo MovieInfo::get(const QString & fileName)
{
    MovieInfo info(fileName);
    return info;
}

QString MovieInfo::info()
{
    return this->infoText;
}

int MovieInfo::duration() {
    return this->m_duration;
}
