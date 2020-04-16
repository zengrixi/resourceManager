#include "zhikongview.h"
#include "ui_zhikongview.h"

static const QStringList s_treewidget_name =
    {"装备编号：", "装备名称：", "工作方式：", "指挥方式：", "作战任务：", "拦截方式：", "频点号：", "责任扇区中心角："};

ZhiKongView::ZhiKongView(QWidget *parent) : QWidget(parent), ui(new Ui::ZhiKongView)
{
    ui->setupUi(this);
    setWindowTitle(tr("指控系统资源状态显示"));

    // 初始化表格
    ui->treeWidget->setColumnCount(2);
    for (int i = 0; i < s_treewidget_name.size(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, QStringList(s_treewidget_name.at(i)));
    }
}

ZhiKongView::~ZhiKongView()
{
    delete ui;
}
