#include "mainwindow.h"

MainWindow::MainWindow() {
    pcentral_window_ = new QWidget(this);
    this->setCentralWidget(pcentral_window_);
    playout_ = new QVBoxLayout(pcentral_window_);

    // 创建自定义窗体
    create_titlebar();
    create_menubar();
    create_toolbar();

    // 标题栏可拖动操作
    init_title_move();

    //...
    playout_->addSpacing(0);
    playout_->addStretch(0);
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
    this->setWindowTitle(tr("装备显控软件"));
    playout_->addWidget(ptitlebar_);
}

void MainWindow::create_menubar() {
    QMenuBar *menubar = this->menuBar();
    playout_->addWidget(reinterpret_cast<QWidget *>(menubar));

    //...
}

void MainWindow::create_toolbar() { playout_->addWidget(reinterpret_cast<QWidget *>(ui.mainToolBar)); }

void MainWindow::init_title_move() {
    phelper_ = new FramelessHelper(this);
    phelper_->activate_on(this);
    phelper_->set_title_height(35);
    phelper_->set_widget_movable(true);
    phelper_->set_widget_esizable(true);
    phelper_->set_ubber_band_on_move(true);
    phelper_->set_rubber_band_on_resize(true);
}
