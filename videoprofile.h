#ifndef VIDEOPROFILE_H
#define VIDEOPROFILE_H
#include <QList>
#include <QString>
#include <QMetaType>

class VideoProfile
{
private:
    QString m_name;
    QString m_options;
    QString m_extension;
    QString m_prefix;

public:
    VideoProfile();
    static QList<VideoProfile> getList();

    QString name() const;
    QString options() const;
    QString extension() const;
    QString prefix() const;
};

Q_DECLARE_METATYPE(VideoProfile)
#endif // VIDEOPROFILE_H
