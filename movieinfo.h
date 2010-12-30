#ifndef MOVIEINFO_H
#define MOVIEINFO_H
#include <QString>

class MovieInfo
{
private:
    MovieInfo(const QString & fileName);
    QString infoText;

public:
    static MovieInfo get(const QString & fileName);
    QString info();

};

#endif // MOVIEINFO_H
