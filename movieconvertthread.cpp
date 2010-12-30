#include "movieconvertthread.h"
#include <QString>
#include <QProcess>
#include <QDebug>

MovieConvertThread::MovieConvertThread(QStringList const &sources) {
    this->m_sources = sources;
}

void MovieConvertThread::run() {
    for (int i = 0; i < m_sources.size(); i++) {
        QString fin = m_sources.at(i);
        QString fout = fin + ".mp4";
        qDebug() << "Converting" << fin << "to" << fout;
        QProcess proc;
        QString prg = "C:\\MinGW\\msys\\1.0\\home\\saoadalm\\ffmpeg-0.6.1\\ffmpeg.exe";
        QStringList args = QStringList() << "-y" << "-i" << fin << fout ;
        qDebug() << args;
        proc.start(prg, args, QProcess::ReadOnly);
        proc.waitForStarted();
        qDebug() << "ffmpeg started";
        while (proc.state() == QProcess::Running) {
            qDebug() << "rodando";
            proc.waitForReadyRead();
            qDebug() << proc.readAllStandardError();
        }
    }
}
