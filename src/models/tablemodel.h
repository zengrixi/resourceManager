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
    QStringList head_title;
    QStringList resource_type;
    QStringList auth_status;
    QStringList equi_status;
    QStringList commun_status;
    int cow_max_;
    int index_;
    TargetDataModel *data_list_;
};

#endif // MESSGELIST_H_
