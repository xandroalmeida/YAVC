#include "movieinfo.h"
#include <QProcess>

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
