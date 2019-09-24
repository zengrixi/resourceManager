#include "titlebar.h"

#include <QApplication>
#include <QEvent>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

#define BTN_W title_height_
#define BTN_H title_height_
#define ICON_W title_height_
#define ICON_H title_height_

TitleBar::TitleBar(QWidget *parent) : QWidget(parent), title_height_(35) {
    setFixedHeight(title_height_);

    init_control();
}

TitleBar::~TitleBar() {}

void TitleBar::init_control() {
    /* 初始化控件 */
    picon_label_ = new QLabel(this);
    ptitle_label_ = new QLabel(this);
    pminimize_btn_ = new QPushButton(this);
    pmaximize_btn_ = new QPushButton(this);
    pclose_button_ = new QPushButton(this);

    /* 设置标题栏图标控件 */
    picon_label_->setFixedSize(ICON_W, ICON_H);
    picon_label_->setScaledContents(true);

    /* 设置标题栏文本控件 */
    ptitle_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ptitle_label_->setAlignment(Qt::AlignCenter);

    /* 设置标题栏按钮控件 */
    pminimize_btn_->setFixedSize(BTN_W, BTN_H);
    pmaximize_btn_->setFixedSize(BTN_W, BTN_H);
    pclose_button_->setFixedSize(BTN_W, BTN_H);

    /* 设置各种对象名称 */
    ptitle_label_->setObjectName("whiteLabel");
    pminimize_btn_->setObjectName("minimizeButton");
    pmaximize_btn_->setObjectName("maximizeButton");
    pclose_button_->setObjectName("closeButton");

    /* 设置标题栏按钮的提示文本 */
    pminimize_btn_->setToolTip(tr("最小化"));
    pmaximize_btn_->setToolTip(tr("最大化"));
    pclose_button_->setToolTip(tr("关闭"));

    /* 设置控件布局 */
    playout_ = new QHBoxLayout(this);
    playout_->addWidget(picon_label_);
    playout_->addSpacing(5);
    playout_->addWidget(ptitle_label_);
    playout_->addWidget(pminimize_btn_);
    playout_->addWidget(pmaximize_btn_);
    playout_->addWidget(pclose_button_);
    playout_->setSpacing(0);
    playout_->setContentsMargins(5, 0, 5, 0);
    setLayout(playout_);

    connect(pminimize_btn_, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(pmaximize_btn_, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(pclose_button_, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event);

    emit pmaximize_btn_->clicked();
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
        case QEvent::WindowTitleChange: {
            QWidget *pwidget = qobject_cast<QWidget *>(obj);
            if (pwidget) {
                ptitle_label_->setText(pwidget->windowTitle());
                return true;
            }
        }
        case QEvent::WindowIconChange: {
            QWidget *pwidget = qobject_cast<QWidget *>(obj);
            if (pwidget) {
                QIcon icon = pwidget->windowIcon();
                picon_label_->setPixmap(icon.pixmap(picon_label_->size()));
                return true;
            }
        }
        case QEvent::WindowStateChange:
        case QEvent::Resize:
            update_maximize();
            return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::on_clicked() {
    QPushButton *pbutton = qobject_cast<QPushButton *>(sender());
    QWidget *pwindow = this->window();
    if (pwindow->isWindow()) {
        if (pbutton == pminimize_btn_)
            pwindow->showMinimized();
        else if (pbutton == pmaximize_btn_)
            pwindow->isMaximized() ? pwindow->showNormal() : pwindow->showMaximized();
        else if (pbutton == pclose_button_)
            pwindow->close();
    }
}

void TitleBar::update_maximize() {
    QWidget *pwindow = this->window();
    if (pwindow->isWindow()) {
        bool bmaximize = pwindow->isMaximized();
        if (bmaximize) {
            pmaximize_btn_->setToolTip("还原");
            pmaximize_btn_->setProperty("maximizeProperty", "restore");
        } else {
            pmaximize_btn_->setProperty("maximizeProperty", "maximize");
            pmaximize_btn_->setToolTip("最大化");
        }

        pmaximize_btn_->setStyle(QApplication::style());
    }
}
