#include "lanjieview.h"
#include "ui_lanjieview.h"

static const QStringList s_treewidget_name = {"装备编号：",
    "装备名称：",
    "工作状态：",
    "战备值班等级：",
    "作战权限：",
    "指挥方式：",
    "传感器应用方式：",
    "系统运行状态：",
    "传感器资源占用百分比："};

LanjieView::LanjieView(QWidget *parent) : QWidget(parent), ui(new Ui::LanjieView)
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

LanjieView::~LanjieView()
{
    delete ui;
}
