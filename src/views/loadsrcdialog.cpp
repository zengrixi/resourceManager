#include "loadsrcdialog.h"

LoadSrcDialog::LoadSrcDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // 添加背景图
    nine_patch_painter_ = new NinePatchPainter(QPixmap(":/Dock/resources/top-window-shadow.png"), 23, 12, 23, 33);
}

void LoadSrcDialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    nine_patch_painter_->paint(&painter, rect()); // 九宫格绘制
}
