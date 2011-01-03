#ifndef MOVIEINFO_H
#define MOVIEINFO_H
#include <QString>
#include <QMetaType>

class MovieInfo
{
public:
    MovieInfo(const QString & fileName);
    MovieInfo();
private:
    QString infoText;
    int m_duration;
    int m_bitrate;
    int m_height;
    int m_width;
    QString m_name;
    QString m_fileName;

public:
    static MovieInfo get(const QString & fileName);
    QString info() const;
    int duration() const;
    int bitrate() const;
    int height() const;
    int width() const;
    QString name() const;
    QString fineName() const;
};

Q_DECLARE_METATYPE(MovieInfo)
#endif // MOVIEINFO_H
