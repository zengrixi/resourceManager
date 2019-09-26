#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

MainWindow::MainWindow() {
    setWindowFlags(Qt::FramelessWindowHint);
    //    setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(1024, 768);

    // 添加背景图
    nine_patch_painter_ = new NinePatchPainter(QPixmap(":/Dock/resources/background.png"), 23, 12, 23, 33);

    // 添加样式
    this->setObjectName("mainwindow");

    central_window_ = new NXMainWindow();
    layout_ = new QVBoxLayout(this);

    // 创建自定义窗体
    create_titlebar();
    // 标题栏可拖动操作
    init_title_move();
    layout_->addWidget(central_window_);

    //创建子窗体
    create_source_window_info();
    create_source_list_info();

    //...
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
    central_window_->setLayout(layout_);
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *e) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0.7);
    animation->start();

    switch (QMessageBox::information(this, tr("提示"), tr("是否关闭？"), tr("确认"), tr("返回"), Q_NULLPTR, 1)) {
        case 0: {
            e->accept();
            exit(0);
        }
        case 1:
        default: {
            animation->setDuration(500);
            animation->setStartValue(0.5);
            animation->setEndValue(1);
            animation->start();
            e->ignore();
            break;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    nine_patch_painter_->paint(&painter, rect()); // 九宫格绘制
}

void MainWindow::create_titlebar() {
    titlebar_ = new TitleBar(this);
    installEventFilter(titlebar_);
    this->setWindowIcon(QIcon(":qss_icons/rc/LOGO.png"));
    this->setWindowTitle(tr("资源调度管理软件"));
    layout_->addWidget(titlebar_);
}

void MainWindow::create_source_window_info() {
    NXDockWidget *tab_dock = new NXDockWidget(tr("资源信息显示窗口"));
    central_window_->addDockWidget(Qt::BottomDockWidgetArea, tab_dock);
    TableView *tab_view = new TableView(this);
    tab_dock->setWidget(tab_view);
}

void MainWindow::create_source_list_info() {
    NXDockWidget *tree_dock = new NXDockWidget(tr("资源列表显示窗体"));
    central_window_->addDockWidget(Qt::LeftDockWidgetArea, tree_dock);
    TreeWidget *tree_wid = new TreeWidget(central_window_);
    QTreeWidgetItem *tree_item = tree_wid->add_root_node(tr("预警卫星"));
    tree_wid->add_child_node(tree_item, tr("预警卫星1"));
    tree_dock->setWidget(tree_wid);
}

void MainWindow::init_title_move() {
    helper_ = new FramelessHelper(this);
    helper_->activate_on(this);
    helper_->set_title_height(35);
    helper_->set_widget_movable(true);
    helper_->set_widget_esizable(true);
    helper_->set_ubber_band_on_move(true);
    helper_->set_rubber_band_on_resize(true);
}
