#ifndef VIDEOPROFILE_H
#define VIDEOPROFILE_H
#include <QList>
#include <QString>

class VideoProfile
{
private:
    VideoProfile();
    QString m_name;
    QString m_options;

public:
    static QList<VideoProfile> getList();

    QString name() const;
    QString options() const;
};

#endif // VIDEOPROFILE_H
