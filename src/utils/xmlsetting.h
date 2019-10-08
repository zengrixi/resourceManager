#ifndef XMLSETTING_H
#define XMLSETTING_H

#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QString>
#include <QXmlStreamWriter>

class XmlSetting {
public:
    XmlSetting();
    ~XmlSetting();

    void write_xml(const QString &file);

    void read_xml(const QString &file);

private:
    QDomDocument *protocols_;
    QFile *file_;
};

#endif // XMLSETTING_H
