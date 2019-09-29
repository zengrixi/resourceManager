#ifndef XMLSETTING_H
#define XMLSETTING_H

#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QString>
#include <QXmlStreamWriter>

class XmlSetting {
public:
    XmlSetting(const QString &file);
    ~XmlSetting();

    void writeXml();

private:
    QDomDocument *protocols_;
    QFile *file_;
};

#endif // XMLSETTING_H
