#include "tableview.h"

#include <assert.h>
#include <math.h>
#include <time.h>

#include <QDebug>
#include <QFile>
#include <QHeaderView>
#include <QList>
#include <QPushButton>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QWheelEvent>

int xx = 0;

TableView::TableView(QWidget *parent) : QTableView(parent), phor_scrollbar_(this->horizontalScrollBar()) {
    ptabmodel_ = TableModel::get_instance(); // 创建模型
    QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setSourceModel(ptabmodel_);
    setModel(proxy_model);
    TextDelegate *pdelegate = new TextDelegate(this);
    setItemDelegate(pdelegate);

    set_sty_sheet();
}

TableView::~TableView() {}

void TableView::set_sty_sheet() {
    setSortingEnabled(true); // 设置表格可排序
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setStretchLastSection(true); // 表头设置最后一列数据填充整个控件
    horizontalHeader()->setDefaultSectionSize(150);  // 设置默认列宽
    horizontalHeader()->setMinimumHeight(40);        // 设置表头最小高度
    verticalHeader()->setVisible(false);             // 隐藏纵列表头
    setAlternatingRowColors(true);                   // 按奇偶区分颜色
    setFocusPolicy(Qt::NoFocus);                     // 去除点击表格虚线
    horizontalHeader()->setHighlightSections(false); // 点击表时不对表头获取焦点

    // 加载样式表
    load_style_sheet("./qdarkstyle/style.qss");
}

void TableView::load_style_sheet(const QString &styleSheetFile) {
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (!file.isOpen()) {
        qDebug() << "open file is faild!";
    }

    QString style_sheet = this->styleSheet();
    style_sheet += QLatin1String(file.readAll()); // 读取样式文件
    this->setStyleSheet(style_sheet);             // 把文件内容传参
    file.close();
}

void TableView::wheelEvent(QWheelEvent *e) {
    if (ptabmodel_->get_msg_list()->isEmpty()) {
        return QTableView::wheelEvent(e);
    }
    int para = e->angleDelta().y(); // 获得鼠标滚轮的滚动距离para, para<0向下滚动，>0向上滚动
    QList<MsgData> *plist = ptabmodel_->get_msg_list();
    int view_size = plist->size();
    int data_size = pmsg_list_.size();
    int *pindex = ptabmodel_->get_index();
    MsgData *pmsg = nullptr;

    if (para > 0 && phor_scrollbar_->value() == phor_scrollbar_->maximum()) {
        if (view_size - 1 != *pindex) {
            pmsg = &pmsg_list_[(*pindex)-- - view_size];
            plist->pop_back();
            plist->push_front(*pmsg);
        }
    } else if (para < 0 && phor_scrollbar_->value() == phor_scrollbar_->minimum()) {
        if (data_size - 1 != *pindex) {
            pmsg = &pmsg_list_[++(*pindex)];
            plist->pop_front();
            plist->push_back(*pmsg);
        }
    }

    ptabmodel_->update_data();

    QTableView::wheelEvent(e);
}

void TableView::add_data() {
    srand((unsigned)time(NULL));

    MsgData data;
    data.sResourcesName = QString::fromLocal8Bit("预警卫星%1").arg(xx++);
    data.nResourcesId = xx;
    data.bAuthStatus = (bool)(rand() % 2);
    data.sEquipStatus = rand() % 4;
    data.bComunStatus = (bool)(rand() % 2);
    data.nLongitude = (double)(rand() % 9999);
    data.nLatitude = (double)(rand() % 9999);
    data.nHeight = (double)(rand() % 9999);
    pmsg_list_.append(data);

    ptabmodel_->set_data_model(&pmsg_list_); // 设置数据
    ptabmodel_->update_data();
    scrollToBottom();
}

void TableView::clean_data() {
    pmsg_list_.clear();
    ptabmodel_->update_data();
}
