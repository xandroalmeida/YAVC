#ifndef MOVIECONVERTTHREAD_H
#define MOVIECONVERTTHREAD_H

#include "videoprofile.h"

#include <QThread>
#include <QStringList>
#include <QProcess>

class MovieConvertThread : public QThread
{
    Q_OBJECT

private:
    QStringList m_sources;
    bool stopPlease;    
    VideoProfile m_videoProfile;

public:
    MovieConvertThread(QStringList const &sources, QString const &profileName);
    virtual void run();
    void stopWhenYouCan();

signals:
    void progress(int newValue);

};

#endif // MOVIECONVERTTHREAD_H
