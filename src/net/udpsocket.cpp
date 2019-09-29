#include "cudpsocket.h"

CUdpSocket *CUdpSocket::pInstance = NULL;

void *pdata = NULL;

CUdpSocket::CUdpSocket()
{
    
}

CUdpSocket *CUdpSocket::getInstance()
{
	if (!pInstance)
		pInstance = new CUdpSocket();
	return pInstance;
}

CUdpSocket::~CUdpSocket()
{
}

bool CUdpSocket::bindServer(QString addr, quint32 port)
{
	m_hostAddr.setAddress(addr);
	bool bPort = m_socket.bind(QHostAddress::AnyIPv4,
		port, QUdpSocket::ReuseAddressHint);
	bool bAddr = m_socket.joinMulticastGroup(m_hostAddr);

	if (bPort && bAddr)
	{
		qDebug() <<	QObject::tr("bind sucess");
		m_socket.setSocketOption(
			QAbstractSocket::ReceiveBufferSizeSocketOption,
			1024 * 1024);
		connect(&m_socket, SIGNAL(readyRead()),
			this, SLOT(readServer()));
		return true;
	}

	qDebug() << QObject::tr("bind error");
	return false;
}

void CUdpSocket::processData(QString data, qint32 size)
{
	quint32 msg_type;
	const char *buf;

	buf = data.toStdString().c_str();

lpanaly:
	// 1. 解析协议头拿到报文的类型
	msg_type = analyHead(buf, size);

	// 2. 根据消息类型获取消息体结构
	switch (msg_type)
	{
	case msg_fusion_track: // 综合航迹
	{
		buf = analyFusionTrack(buf, size);
		if (buf) goto lpanaly;
		break;
	}
	case msg_space_analysis:
	{
		buf = analySpaceAnalysis(buf, size);
		if (buf) goto lpanaly;
		break;
	}
	case msg_trajectory:
	{
		buf = analyTrajectory(buf, size);
		if (buf) goto lpanaly;
		break;
	}
	default:
		break;
	}

	buf = NULL;
}

quint32 CUdpSocket::analyHead(QString data, qint32 size)
{
	PKGhead  pkg_head;
	quint32 head_size;

	head_size = sizeof(pkg_head);
	if (size < head_size) return 0;
	memcpy(&pkg_head, data.toStdString().c_str(), head_size);

	return pkg_head.msg_type;
}

const char *CUdpSocket::analyFusionTrack(QString data, qint32 size)
{
	FusionTrack *pfusion = new FusionTrack();
	const char *buf;
	char *point, *dest;
	int len;
	int n_size;

	// 1. 获取名称前面数据
	n_size = size; // 记录数据大小
	buf    = data.toStdString().c_str();
	point  = (char *)pfusion;
	dest   = (char *)& pfusion->target_name;
	len    = dest - point;
	buf    = p_cpymem(point, buf, len);

	// 2. 根据名称长度获取名称
	if (pfusion->num1)
	{
	}
	else
	{
		pfusion->target_name = NULL;
	}
	buf += pfusion->num1;

	// 3. 获取名字后面的两个数据
	point = (char *)& pfusion->source_id;
	buf   = p_cpymem(point, buf, 0);

	// 4. 获取最后两个数据
	if (pfusion->num2 == 38)
	{
		buf += pfusion->num2 * 4 - 4;
	}
	else
	{
		pfusion->cov_matrix = NULL;
	}
	dest = (char *)& pfusion->father_id;
	buf  = p_cpymem(dest, buf, 4);

	// 5. 保存数据
	transMsgData((void *)pfusion, msg_fusion_track);

	// 6. 收尾工作
	if (buf - data.toStdString().c_str() < n_size)
		return buf;
	return NULL;
}

