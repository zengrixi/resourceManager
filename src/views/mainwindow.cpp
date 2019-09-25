#include "mainwindow.h"

MainWindow::MainWindow() {
    pcentral_window_ = new NXMainWindow();
    playout_ = new QVBoxLayout(this);

    // 创建自定义窗体
    create_titlebar();
    // 标题栏可拖动操作
    init_title_move();
    playout_->addWidget(pcentral_window_);

    //创建子窗体
    create_source_info_window();

    //...
    playout_->addSpacing(0);
    pcentral_window_->setLayout(playout_);
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

void MainWindow::create_titlebar() {
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    ptitlebar_ = new TitleBar(this);
    installEventFilter(ptitlebar_);
    this->setWindowIcon(QIcon(":qss_icons/rc/LOGO.png"));
    this->setWindowTitle(tr("资源调度管理软件"));
    playout_->addWidget(ptitlebar_);
}

void MainWindow::create_source_info_window() {
    NXDockWidget *tab_dock = new NXDockWidget(tr("资源信息显示窗口"));
    pcentral_window_->addDockWidget(Qt::BottomDockWidgetArea, tab_dock);
    TableView *tab_view = new TableView(this);
    tab_dock->setWidget(tab_view);
}

void MainWindow::init_title_move() {
    phelper_ = new FramelessHelper(this);
    phelper_->activate_on(this);
    phelper_->set_title_height(35);
    phelper_->set_widget_movable(true);
    phelper_->set_widget_esizable(true);
    phelper_->set_ubber_band_on_move(true);
    phelper_->set_rubber_band_on_resize(true);
}
