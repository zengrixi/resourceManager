#include "yujinview.h"
#include "ui_yujinview.h"

static const QStringList s_treewidget_name = {"装备编号：",
    "装备名称：",
    "开关机：",
    "受控状态：",
    "天线扫描方式：",
    "天线机械俯仰角：",
    "波束起始扫描仰角：",
    "抗干扰措施：",
    "杂波图：",
    "电磁干扰强度：",
    "时间资源分配状态：",
    "跟踪数据率："};

YuJinView::YuJinView(QWidget *parent) : QWidget(parent), ui(new Ui::YuJinView)
{
    ui->setupUi(this);
    setWindowTitle(tr("预警系统资源状态显示"));

    // 初始化表格
    ui->treeWidget->setColumnCount(2);
    for (int i = 0; i < s_treewidget_name.size(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, QStringList(s_treewidget_name.at(i)));
    }
}

YuJinView::~YuJinView()
{
    delete ui;
}
