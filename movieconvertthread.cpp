#include "movieconvertthread.h"
#include <QString>
#include <QDebug>

MovieConvertThread::MovieConvertThread(QStringList const &sources):
    stopPlease(false)
{
    this->m_sources = sources;
}

void MovieConvertThread::stopWhenYouCan()
{
    this->stopPlease = true;
}

void MovieConvertThread::run() {
    for (int i = 0; i < m_sources.size(); i++) {
        QString fin = m_sources.at(i);
        QString fout = fin + ".mp4";
        qDebug() << "Converting" << fin << "to" << fout;

        QString prg = "C:\\MinGW\\msys\\1.0\\home\\saoadalm\\ffmpeg-0.6.1\\ffmpeg.exe";
        QStringList args = QStringList() << "-y" << "-i" << fin << fout ;
        qDebug() << args;

        QProcess proc;
        proc.start(prg, args, QProcess::ReadOnly);
        proc.waitForStarted();

        int c = 0;
        while (!proc.waitForFinished(500)) {
            if (this->stopPlease) {
                qDebug() << "Ops, stop de ffmpeg";
                proc.close();
                return;
            }
            qDebug() << proc.readAllStandardError() << c++;
            emit progress(c*5);
        }
        qDebug() << "ffmpeg finished";
    }

    qDebug() << "MovieConvertThread::run finished";
}
