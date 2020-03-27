#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainWindow {background: white;} ");
    setWindowTitle(tr("资源调度管理软件"));

    // 创建模态对话框
}

MainWindow::~MainWindow()
{
}