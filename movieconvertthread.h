#ifndef MOVIECONVERTTHREAD_H
#define MOVIECONVERTTHREAD_H

#include <QThread>
#include <QStringList>

class MovieConvertThread : public QThread
{

private:
    QStringList m_sources;
public:
    MovieConvertThread(QStringList const &sources);
    virtual void run();
};

#endif // MOVIECONVERTTHREAD_H
