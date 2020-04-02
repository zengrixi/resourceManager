#include "mainwindow.h"

#include <QAction>
#include <QPushButton>

#include "ui_mainwindow.h"

static constexpr char *s_style_sheet_qss = ":qdarkstyle/style.qss";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), top_file_browse(nullptr), xml_map_(nullptr)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainWindow {background: white;} ");
    setWindowTitle(tr("资源调度管理软件"));

    // 设置左右窗体的比例为1:9
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 9);

    // loadStyle(); // 加载样式表文件
    initTreeWidget();

    connect(ui->action_loadxml, &QAction::triggered, this, &MainWindow::loadXMLWindow);
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

    // 关闭想定选择窗体后，获取用户选择的想定文件路径
    const QString &file_path = file_browse->getFilePath();
    if (!file_path.isEmpty())
    {
        if (xml_map_ != nullptr)
        {
            delete xml_map_;
        }
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
                    item_radar->setFlags(item_radar->flags() & (~Qt::ItemIsEditable)); // 设置不可编辑
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
    ui->tree_view->setHeaderHidden(true); // 隐藏表头

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

    // 设置item的属性
    foreach (auto item, item_group_)
    {
        item->setFlags(item->flags() & (~Qt::ItemIsEditable)); // 设置不可编辑
    }
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
