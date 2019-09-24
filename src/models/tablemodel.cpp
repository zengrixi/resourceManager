#include "tablemodel.h"

#include <QLabel>
#include <QString>

#define VIEW_MAX 100 // 显示数据的最大值

class TableModel *TableModel::pModeViewTabel = nullptr;

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) { pmsg_list_ = new QList<MsgData>(); }

TableModel::~TableModel() {}

int *TableModel::get_index() { return &index_; }

QList<MsgData> *TableModel::get_msg_list() const { return pmsg_list_; }

void TableModel::set_msg_list(QList<MsgData> *pmsg_list) { pmsg_list_ = pmsg_list; }

void TableModel::update_data() {
    beginResetModel(); // 开始模型重置操作
    endResetModel();   // 完成模型重置操作
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return pmsg_list_->count();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return COL_MAX;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    int row = index.row();
    int column = index.column();
    const MsgData *data = &pmsg_list_->at(row);

    switch (role) {
        case Qt::TextColorRole:
            return QColor(Qt::white);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        case Qt::DisplayRole:
            if (column == Enum_ResourcesName)
                return data->sResourcesName;
            else if (column == Enum_ResourcesId) {
                return data->nResourcesId;
            } else if (column == Enum_AuthorizationStatus) {
                return data->bAuthStatus;
            } else if (column == Enum_EquipmentStatus) {
                return data->sEquipStatus;
            } else if (column == Enum_ComunicationStatus)
                return data->bComunStatus;
            else if (column == Enum_Longitude)
                return data->nLongitude;
            else if (column == Enum_Latitude) {
                return data->nLatitude;
            } else if (column == Enum_Height) {
                return QString::number(data->nHeight) + tr(" 米");
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
                return tr(headerText[section]);
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

void TableModel::set_data_model(QList<MsgData> *plist) {
    if (pmsg_list_->size() > VIEW_MAX - 1) pmsg_list_->pop_front();
    if (!plist->isEmpty()) {
        pmsg_list_->push_back(plist->back());
        index_ = plist->size() - 1;
    }
}
