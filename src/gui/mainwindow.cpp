#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainWindow {background: white;} ");
    setWindowTitle(tr("资源调度管理软件"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
