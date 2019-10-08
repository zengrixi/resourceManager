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
#include <QTimer>
#include <QWheelEvent>

TableView::TableView(QWidget *parent) : QTableView(parent), hor_scrollbar_(this->horizontalScrollBar()) {
    tabmodel_ = new TableModel(this); // 创建模型
    QSortFilterProxyModel *roxy_model = new QSortFilterProxyModel(this);
    roxy_model->setSourceModel(tabmodel_);
    setModel(roxy_model);
    TextDelegate *delegate = new TextDelegate(this);
    setItemDelegate(delegate);

    set_sty_sheet();

    //开启测试
    QTimer *test_add_data = new QTimer();
    connect(test_add_data, SIGNAL(timeout()), this, SLOT(add_data()));
    test_add_data->start(2000);
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
    QList<TargetData> *list = tabmodel_->get_msg_list();

    if (list->isEmpty()) {
        return QTableView::wheelEvent(e);
    }

    int para = e->angleDelta().y(); // 获得鼠标滚轮的滚动距离para, para<0向下滚动，>0向上滚动
    int view_size = list->size();
    int data_size = data_list_.size();
    int *index = tabmodel_->get_index();
    TargetData *data = nullptr;

    if (para > 0 && hor_scrollbar_->value() == hor_scrollbar_->maximum()) {
        if (view_size - 1 != *index) {
            data = &data_list_[(*index)-- - view_size];
            list->pop_back();
            list->push_front(*data);
        }
    } else if (para < 0 && hor_scrollbar_->value() == hor_scrollbar_->minimum()) {
        if (data_size - 1 != *index) {
            data = &data_list_[++(*index)];
            list->pop_front();
            list->push_back(*data);
        }
    }

    tabmodel_->update_data();

    QTableView::wheelEvent(e);
}

void TableView::add_data() {
    srand((unsigned)time(NULL));

    TargetData data;
    data.title = new char[10];
    strcpy(data.title, "预警雷达");
    data.id = new char[5];
    strcpy(data.id, "1");
    data.type = rand() % 6;
    data.auth_status = rand() % 2;
    data.equi_status = rand() % 4;
    data.commun_status = rand() % 2;
    data.pos_x = rand() % 100;
    data.pos_y = rand() % 100;
    data.pos_z = rand() % 100;
    data.count = rand() % 1000;

    data_list_.append(data);

    tabmodel_->set_data_model(&data_list_); // 设置数据
    tabmodel_->update_data();
    scrollToBottom();
}

void TableView::clean_data() {
    data_list_.clear();
    tabmodel_->update_data();
}
