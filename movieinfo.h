#ifndef MOVIEINFO_H
#define MOVIEINFO_H
#include <QString>

class MovieInfo
{
private:
    MovieInfo(const QString & fileName);
    QString infoText;
    int m_duration;
    int m_bitrate;
    int m_height;
    int m_width;

public:
    static MovieInfo get(const QString & fileName);
    QString info() const;
    int duration() const;
    int bitrate() const;
    int height() const;
    int width() const;

};

#endif // MOVIEINFO_H
