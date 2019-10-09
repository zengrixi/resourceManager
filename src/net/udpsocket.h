#pragma once

#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QList>
#include <QString>
#include <QThread>
#include <QUdpSocket>
#include <QXmlStreamWriter>

class UdpSocket : public QThread {
    Q_OBJECT

public:
    /**
     * @brief UdpSocket
     * @param addr 组播地址
     * @param port 端口
     */
    UdpSocket(QString addr, quint16 port);
    ~UdpSocket();

protected:
    /**
     * @brief run
     * 循环获取组播发送的数据并调用业务处理程序
     */
    virtual void run() override;

private slots:
    /**
     * @brief process_data 业务逻辑处理
     * @param data 接收到的数据
     */
    void process_data(QString data);

private:
    /* 协议相关 */
    quint16 port_;
    QString addr_;
    QUdpSocket socket_;
    QHostAddress host_addr_;
};

class NetWork : public QObject {
    Q_OBJECT

public:
    NetWork();
    virtual ~NetWork() override;

    bool udp_bind(QString addr, quint16 port);
};

class XmlSetting {
public:
    XmlSetting();
    ~XmlSetting();

    /**
     * @brief write_xml
     * @param file 文件路径
     */
    void write_xml(const QString &file);

    /**
     * @brief read_xml
     * @param file 文件路径
     */
    void read_xml(const QString &file);

private:
    QDomDocument *protocols_;
    QFile *file_;
};
