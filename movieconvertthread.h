#ifndef MOVIECONVERTTHREAD_H
#define MOVIECONVERTTHREAD_H

#include <QThread>
#include <QStringList>
#include <QProcess>

class MovieConvertThread : public QThread
{
    Q_OBJECT

private:
    QStringList m_sources;
    bool stopPlease;    

public:
    MovieConvertThread(QStringList const &sources);
    virtual void run();
    void stopWhenYouCan();

signals:
    void progress(int newValue);

};

#endif // MOVIECONVERTTHREAD_H
