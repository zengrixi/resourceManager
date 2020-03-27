#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "messagebox.h"
#include "topwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
};
#endif // MAINWINDOW_H
