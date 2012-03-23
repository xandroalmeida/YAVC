/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef VIDEOPROFILE_H_
#define VIDEOPROFILE_H_

#include <QList>
#include <QString>
#include <QMetaType>

class VideoProfile {
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
#endif  // VIDEOPROFILE_H_
