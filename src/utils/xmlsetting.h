#ifndef XMLSETTING_H
#define XMLSETTING_H

#include <QDebug>
#include <QFile>
#include <QString>
#include <QXmlStreamWriter>

class XmlSetting {
public:
    XmlSetting(const QString &file);

    void writeXml();

private:
    QFile *file_;
};

#endif // XMLSETTING_H
