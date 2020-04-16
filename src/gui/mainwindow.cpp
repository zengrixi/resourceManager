#include "mainwindow.h"

#include <QAction>
#include <QPushButton>

#include "ui_mainwindow.h"
#include "yujinview.h"
#include "zhikongview.h"
#include "lanjieview.h"

static const char *s_style_sheet_qss = ":qdarkstyle/style.qss";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), top_file_browse(nullptr), xml_map_(nullptr)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainWindow {background: white;} ");
    setWindowTitle(tr("资源调度管理软件"));

    // 设置左右窗体的比例为1:9
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 8);

    // loadStyle(); // 加载样式表文件
    initTreeWidget();     // 初始化树形面板
    initTableWidgetOne(); // 初始化反导装备资源信息窗口
    initTableWidgetTwo(); // 初始化预警系统资源状态显示窗口

    connect(ui->action_loadxml, &QAction::triggered, this, &MainWindow::loadXMLWindow);

    for (int i = 0; i < 100; i++)
    {
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化XML列表窗体
void MainWindow::createFileBrowse()
{
    FileBrowse *file_browse = new FileBrowse();
    TopWindow top_file_browse(file_browse);
    top_file_browse.setTitle(tr("选择想定文件"));
    top_file_browse.setTitleBarButtonsVisible(false, false, true);
    top_file_browse.setMinimumSize(800, 300);

    connect(file_browse, &FileBrowse::onClickOK, &top_file_browse, &TopWindow::close);
    connect(file_browse, &FileBrowse::onClickCancel, &top_file_browse, &TopWindow::close);
    top_file_browse.showModal();

    // 1、清理XML读取器
    if (xml_map_ != nullptr)
    {
        delete xml_map_;
        xml_map_ = nullptr;
    }

    // 2、关闭想定选择窗体后，获取用户选择的想定文件路径
    const QString &file_path = file_browse->getFilePath();

    // 3、读取想定文件
    if (!file_path.isEmpty())
    {
        xml_map_ = new XmlMap(file_path);
    }
}

void MainWindow::loadXMLWindow()
{
    // 生成XML浏览窗体
    createFileBrowse();

    // 读取文件夹内所有XML文件
    if (xml_map_ != nullptr)
    {
        freeResource();

        foreach (XmlMap *catalog_items, xml_map_->$("Catalog*")->c)
        {
            foreach (XmlMap *system_items, catalog_items->$("System.")->c)
            {
                const QString name = system_items->e.attribute("name");
                // 如果组节点不存在则创建组节点
                if (name.contains(QStringLiteral("雷达")))
                {
                    QStandardItem *item_radar = new QStandardItem(name); // 以后可添加图片
                    item_group_.find("预警雷达").value()->appendRow(item_radar);
                }
                else
                {
                    // 其他待续...
                }
            }
        }
    }
}

// 初始化树列表
void MainWindow::initTreeWidget()
{
    ui->tree_view->setHeaderHidden(true);                              // 隐藏表头
    ui->tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置为只读属性 不可编辑

    QStandardItemModel *model = new QStandardItemModel(ui->tree_view);
    QStandardItem *item_satellite = new QStandardItem(QStringLiteral("预警卫星")); // 以后可添加图标
    model->appendRow(item_satellite);
    QStandardItem *item_early = new QStandardItem(QStringLiteral("预警雷达")); // 以后可添加图标
    model->appendRow(item_early);
    QStandardItem *item_identify = new QStandardItem(QStringLiteral("识别雷达")); // 以后可添加图标
    model->appendRow(item_identify);
    QStandardItem *item_detection = new QStandardItem(QStringLiteral("空基探测装备")); // 以后可添加图标
    model->appendRow(item_detection);

    ui->tree_view->setModel(model);

    item_group_.insert(QStringLiteral("预警卫星"), item_satellite);
    item_group_.insert(QStringLiteral("预警雷达"), item_early);
    item_group_.insert(QStringLiteral("识别雷达"), item_identify);
    item_group_.insert(QStringLiteral("空基探测装备"), item_detection);

    // 保存类型名称
    system_type_.insert(QStringLiteral("预警卫星"), kYujin);
    system_type_.insert(QStringLiteral("预警雷达"), kYujin);
    system_type_.insert(QStringLiteral("识别雷达"), kYujin);
    system_type_.insert(QStringLiteral("空基探测装备"), kYujin);

    // TEST
    QStandardItem *item_zhikongtest = new QStandardItem(QStringLiteral("指控测试"));
    model->appendRow(item_zhikongtest);
    item_group_.insert(QStringLiteral("指控测试"), item_zhikongtest);
    system_type_.insert(QStringLiteral("指控测试"), kZhikong);

    QStandardItem *item_lanjietest = new QStandardItem(QStringLiteral("拦截测试"));
    model->appendRow(item_lanjietest);
    item_group_.insert(QStringLiteral("拦截测试"), item_lanjietest);
    system_type_.insert(QStringLiteral("拦截测试"), kLanjie);
}

// 初始化反导装备资源信息窗口
void MainWindow::initTableWidgetOne()
{
    // 初始化表格
    ui->tableWidget->setColumnCount(8);
    const QStringList table_widget_head = {QStringLiteral("资源名称"),
        QStringLiteral("资源编号"),
        QStringLiteral("授权状态"),
        QStringLiteral("装备状态"),
        QStringLiteral("通信状态"),
        QStringLiteral("位置-经度"),
        QStringLiteral("位置-纬度"),
        QStringLiteral("位置-高度")};
    ui->tableWidget->setHorizontalHeaderLabels(table_widget_head);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 表格均分窗体
    ui->tableWidget->verticalHeader()->setHidden(true);                              // 隐藏行号
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            // 设置选择模式，选择单行
    ui->tableWidget->setShowGrid(true);                                              // 设置不显示格子线
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);                                    // 去除点击表格虚线
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);                // 点击表单元时不对表头获取焦点
    QFont font = ui->tableWidget->horizontalHeader()->font();                        // 先获取字体
    font.setBold(true);                                                              // 字体设置为粗体
    ui->tableWidget->horizontalHeader()->setFont(font);                              // 设置每一列的标题字体为粗体
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             // 设置表格为只读属性 不可编辑
}

