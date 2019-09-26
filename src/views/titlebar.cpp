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
    icon_label_ = new QLabel(this);
    title_label_ = new QLabel(this);
    minimize_btn_ = new QPushButton(this);
    maximize_btn_ = new QPushButton(this);
    close_button_ = new QPushButton(this);

    /* 设置标题栏图标控件 */
    icon_label_->setFixedSize(ICON_W, ICON_H);
    icon_label_->setScaledContents(true);

    /* 设置标题栏文本控件 */
    title_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    title_label_->setAlignment(Qt::AlignCenter);

    /* 设置标题栏按钮控件 */
    minimize_btn_->setFixedSize(BTN_W, BTN_H);
    maximize_btn_->setFixedSize(BTN_W, BTN_H);
    close_button_->setFixedSize(BTN_W, BTN_H);

    /* 设置各种对象名称 */
    title_label_->setObjectName("whiteLabel");
    minimize_btn_->setObjectName("minimizeButton");
    maximize_btn_->setObjectName("maximizeButton");
    close_button_->setObjectName("closeButton");

    /* 设置标题栏按钮的提示文本 */
    minimize_btn_->setToolTip(tr("最小化"));
    maximize_btn_->setToolTip(tr("最大化"));
    close_button_->setToolTip(tr("关闭"));

    /* 设置控件布局 */
    layout_ = new QHBoxLayout(this);
    layout_->addWidget(icon_label_);
    layout_->addSpacing(5);
    layout_->addWidget(title_label_);
    layout_->addWidget(minimize_btn_);
    layout_->addWidget(maximize_btn_);
    layout_->addWidget(close_button_);
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
    setLayout(layout_);

    connect(minimize_btn_, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(maximize_btn_, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(close_button_, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event);

    emit maximize_btn_->clicked();
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
        case QEvent::WindowTitleChange: {
            QWidget *widget = qobject_cast<QWidget *>(obj);
            if (widget) {
                title_label_->setText(widget->windowTitle());
                return true;
            }
        }
        case QEvent::WindowIconChange: {
            QWidget *widget = qobject_cast<QWidget *>(obj);
            if (widget) {
                QIcon icon = widget->windowIcon();
                icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
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
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QWidget *window = this->window();
    if (window->isWindow()) {
        if (button == minimize_btn_)
            window->showMinimized();
        else if (button == maximize_btn_)
            window->isMaximized() ? window->showNormal() : window->showMaximized();
        else if (button == close_button_)
            window->close();
    }
}

void TitleBar::update_maximize() {
    QWidget *window = this->window();
    if (window->isWindow()) {
        bool bmaximize = window->isMaximized();
        if (bmaximize) {
            maximize_btn_->setToolTip("还原");
            maximize_btn_->setProperty("maximizeProperty", "restore");
        } else {
            maximize_btn_->setProperty("maximizeProperty", "maximize");
            maximize_btn_->setToolTip("最大化");
        }

        maximize_btn_->setStyle(QApplication::style());
    }
}
