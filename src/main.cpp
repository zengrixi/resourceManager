#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // 启用 Retina 高分辨率
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    MainWindow *mainwindow = new MainWindow;
    TopWindow window(mainwindow);
    window.showMaximized();
    window.show();

    return a.exec();
}