// 初始化预警系统资源状态显示窗口
void MainWindow::initTableWidgetTwo()
{
    // 初始化表格
    ui->tableWidget_2->setColumnCount(5);
    const QStringList table_widget_head = {
        QStringLiteral("时刻"), QStringLiteral("命令发布"), QStringLiteral("命令执行"), QStringLiteral("作用目标"), QStringLiteral("命令内容")};
    ui->tableWidget_2->setHorizontalHeaderLabels(table_widget_head);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 表格均分窗体
    ui->tableWidget_2->verticalHeader()->setHidden(true);                              // 隐藏行号
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);            // 设置选择模式，选择单行
    ui->tableWidget_2->setShowGrid(false);                                             // 设置不显示格子线
    ui->tableWidget_2->setFocusPolicy(Qt::NoFocus);                                    // 去除点击表格虚线
    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);                // 点击表单元时不对表头获取焦点
    QFont font = ui->tableWidget_2->horizontalHeader()->font();                        // 先获取字体
    font.setBold(true);                                                                // 字体设置为粗体
    ui->tableWidget_2->horizontalHeader()->setFont(font);                              // 设置每一列的标题字体为粗体
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);               // 设置表格为只读属性 不可编辑
}

// 加载样式表文件
void MainWindow::loadStyle()
{
    QFile file(s_style_sheet_qss);
    if (!file.exists())
    {
        MessageBox::message(tr("设置样式表失败，找不到文件！"));
    }
    else
    {
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream text_stream(&file);
        setStyleSheet(text_stream.readAll());
    }
}

// 释放资源
void MainWindow::freeResource()
{
    // 清理树结构
    // foreach (auto item, item_group_)
    // {
    //     item->clearData();
    // }

    //
}

// 树形控件被点击响应
void MainWindow::on_tree_view_clicked(const QModelIndex &index)
{
    QString str;
    str += QStringLiteral("当前选中：%1\nrow:%2,column:%3\n").arg(index.data().toString()).arg(index.row()).arg(index.column());
    str += QStringLiteral("父级：%1\n").arg(index.parent().data().toString());
    qDebug() << str;
}
void MainWindow::on_tree_view_doubleClicked(const QModelIndex &index)
{
    // 获取类型
    SystemType type = system_type_.find(index.data().toString()).value();
    //
    switch (type)
    {
        case kYujin: {
            YuJinView *yujin_view = new YuJinView;
            MessageBox::window(yujin_view, 800, 800);
            break;
        }
        case kZhikong: {
            ZhiKongView *zhikong_view = new ZhiKongView;
            MessageBox::window(zhikong_view, 800, 800);
            break;
        }
        case kLanjie: {
            LanjieView *lanjie_view = new LanjieView;
            MessageBox::window(lanjie_view, 800, 800);
            break;
        }
    }
}
