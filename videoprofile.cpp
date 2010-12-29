#include "videoprofile.h"
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>

VideoProfile::VideoProfile()
{
}

QList<VideoProfile> VideoProfile::getList()
{
    QList<VideoProfile> list;

    QXmlStreamReader xml;
    QFile* resource = new QFile(":/info/profiles.xml");
    resource->open(QIODevice::ReadOnly);
    xml.addData(resource->readAll());
    resource->close();

    QString currentTag;
    QString options;
    QString name;

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            currentTag = xml.name().toString();
        } else if (xml.isEndElement()) {
            if (xml.name() == "profile") {
                VideoProfile v;
                v.m_name = name;
                v.m_options = options;
                list << v;
                name.clear();
                options.clear();
            }
        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (currentTag == "options") {
                options += xml.text().toString();
            } else if (currentTag == "name") {
                name += xml.text().toString();
            }
        }
    }
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
    }

    return list;
}

QString VideoProfile::name() const
{
    return this->m_name;
}

QString VideoProfile::options() const
{
    return this->m_options;
}
