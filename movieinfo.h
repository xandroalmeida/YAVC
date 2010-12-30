#ifndef MOVIEINFO_H
#define MOVIEINFO_H
#include <QString>

class MovieInfo
{
private:
    MovieInfo(const QString & fileName);
    QString infoText;
    int m_duration;

public:
    static MovieInfo get(const QString & fileName);
    QString info();
    int duration();

};

#endif // MOVIEINFO_H