const char *CUdpSocket::analySpaceAnalysis(QString data, qint32 size)
{
	SpaceAnalysis *pspace = new SpaceAnalysis();
	const char *buf;
	char *point, *dest;
	int len;
	int n_size;

	// 1. 获取二次拦截索引序列前面的数据
	n_size = size;
	buf    = data.toStdString().c_str();
	point  = (char *)pspace;
	dest   = (char *)& pspace->second_index_seq;
	len    = dest - point;
	buf    = p_cpymem(point, dest, len);

	// 2. 根据num1获取二次拦截索引序列
	if (pspace->num1)
	{
		buf += pspace->num1 * 4 - 1;
	}
	else
	{
		pspace->second_index_seq = NULL;
	}

	// 3. 获取num2的数据，然后根据num2获取可拦截段内拦截概率序列(0-1)
	point = (char *)& pspace->num2;
	buf   = p_cpymem(point, buf, 4);
	if (pspace->num2)
	{
		buf += pspace->num2 * 8 - 8;
	}
	else
	{
		pspace->intercept_prob_seq = NULL;
	}

	// 4. 获取后面的数据
	point = (char *)& pspace->cross_point;
	dest  = (char *)& pspace->remained_time + 8;
	buf   = p_cpymem(point, buf, dest - point);

	// 5. 保存数据
	transMsgData((void *)pspace, msg_space_analysis);

	// 6. 收尾工作
	if (buf - data.toStdString().c_str() < n_size) return buf;
	return NULL;
}

const char *CUdpSocket::analyTrajectory(QString data, qint32 size)
{
	Trajectory *ptraject = new Trajectory();
	const char *buf;
	char  *point, *dest;
	int   len;
	int   n_size;

	// 1. 获取二次拦截索引序列前面的数据
	n_size = size;
	buf    = data.toStdString().c_str();
	point  = (char *)ptraject;
	dest   = (char *)& ptraject->points;
	len    = dest - point;
	buf    = p_cpymem(point, buf, len);

	// 2. 根据num获取轨迹点
	if (ptraject->num)
	{
		ptraject->points = new Point[ptraject->num];
		buf = p_cpymem((char *)ptraject->points, buf, ptraject->num * sizeof(Point));
	}
	else
	{
		ptraject->points = NULL;
	}

	// 3. 保存数据
	transMsgData((void *)ptraject, msg_trajectory);

	// 4. 收尾工作
	if (buf - data.toStdString().c_str() < n_size)
		return buf;

	return NULL;
}

const char *CUdpSocket::p_cpymem(char *dest, const char *src, int n)
{
	memcpy(dest, src, n);
	return src + n;
}

void CUdpSocket::transMsgData(void *src, qint32 type)
{
	switch (type)
	{
	case msg_fusion_track:
	{
        //互斥...
		pfusions_.append((FusionTrack *)src);
        break;
	}
	case msg_space_analysis:
	{
		pspaces_.append((SpaceAnalysis *)src);
		break;
	}
	case msg_trajectory:
	{
		ptrajects_.append((Trajectory *)src);
		break;
	}
	default:
		break;
	}
}

void CUdpSocket::readServer()
{
	QByteArray array;

	while (m_socket.hasPendingDatagrams())
	{
		array.resize(m_socket.pendingDatagramSize());
		m_socket.readDatagram(array.data(), array.size());

		processData(array.data(), array.size()); // 处理数据
	}
}

void *CUdpSocket::returnData(qint32 type)
{
    switch ( type )
    {
        case msg_fusion_track :
            if ( !pfusions_.empty() )
            {
				pdata = (void *)pfusions_[0];
				pfusions_.pop_front();
                return pdata;
            }
            break;

        case msg_space_analysis :
            if ( !pspaces_.empty() )
            {
				pdata = (void *)pspaces_[0];
				pspaces_.pop_front();
				return pdata;
            }
            break;

        case msg_trajectory :
            if ( !ptrajects_.empty() )
            {
				pdata = (void *)ptrajects_[0];
				ptrajects_.pop_front();
				return pdata;
            }
            break;

        default:
            ;
            break;
    }

    return NULL;
}