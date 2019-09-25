#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QVBoxLayout>

#include "src/utils/3rdParty/NXDockWidget.h"
#include "src/utils/3rdParty/NXMainWindow.h"
#include "src/utils/frameless_helper.h"
#include "src/views/tableview.h"
#include "src/views/titlebar.h"
#include "src/views/treewidget.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

protected:
    virtual void closeEvent(QCloseEvent *e) override;

private:
    void create_titlebar();
    void create_source_window_info();
    void create_source_list_info();

    // 标题栏移动操作
    void init_title_move();

private:
    TitleBar *ptitlebar_;
    QVBoxLayout *playout_;
    NXMainWindow *pcentral_window_;
    FramelessHelper *phelper_;
};
#endif // MAINWINDOW_H
