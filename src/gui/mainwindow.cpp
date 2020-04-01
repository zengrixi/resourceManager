#include "mainwindow.h"

#include <QAction>
#include <QPushButton>

#include "xmlmap.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), top_file_browse(nullptr)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainWindow {background: white;} ");
    setWindowTitle(tr("资源调度管理软件"));

    // 设置左右窗体的比例为1:9
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 9);

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

    // 关闭想定选择窗体后，获取用户选择的想定文件信息
}

// 读取想定文件
bool MainWindow::loadXML(const QString &file_path)
{
    XmlMap *root_xml = new XmlMap(file_path);

    if (root_xml == nullptr)
    {
        return false;
    }

    // 获取xml中的内容并创建树形面板
}

void MainWindow::loadXMLWindow()
{
    // 生成XML浏览窗体
    createFileBrowse();

    // 读取文件夹内所有XML文件

    // 添加条目
}