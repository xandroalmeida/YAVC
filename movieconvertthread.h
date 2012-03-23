/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef MOVIECONVERTTHREAD_H_
#define MOVIECONVERTTHREAD_H_

#include "videoprofile.h"
#include "movieinfo.h"

#include <QThread>
#include <QList>
#include <QProcess>

class MovieConvertThread : public QThread {
    Q_OBJECT

 private:
    QList<MovieInfo> m_movies;
    bool stopPlease;
    VideoProfile m_videoProfile;

 public:
    MovieConvertThread(QList<MovieInfo> const &movies, VideoProfile const &videoProfile);
    virtual void run();
    void stopWhenYouCan();

 signals:
    void progressMovie(int actual);
    void progressOverall(int actual);
    void startConvert(MovieInfo const &movieinfo);
    void finishedConvert(MovieInfo const &movieinfo, bool ok);
};

#endif  // MOVIECONVERTTHREAD_H_
