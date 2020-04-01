#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "messagebox.h"
#include "topwindow.h"
#include "filebrowse.h"

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

    // 读取想定文件
    bool loadXML(const QString &file_path);

public Q_SLOTS:
    void loadXMLWindow();

private:
    Ui::MainWindow *ui;

    TopWindow *top_file_browse;
};

#endif // MAINWINDOW_H
