#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QVBoxLayout>

#include "src/utils/3rdParty/NXMainWindow.h"
#include "src/utils/frameless_helper.h"
#include "src/views/titlebar.h"

class MainWindow : public NXMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

protected:
    virtual void closeEvent(QCloseEvent *e) override;

private:
    void create_titlebar();
    void create_menubar();
    void create_toolbar();

    // 标题栏移动操作
    void init_title_move();

private:
    TitleBar *ptitlebar_;
    QVBoxLayout *playout_;
    QWidget *pcentral_window_;
    FramelessHelper *phelper_;
};
#endif // MAINWINDOW_H
