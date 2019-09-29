#include "UdpSocket.h"

UdpSocket *UdpSocket::pInstance = NULL;

void *pdata = NULL;

UdpSocket::UdpSocket() {}

UdpSocket *UdpSocket::getInstance() {
    if (!pInstance) pInstance = new UdpSocket();
    return pInstance;
}

UdpSocket::~UdpSocket() {}

bool UdpSocket::bindServer(QString addr, quint32 port) {
    m_hostAddr.setAddress(addr);
    bool bPort = m_socket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ReuseAddressHint);
    bool bAddr = m_socket.joinMulticastGroup(m_hostAddr);

    if (bPort && bAddr) {
        qDebug() << QObject::tr("bind sucess");
        m_socket.setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024);
        connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readServer()));
        return true;
    }

    qDebug() << QObject::tr("bind error");
    return false;
}

void UdpSocket::processData(QString data, qint32 size) {}

void UdpSocket::readServer() {
    QByteArray array;

    while (m_socket.hasPendingDatagrams()) {
        array.resize(m_socket.pendingDatagramSize());
        m_socket.readDatagram(array.data(), array.size());

        processData(array.data(), array.size()); // 处理数据
    }
}
