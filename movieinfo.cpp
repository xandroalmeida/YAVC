#include "movieinfo.h"
#include "settings.h"

#include <QProcess>
#include <QRegExp>
#include <QDir>
#include <QDebug>

MovieInfo::MovieInfo()
{
}

MovieInfo::MovieInfo(const QString & fileName)
{
    this->m_name = QFileInfo(fileName).fileName();
    this->m_fileName = fileName;

    QString prg = AppSettings::ffmpegFolder() + QDir::separator() + "ffmpeg.exe";
    qDebug() << prg;
    QStringList args = QStringList() << "-i" << fileName;
    QProcess proc;
    proc.start(prg, args, QProcess::ReadOnly);
    if(!proc.waitForStarted()) {
        this->infoText = "Err";
        return;
    }
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
            this->m_duration = fields.at(2).toFloat();
            this->m_duration += fields.at(1).toInt() * 60;
            this->m_duration += fields.at(0).toInt() * 60 * 60;
        }
    }

    re.setPattern("bitrate:\\s(\\d+)\\skb");
    if (re.indexIn(txt) > 0) {
        this->m_bitrate = re.cap(1).toInt();
    }

    re.setPattern("(\\d+)x(\\d+)");
    if (re.indexIn(txt) > 0) {
        this->m_width = re.cap(1).toInt();
        this->m_height = re.cap(2).toInt();
    }
}

QString MovieInfo::info() const
{
    return this->infoText;
}

int MovieInfo::duration() const
{
    return this->m_duration;
}

int MovieInfo::bitrate() const
{
    return this->m_bitrate;
}

int MovieInfo::height() const
{
    return this->m_height;
}

int MovieInfo::width() const
{
    return this->m_width;
}

QString MovieInfo::name() const
{
    return this->m_name;
}

QString MovieInfo::fileName() const
{
    return this->m_fileName;
}
