#ifndef MOVIECONVERTTHREAD_H
#define MOVIECONVERTTHREAD_H

#include "videoprofile.h"
#include "movieinfo.h"

#include <QThread>
#include <QList>
#include <QProcess>

class MovieConvertThread : public QThread
{
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

#endif // MOVIECONVERTTHREAD_H
