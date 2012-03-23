/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "movieconvertthread.h"
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "settings.h"

static int cpuCount = 2;

#ifdef WIN32
#include <windows.h>

/* Hack win32 start */

static void lookupNumberOfCpu() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    cpuCount = si.dwNumberOfProcessors;
}
/* Hack win32 end */
#endif

MovieConvertThread::MovieConvertThread(QList<MovieInfo> const &movies, VideoProfile const &videoProfile)
    : stopPlease(false) {
#ifdef WIN32
    lookupNumberOfCpu();
#endif
    this->m_movies = movies;
    this->m_videoProfile = videoProfile;
}

void MovieConvertThread::stopWhenYouCan() {
    this->stopPlease = true;
}

void MovieConvertThread::run() {
    double overAllTimeTotal = 0;
    double overAllTime = 0;

    for (int i = 0; i < m_movies.size(); i++) {
        overAllTimeTotal += m_movies.at(i).duration();
    }

    qDebug() << "overAllTimeTotal = " << overAllTimeTotal;

    for (int i = 0; i < m_movies.size(); i++) {
        emit(startConvert(m_movies.at(i)));
        QString fin = m_movies.at(i).fileName();
        QString fout = fin;
        int idx = -1;
        if ((idx = fout.lastIndexOf(".")) > -1) {
            fout = fout.left(idx+1) + m_videoProfile.extension();
        }

        fout = AppSettings::outputFolder() + QDir::separator() + m_videoProfile.prefix() + QFileInfo(fout).fileName();

        QString prg = AppSettings::ffmpegFolder() + QDir::separator() + "ffmpeg.exe";
        QStringList args = QStringList() << "-y" << "-i" << fin;
        args << m_videoProfile.options().split(" ");

        // Lets go use all the cores!
        if (cpuCount > 0)
            args << "-threads" << QString::number(cpuCount);

        args << fout;
        qDebug() << "number of CPUs detected: " << cpuCount;

        QProcess proc;

        qDebug() << prg << args;

        proc.start(prg, args, QProcess::ReadOnly);
        if (!proc.waitForStarted()) {
            qDebug() << "err on start ffmpeg.";
            emit(finishedConvert(m_movies.at(i), false));
            continue;
        }

        qDebug() << "ffmpeg started.";

        QRegExp re("time=(\\S*\\s)");
        while (!proc.waitForFinished(500)) {
            QString log = proc.readAllStandardError();

            qDebug() << log;
            if (this->stopPlease) {
                proc.close();
                emit(finishedConvert(m_movies.at(i), false));
                return;
            }

            if (re.indexIn(log) > 0) {
                qDebug() << "RegEx: [" << re.cap(1) << "]";
                QStringList timeFields = re.cap(1).trimmed().split(":");
                qDebug() << "Fields: " << timeFields;
                float time = timeFields[0].toFloat() * 60 * 60;
                time += timeFields[1].toFloat() * 60;
                time += timeFields[2].toFloat();

                double overall = ((overAllTime + time)/overAllTimeTotal) * 100;
                emit progressOverall(static_cast<int>(overall));
                qDebug() << "overAllTime=" << overAllTime << " -- " << (overAllTime + time);

                time = (time/m_movies.at(i).duration()) * 100;
                emit progressMovie(static_cast<int>(time));
            }
        }

        // qDebug() << proc.readAllStandardOutput();
        // qDebug() << proc.readAllStandardError();

        qDebug() << "ffmpeg finished.";
        overAllTime += m_movies.at(i).duration();
        emit(finishedConvert(m_movies.at(i), true));
    }
}
