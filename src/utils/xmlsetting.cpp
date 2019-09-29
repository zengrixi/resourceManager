#include "xmlsetting.h"

XmlSetting::XmlSetting(const QString &file) {
    file_ = new QFile(file);
    if (!file_->open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << QString("cannot write file %1(%2)").arg(file).arg(file_->errorString());
        return;
    }

    writeXml();
}

XmlSetting::~XmlSetting() {
    if (file_ != nullptr) {
        file_->close();
        delete file_;
    }
}

void XmlSetting::writeXml() {
    QXmlStreamWriter writer(file_);

    writer.setAutoFormatting(true);                           //自动格式化
    writer.writeStartDocument("1.0", true);                   //开始文档 ( XML 声明)
    writer.writeComment(QObject::tr("软件协议数据配置文件")); //注释
    writer.writeProcessingInstruction("xml-stylesheet type=\"text/css\"href=\"style.css\""); //处理指令

    //定义根节点
    protocols_ = new QDomDocument();

    protocols_->appendChild(protocols_->createProcessingInstruction("xml", "Version=\"1.0\" encoding=\"UTF-8\""));

    //添加根元素
    QDomElement protocols = protocols_->createElement("protocol");
    protocols.setAttribute("id", "1");
    protocols_->appendChild(protocols);

    QDomElement proto1 = protocols_->createElement("protocol1");
    proto1.setAttribute("proto_name", "udp1");
    proto1.setAttribute("host_addr", "127.0.0.1");
    proto1.setAttribute("port", "8080");
    proto1.setAttribute("endian", "0");
    protocols.appendChild(proto1);

    QDomElement struct1 = protocols_->createElement("struct1");
    struct1.setAttribute("head_len", "20");
    struct1.setAttribute("struct_name", "Trajectory");
    struct1.setAttribute("struct_len", "14");
    struct1.setAttribute("struct_type", "0");
    proto1.appendChild(struct1);

    QDomElement field1 = protocols_->createElement("field1");
    field1.setAttribute("field_name", "target_id");
    field1.setAttribute("field_type", "unsigned int");
    field1.setAttribute("field_len", "4");
    struct1.appendChild(field1);

    QDomElement field2 = protocols_->createElement("field2");
    field2.setAttribute("field_name", "target_name");
    field2.setAttribute("field_type", "char *");
    field2.setAttribute("field_len", "10");
    struct1.appendChild(field2);

    QTextStream out(file_);
    protocols_->save(out, 4);
}
