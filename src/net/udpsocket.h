#pragma once

#include <QList>
#include <QObject>
#include <QUdpSocket>
#include <mutex>
#include <thread>

using namespace std;

class UdpSocket : public QObject {
    Q_OBJECT

private:
    static UdpSocket *pInstance;
    UdpSocket();

public:
    static UdpSocket *getInstance();
    ~UdpSocket();

    bool bindServer(QString addr, quint32 port);

    void processData(QString data, qint32 size);

public slots:
    /*
     * 读取服务器发送的消息
     */
    void readServer();

private:
    /* 协议相关 */
    uint16_t m_port;
    QString m_addr;
    QUdpSocket m_socket;
    QHostAddress m_hostAddr;
};
