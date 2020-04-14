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
#include <QGridLayout>

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
    enum SystemType
    {
        kYujin,
        kZhikong,
        kLanjie
    };
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 初始化XML列表窗体
    void createFileBrowse();

public Q_SLOTS:
    void loadXMLWindow();

private Q_SLOTS:
    // 树形控件被点击响应
    void on_tree_view_clicked(const QModelIndex &index);
    // 树形控件被双击
    void on_tree_view_doubleClicked(const QModelIndex &index);

private:
    // 初始化树列表
    void initTreeWidget();
    // 初始化反导装备资源信息窗口
    void initTableWidgetOne();
    // 初始化预警系统资源状态显示窗口
    void initTableWidgetTwo();
    // 加载样式表文件
    void loadStyle();
    // 释放资源
    void freeResource();

private:
    Ui::MainWindow *ui;

    TopWindow *top_file_browse;
    XmlMap *xml_map_; // 想定解析

    // 树形窗口
    QMap<QString, QStandardItem *> item_group_;
    QMap<QString, SystemType> system_type_; // 根据名称获取系统类型

    // 反导装备资源信息窗口

    // 预警系统资源状态显示
};

#endif // MAINWINDOW_H
