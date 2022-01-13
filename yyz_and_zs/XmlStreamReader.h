#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QXmlStreamAttribute>
#include <QList>

class XmlStreamReader
{
public:
    XmlStreamReader();
    ~XmlStreamReader();

    QString xmlStreamReaderFile(QString fileName);

protected:
    QList<QString> l_list;//存放标签的属性值
};

#endif // XMLSTREAMREADER_H
