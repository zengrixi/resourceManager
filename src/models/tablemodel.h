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

#define COL_MAX 8 // 消息列表的总列数

typedef struct {
    QString sResourcesName; // 资源名称
    int nResourcesId;       // 资源编号
    bool bAuthStatus;       // 授权状态
    int sEquipStatus;       // 装备状态
    bool bComunStatus;      // 通信状态
    double nLongitude;      // 位置-经度
    double nLatitude;       // 位置-纬度
    double nHeight;         // 位置-高度
} MsgData;

// 消息类型 - 与消息数据对应
enum MsgType {
    Enum_ResourcesName = 0,
    Enum_ResourcesId,
    Enum_AuthorizationStatus,
    Enum_EquipmentStatus,
    Enum_ComunicationStatus,
    Enum_Longitude,
    Enum_Latitude,
    Enum_Height
};

// 消息头文本
const char headerText[][50] = {
    "资源名称", "资源编号", "授权状态", "装备状态", "通信状态", "位置-经度", "位置-纬度", "位置-高度",
};

class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    static class TableModel *pModeViewTabel;
    static TableModel *get_instance() {
        if (nullptr != pModeViewTabel) return pModeViewTabel;
        pModeViewTabel = new TableModel();
        assert(NULL != pModeViewTabel);
        return pModeViewTabel;
    }

    /*
     * @description: 更新消息列表
     * @param: _msgList 消息列表
     * @return:
     */
    void update_data();

    /*
     * 设置数据
     */
    void set_data_model(QList<MsgData> *pList);

    QList<MsgData> *get_msg_list() const;
    void set_msg_list(QList<MsgData> *pMsgList);

    int *get_index();

protected:
    /*
     * @description: 返回给定行数
     * @param: 当前模型索引
     * @return:
     */
    int rowCount(const QModelIndex &parent) const;

    /*
     * @description: 返回给定列数
     * @param: 当前模型索引
     * @return:
     */
    int columnCount(const QModelIndex &parent) const;

    /*
     * @description: 返回给定角色下存储的数据
     * @param:
     * @return:
     */
    QVariant data(const QModelIndex &index, int role) const;

    /*
     * @description: 返回具有指定方向的标题中给定角色的数据
     * @param:
     * @return:
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /*
     * @description: 返回给定索引的项标志
     * @param:
     * @return:
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    TableModel(QObject *parent = nullptr);
    ~TableModel();

private:
    int index_;
    QList<MsgData> *pmsg_list_;
};

#endif // MESSGELIST_H_
