#include "UdpSocket.h"

/*-----------------------------------------------------------------------------|
 |                                UdpSocket                                    |
 |----------------------------------------------------------------------------*/

UdpSocket::~UdpSocket() {}

void UdpSocket::run() {
    while (socket_.hasPendingDatagrams()) {
        QByteArray array; //拥于存放接收的数据报

        /**
         * pendingDatagramSize为返回第一个在等待读取报文的size，
         * resize函数是把datagram的size归一化到参数size的大小一样
         */
        array.resize(socket_.pendingDatagramSize());
        /**
         * 接收数据报，将其存放到datagram中
         * 将读取到的不大于datagram.size()大小数据输入到datagram.data()中，
         * datagram.data()返回的是一个字节数组中存储数据位置的指针
         */
        socket_.readDatagram(array.data(), array.size());

        QString hex_data = array.toHex(); //将数据报内容显示出来
        process_data(hex_data);           // 处理数据
    }
}

void UdpSocket::process_data(QString data) {}

/*-----------------------------------------------------------------------------|
 |                                XmlSetting                                   |
 |----------------------------------------------------------------------------*/

XmlSetting::XmlSetting() {}

XmlSetting::~XmlSetting() {}

void XmlSetting::write_xml(const QString &name) {
    QFile file(name);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << QString("cannot write file %1(%2)").arg(name).arg(file.errorString());
        return;
    }

    //定义根节点
    protocols_ = new QDomDocument();
    protocols_->appendChild(protocols_->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));

    //添加根元素
    QDomElement protocols = protocols_->createElement("protocols");
    protocols_->appendChild(protocols);

    QDomElement proto1 = protocols_->createElement("protocol1");
    proto1.setAttribute("proto_name", "udp1");
    proto1.setAttribute("host_addr", "127.0.0.1");
    proto1.setAttribute("port", 8080);
    proto1.setAttribute("endian", 0);
    protocols.appendChild(proto1);

    QDomElement struct1 = protocols_->createElement("struct1");
    struct1.setAttribute("head_len", 20);
    struct1.setAttribute("struct_name", "Trajectory");
    struct1.setAttribute("struct_len", 14);
    struct1.setAttribute("struct_type", 0);
    proto1.appendChild(struct1);

    QDomElement field1 = protocols_->createElement("field1");
    field1.setAttribute("field_name", "target_id");
    field1.setAttribute("field_type", "unsigned int");
    field1.setAttribute("field_len", 4);
    struct1.appendChild(field1);

    QDomElement field2 = protocols_->createElement("field2");
    field2.setAttribute("field_name", "target_name");
    field2.setAttribute("field_type", "char *");
    field2.setAttribute("field_len", 10);
    struct1.appendChild(field2);

    QTextStream out(&file);
    protocols_->save(out, 4);

    file.close();
}

void XmlSetting::read_xml(const QString &name) {
    QFile file(name);
    if (!file.open(QFile::ReadOnly)) return;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement(); //返回根节点
    qDebug() << root.nodeName();
    QDomNode node = root.firstChild(); //获得第一个子节点
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement e = node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            //打印键值对，tagName和nodeName是一个东西
            qDebug() << e.tagName() << " " << e.attribute("host_addr") << " " << e.attribute("port")
                     << e.attribute("endian") << e.attribute("proto_name");

            QDomNodeList list = e.childNodes();
            //遍历子元素，count和size都可以用,可用于标签数计数
            for (int i = 0; i < list.count(); i++) {
                QDomNode n = list.at(i);
                if (node.isElement()) qDebug() << n.nodeName() << ":" << n.toElement().text();
            }
        }
        node = node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}

UdpSocket::UdpSocket(QString addr, quint16 port) {
    host_addr_.setAddress(addr);
    bool bPort = socket_.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ReuseAddressHint);
    bool bAddr = socket_.joinMulticastGroup(host_addr_);

    if (bPort && bAddr) {
        qDebug() << QObject::tr("bind sucess");
    } else {
        qDebug() << QObject::tr("bind error");
    }
}
