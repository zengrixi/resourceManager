///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： mainwindow.h
// 文件摘要： 程序的入口
// 创建作者： 曾日希
// 创建时间： 2020-04-02 10:12:16
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "messagebox.h"
#include "topwindow.h"
#include "filebrowse.h"
#include "xmlmap.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 初始化XML列表窗体
    void createFileBrowse();

public Q_SLOTS:
    void loadXMLWindow();

private:
    // 初始化树列表
    void initTreeWidget();
    // 加载样式表文件
    void loadStyle();
    // 释放资源
    void freeResource();

private:
    Ui::MainWindow *ui;

    TopWindow *top_file_browse;
    XmlMap *xml_map_; // 想定解析
    QMap<QString, QStandardItem *> item_group_;
};

#endif // MAINWINDOW_H
