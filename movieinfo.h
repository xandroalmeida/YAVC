/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef MOVIEINFO_H_
#define MOVIEINFO_H_

#include <QString>
#include <QMetaType>
#include <QVariant>

class MovieInfo {
 public:
    explicit MovieInfo(const QString & fileName);
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
    QString info() const;
    int duration() const;
    int bitrate() const;
    int height() const;
    int width() const;
    QString name() const;
    QString fileName() const;
};

Q_DECLARE_METATYPE(MovieInfo)
#endif  // MOVIEINFO_H_
