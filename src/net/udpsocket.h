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

    /**
     * 解析包头
     * 根据包头确定后面消息体的类型
     * 做出对应的处理
     */
    quint32 analyHead(QString data, qint32 size);

    /**
     * 解析综合航迹
     * 传入数据和大小
     * 返回包头中报文的类型
     */
    const char *analyFusionTrack(QString data, qint32 size);

    /*
     * 解析作战空间分析结果
     */
    const char *analySpaceAnalysis(QString data, qint32 size);

    /*
     * 解析弹道预报
     */
    const char *analyTrajectory(QString data, qint32 size);

public slots:
    /*
     * 读取服务器发送的消息
     */
    void readServer();

    /* 返回保存的数据，如果为空则返回NULL */
    void *returnData(qint32 type);

private:
    /*
     * 工具函数
     * 拷贝内存后把src的指针往后移动拷贝的大小
     */
    const char *p_cpymem(char *dest, const char *src, int n);

    /*
     * 数据转发
     * 当收到数据是将数据转发
     * 根据数据类型的不同进行不同的处理
     */
    void transMsgData(void *src, qint32 type);

private:
    /* 协议相关 */
    uint16_t m_port;
    QString m_addr;
    QUdpSocket m_socket;
    QHostAddress m_hostAddr;

    /* 保存数据 */
    QList<FusionTrack *> pfusions_;
    QList<SpaceAnalysis *> pspaces_;
    QList<Trajectory *> ptrajects_;
};
