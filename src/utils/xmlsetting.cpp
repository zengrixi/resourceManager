#include "xmlsetting.h"

XmlSetting::XmlSetting(const QString &file) {
    file_ = new QFile(file);
    if (!file_->open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << QString("cannot write file %1(%2)").arg(file).arg(file_->errorString());
        return;
    }

    writeXml();
}

void XmlSetting::writeXml() {
    QXmlStreamWriter writer(file_);

    writer.setAutoFormatting(true);                           //自动格式化
    writer.writeStartDocument("1.0", true);                   //开始文档 ( XML 声明)
    writer.writeComment(QObject::tr("软件协议数据配置文件")); //注释
    writer.writeProcessingInstruction("xml-stylesheet type=\"text/css\"href=\"style.css\""); //处理指令

    // DTD
    writer.writeDTD(QObject::tr("<!DO>"))
}
