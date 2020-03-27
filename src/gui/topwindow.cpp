#include "ui_topwindow.h"
#include "topwindow.h"

#include <QDebug>
#include <QSizeGrip>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>

#include "ninepatchpainter.h"

class TopWindowPrivate
{
public:
    TopWindowPrivate(const QMargins &window_paddings,
        const QMargins &border_image_borders,
        const QString &border_image_path,
        bool border_image_horizontal_stretch,
        bool border_image_vertical_stretch)
    {
        nine_patch_painter_ = new NinePatchPainter(QPixmap(border_image_path),
            border_image_borders.left(),
            border_image_borders.top(),
            border_image_borders.right(),
            border_image_borders.bottom(),
            border_image_horizontal_stretch,
            border_image_vertical_stretch);
        size_grip_ = new QSizeGrip(nullptr);
        padding = window_paddings;
    }

    NinePatchPainter *nine_patch_painter_; // 九宫格绘图工具类
    QPoint window_position_before_moving_; // 移动窗口前窗口左上角的坐标
    QPoint mouse_pressed_position_;        // 按下鼠标时鼠标的全局坐标
    QSizeGrip *size_grip_;                 // 修改窗口大小的 handle
    QMargins padding;                      // 窗口的 padding
    bool resizable = true;                 // 默认是可以缩放窗口的
};

TopWindow::TopWindow(QWidget *central_widget,
    const QMargins &window_paddings,
    const QMargins &border_image_borders,
    const QString &border_image_path,
    bool border_image_horizontal_stretch,
    bool border_image_vertical_stretch)
    : ui(new Ui::TopWindow)
{
    ui->setupUi(this);
    ui->restore_button->hide();
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    d_ = new TopWindowPrivate(
        window_paddings, border_image_borders, border_image_path, border_image_horizontal_stretch, border_image_vertical_stretch);

    // 去掉 padding 和 spacing
    QGridLayout *l = qobject_cast<QGridLayout *>(layout());
    l->setSpacing(0);
    l->setContentsMargins(d_->padding);

    // 替换 central widget
    central_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delete l->replaceWidget(ui->central_widget, central_widget);
    delete ui->central_widget;
    setTitle(central_widget->windowTitle()); // 默认使用 central_widget 的标题

    // 添加 size grip 到窗口右下角
    l->addWidget(d_->size_grip_, 1, 0, Qt::AlignRight | Qt::AlignBottom);

    // 信号槽事件处理
    handleEvents();
}

TopWindow::~TopWindow()
{
    delete ui;
    delete d_;
}

// 设置窗口的标题
void TopWindow::setTitle(const QString &title)
{
    ui->title_label->setText(title);
}

// 使用自定义的标题栏 (会隐藏默认的标题栏)
void TopWindow::setTitleBar(QWidget *titleBar)
{
    ui->title_bar->hide();
    delete layout()->replaceWidget(ui->title_bar, titleBar);
}

// 设置是否显示标题栏
void TopWindow::setTitleBarVisible(bool visible)
{
    ui->title_bar->setVisible(visible);
}

// 设置是否显示最小化，最大化，关闭按钮
void TopWindow::setTitleBarButtonsVisible(bool min, bool max, bool close)
{
    ui->min_button->setVisible(min);
    ui->max_button->setVisible(max);
    ui->close_button->setVisible(close);
}

// 设置是否可以修改窗口的大小，默认为可以修改窗口大小
void TopWindow::setResizable(bool resizable)
{
    d_->resizable = resizable;
    d_->size_grip_->setVisible(resizable);
}

// 最大化窗口
void TopWindow::showMaximized()
{
    // 最大化窗口时不需要阴影，所以去掉窗口的 padding
    // 隐藏最大化按钮
    // 显示恢复按钮
    // 隐藏 size_grip_

    layout()->setContentsMargins(0, 0, 0, 0);
    ui->max_button->hide();
    ui->restore_button->show();
    d_->size_grip_->setVisible(false);

    QWidget::showMaximized();
}

void TopWindow::showNormal()
{
    layout()->setContentsMargins(d_->padding); // 恢复窗口大小时显示阴影，所以加上窗口的 padding
    ui->max_button->show();
    ui->restore_button->hide();
    d_->size_grip_->setVisible(d_->resizable);

    QWidget::showNormal();
}

void TopWindow::showModal()
{
    // 作为 Dialog 需要同时设置 Qt::Dialog | Qt::Popup 两个 flags
    setWindowFlags(Qt::Dialog | Qt::Popup | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    showCenter(this);

    // 进入局部事件循环，阻塞代码继续往下走，窗口关闭时结束此局部事件循环，控制权交还给 QApplication
    // The event loop returns from the call to quit().
    QEventLoop loop;
    connect(this, &TopWindow::aboutClose, &loop, &QEventLoop::quit);
    loop.exec();
}

// 查找 widget 所在的顶级窗口
QWidget *TopWindow::findWindow(QWidget *widget)
{
    QWidget *p = widget;

    while (nullptr != p->parentWidget())
    {
        p = p->parentWidget();
    }

    return p;
}

// 居中显示窗口
void TopWindow::showCenter(QWidget *window)
{
    // This doesn't show the widget on the screen since you don't relinquish control back to the queue
    // until the hide() happens. In between, the invalidate() computes the correct positions.
    window->show();
    window->layout()->invalidate();
    window->hide();

    QSize size = qApp->primaryScreen()->availableSize() - window->size();
    int x = qMax(0, size.width() / 2);
    int y = qMax(0, size.height() / 2);
    window->move(x, y);
    window->show();
}

// 使用九宫格的方式绘制背景
void TopWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    d_->nine_patch_painter_->paint(&painter, rect());
}

// 鼠标按下时记录此时鼠标的全局坐标和窗口左上角的坐标
void TopWindow::mousePressEvent(QMouseEvent *event)
{
    d_->mouse_pressed_position_ = event->globalPos();
    d_->window_position_before_moving_ = frameGeometry().topLeft();
}
// 鼠标放开时设置 mouse_pressed_position_ 为空坐标
void TopWindow::mouseReleaseEvent(QMouseEvent *)
{
    d_->mouse_pressed_position_ = QPoint();
}

// 鼠标移动时如果 mouse_pressed_position_ 不为空，则说明需要移动窗口
// 鼠标移动的位移差，就是窗口移动的位移差
void TopWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 最大化时不可以移动窗口
    if (isMaximized())
    {
        return;
    }

    if (!d_->mouse_pressed_position_.isNull())
    {
        QPoint delta = event->globalPos() - d_->mouse_pressed_position_;
        QPoint newPosition = d_->window_position_before_moving_ + delta;
        move(newPosition);
    }
}

// 关闭窗口时发送 aboutClose() 信号，模态对话框收到此信号时好结束事件循环
void TopWindow::closeEvent(QCloseEvent *event)
{
    emit aboutClose();
    QWidget::closeEvent(event);
}

void TopWindow::handleEvents()
{
    connect(ui->min_button, &QPushButton::clicked, [this] {
        showMinimized(); // 最小化
    });

    connect(ui->max_button, &QPushButton::clicked, [this] {
        showMaximized(); // 最大化
    });

    connect(ui->restore_button, &QPushButton::clicked, [this] {
        showNormal(); // 恢复窗口大小
    });

    connect(ui->close_button, &QPushButton::clicked, [this] {
        close(); // 关闭窗口
    });
}
