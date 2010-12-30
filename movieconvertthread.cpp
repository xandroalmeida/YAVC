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

        QString prg = "C:\\MinGW\\msys\\1.0\\home\\Alexandro\\ffmpeg-0.6.1\\ffmpeg.exe";
        QStringList args = QStringList() << "-y" << "-i" << fin << fout ;
        qDebug() << args;

        QProcess proc;
        proc.start(prg, args, QProcess::ReadOnly);
        if (!proc.waitForStarted())
            return;

        int totalDuraction = -1;
        QRegExp re("time=(\\S*)");
        while (!proc.waitForFinished(500)) {
            if (this->stopPlease) {
                qDebug() << "Ops, stop de ffmpeg";
                proc.close();
                return;
            }

            QString log = proc.readAllStandardError();
            qDebug() << log;
            if (totalDuraction > 0 && re.indexIn(log) > 0) {
                float time = re.cap(1).toFloat();
                time = (time/totalDuraction) * 100;

                emit progress((int)time);
            } else if (totalDuraction < 0) {
                QRegExp r1("Duration:\\s([^,]*)");
                if (r1.indexIn(log) > 0) {
                    QStringList fields = r1.cap(1).split(":");
                    if (fields.size() == 3) {
                        qDebug() << fields;
                        totalDuraction = fields.at(2).toFloat();
                        totalDuraction += fields.at(1).toInt() * 60;
                        totalDuraction += fields.at(0).toInt() * 60 * 60;
                    }
                }
            }
        }
    }
}
