#include "movieconvertthread.h"
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "settings.h"

#include <windows.h>

/* Hack win32 start */
int static cpuCount = 0 ;

static void lookupNumberOfCpu() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    cpuCount = si.dwNumberOfProcessors;
}
/* Hack win32 end */


MovieConvertThread::MovieConvertThread(QStringList const &sources, QString const &profileName):
    stopPlease(false)
{
    lookupNumberOfCpu();
    this->m_sources = sources;
    QList<VideoProfile> list = VideoProfile::getList();
    for (int i = 0; i < list.size(); i++) {
        if (list.at(i).name() == profileName)
            this->m_videoProfile = list.at(i);
    }
}

void MovieConvertThread::stopWhenYouCan()
{
    this->stopPlease = true;
}

void MovieConvertThread::run() {
    for (int i = 0; i < m_sources.size(); i++) {
        QString fin = m_sources.at(i);
        QString fout = fin;
        int idx = -1;
        if((idx = fout.lastIndexOf(".")) > -1) {
            fout = fout.left(idx+1) + m_videoProfile.extension();
        }

        fout = AppSettings::outputFolder() + QDir::separator() + m_videoProfile.prefix() + QFileInfo(fout).fileName();

        //qDebug() << fout;

        QString prg = AppSettings::ffmpegFolder() + "\\ffmpeg.exe";
        //qDebug() << prg;
        QStringList args = QStringList() << "-y" << "-i" << fin;
        args << m_videoProfile.options().split(" ");

        //Lets go use all the cores!
        if (cpuCount > 0)
            args << "-threads" << QString::number(cpuCount);

        args << fout;
        qDebug() << args;
        qDebug() << fout;

        QProcess proc;
        proc.start(prg, args, QProcess::ReadOnly);
        if (!proc.waitForStarted()) {
            qDebug() << "Not started";
            return;
        }

        int totalDuraction = -1;
        QRegExp re("time=(\\S*)");
        while (!proc.waitForFinished(500)) {
            if (this->stopPlease) {
                qDebug() << "Ops, stop de ffmpeg";
                proc.close();
                return;
            }

            QString log = proc.readAllStandardError();
            if (totalDuraction > 0 && re.indexIn(log) > 0) {
                float time = re.cap(1).toFloat();
                time = (time/totalDuraction) * 100;

                emit progress((int)time);
            } else if (totalDuraction < 0) {
                QRegExp r1("Duration:\\s([^,]*)");
                if (r1.indexIn(log) > 0) {
                    QStringList fields = r1.cap(1).split(":");
                    if (fields.size() == 3) {
                        totalDuraction = fields.at(2).toFloat();
                        totalDuraction += fields.at(1).toInt() * 60;
                        totalDuraction += fields.at(0).toInt() * 60 * 60;
                    }
                }
            }
        }

        qDebug() << proc.readAllStandardError();
    }
}
