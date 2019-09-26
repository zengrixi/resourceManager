#ifndef MESSGELIST_H_
#define MESSGELIST_H_

#include <assert.h>

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QVariant>
#include <QWidget>

#include "src/models/datamodel.h"

// 消息类型 - 与消息数据对应
enum MsgType {
    ResourcesName = 0,
    ResourcesId,
    ResourcesType,
    AuthorizationStatus,
    EquipmentStatus,
    ComunicationStatus,
    Longitude,
    Latitude,
    Height,
    Count
};

// 消息头文本
static const QStringList head_title = {"资源名称", "资源编号",  "资源类型",  "授权状态",  "装备状态",
                                       "通信状态", "位置-经度", "位置-纬度", "位置-高度", "目标数目"};

static const QStringList resource_type = {"预警卫星", "预警雷达", "识别雷达", "空基探测", "中段阵地", "末高阵地"};

static const QStringList auth_status = {"未授权", "已授权"};

static const QStringList equi_status = {"待机", "准备", "正常运行", "故障"};

static const QStringList commun_status = {"未通信", "正在通信"};

class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    ~TableModel();
    void update_data();

    void set_data_model(TargetDataModel *pList);

    QVector<TargetData *> *get_msg_list() const;
    void set_msg_list(TargetDataModel *pMsgList);

    int *get_index();

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    int cow_max_;
    int index_;
    TargetDataModel *data_list_;
};

#endif // MESSGELIST_H_
