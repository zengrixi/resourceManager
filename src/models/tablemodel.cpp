#include "tablemodel.h"

#include <QLabel>
#include <QString>

#define VIEW_MAX 100 // 显示数据的最大值

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) {
    // 消息头文本
    head_title << "资源名称"
               << "资源编号"
               << "资源类型"
               << "授权状态"
               << "装备状态"
               << "通信状态"
               << "位置-经度"
               << "位置-纬度"
               << "位置-高度"
               << "目标数目";
    resource_type << "预警卫星"
                  << "预警雷达"
                  << "识别雷达"
                  << "空基探测"
                  << "中段阵地"
                  << "末高阵地";
    auth_status << "未授权"
                << "已授权";
    equi_status << "待机"
                << "准备"
                << "正常运行"
                << "故障";
    commun_status << "未通信"
                  << "正在通信";

    cow_max_ = head_title.size();
    data_list_ = new TargetDataModel();
}

TableModel::~TableModel() {}

int *TableModel::get_index() { return &index_; }

QVector<TargetData *> *TableModel::get_msg_list() const { return &data_list_->target_list; }

void TableModel::set_msg_list(TargetDataModel *msg_list) { data_list_ = msg_list; }

void TableModel::update_data() {
    beginResetModel(); // 开始模型重置操作
    endResetModel();   // 完成模型重置操作
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return data_list_->target_list.count();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return cow_max_;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    int row = index.row();
    int column = index.column();
    const TargetData *data = data_list_->target_list[row];

    switch (role) {
        case Qt::TextColorRole:
            return QColor(Qt::white);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        case Qt::DisplayRole:
            if (column == ResourcesName)
                return data->id;
            else if (column == ResourcesId) {
                if (data->title == nullptr) {
                    return "";
                } else {
                    return "";
                }
            } else if (column == ResourcesType) {
                return resource_type.at(data->type);
            } else if (column == AuthorizationStatus) {
                return auth_status.at(data->auth_status);
            } else if (column == EquipmentStatus) {
                return equi_status.at(data->equi_status);
            } else if (column == ComunicationStatus)
                return commun_status.at(data->commun_status);
            else if (column == Longitude)
                return data->pos_x;
            else if (column == Latitude) {
                return data->pos_y;
            } else if (column == Height) {
                return QString::number(data->pos_z) + tr(" 米");
            } else if (Count) {
                return data->count;
            }

            return "";

        default:
            return QVariant();
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        case Qt::DisplayRole:
            if (orientation == Qt::Horizontal) {
                return head_title[section];
            }
        default:
            return QVariant();
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return QAbstractTableModel::flags(index);

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void TableModel::set_data_model(TargetDataModel *list) {
    QVector<TargetData *> data = list->target_list;
    int size = data.size();
    if (size > VIEW_MAX - 1) data.pop_front();
    if (!data.isEmpty()) {
        data.push_back(data.back());
        index_ = data.size() - 1;
    }
}
