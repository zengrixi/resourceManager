#include "ui_messagebox.h"
#include "messagebox.h"
#include "topwindow.h"

MessageBox::MessageBox(const QString &message, bool cancel_button_visible) : ui(new Ui::MessageBox)
{
    init();
    ui->message_label->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->message_label->setText(message);
    ui->cancel_button->setVisible(cancel_button_visible);
}

MessageBox::MessageBox(QWidget *w, bool cancel_button_visible) : ui(new Ui::MessageBox)
{
    init();
    // 替换中心窗体为传入的窗体
    ui->gridLayout->replaceWidget(ui->message_label, w);
    ui->cancel_button->setVisible(cancel_button_visible);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::message(const QString &msg,
    int width,
    int height,
    const QMargins &window_paddings,
    const QMargins &border_image_borders,
    const QString &border_image_path,
    bool border_image_horizontal_stretch,
    bool border_image_vertical_stretch)
{
    // 使用自定义窗口
    MessageBox *box = new MessageBox(msg, false);
    TopWindow *window =
        new TopWindow(box, window_paddings, border_image_borders, border_image_path, border_image_horizontal_stretch, border_image_vertical_stretch);
    MessageBox::setMessageBoxForTopWindow(window, width, height);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

bool MessageBox::confirm(const QString &msg,
    int width,
    int height,
    const QMargins &window_paddings,
    const QMargins &border_image_borders,
    const QString &border_image_path,
    bool border_image_horizontal_stretch,
    bool border_image_vertical_stretch)
{
    // 使用自定义窗口
    MessageBox *box = new MessageBox(msg, true);
    TopWindow window(box, window_paddings, border_image_borders, border_image_path, border_image_horizontal_stretch, border_image_vertical_stretch);
    MessageBox::setMessageBoxForTopWindow(&window, width, height);
    window.showModal();

    return box->result_;
}

bool MessageBox::window(QWidget *w,
    int width,
    int height,
    const QMargins &window_paddings,
    const QMargins &border_image_borders,
    const QString &border_image_path,
    bool border_image_horizontal_stretch,
    bool border_image_vertical_stretch)
{
    // 使用自定义窗口
    MessageBox *box = new MessageBox(w);
    TopWindow window(box, window_paddings, border_image_borders, border_image_path, border_image_horizontal_stretch, border_image_vertical_stretch);
    window.setTitle(w->windowTitle());
    MessageBox::setMessageBoxForTopWindow(&window, width, height);
    window.showModal();

    return box->result_;
}

void MessageBox::setMessageBoxForTopWindow(TopWindow *window, int width, int height)
{
    window->setTitleBarVisible(false);
    window->setResizable(false);
    window->setWindowFlags(Qt::Dialog | Qt::Popup | Qt::FramelessWindowHint);
    window->setWindowModality(Qt::ApplicationModal);
    window->resize(width, height);
}

inline void MessageBox::init()
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(".MessageBox { background: white; }");

    // 点击取消按钮关闭窗口
    connect(ui->cancel_button, &QPushButton::clicked, [this] {
        result_ = false;
        TopWindow::findWindow(this)->close();
    });

    // 点击确定按钮关闭窗口
    connect(ui->ok_button, &QPushButton::clicked, [this] {
        result_ = true;
        TopWindow::findWindow(this)->close();
    });
}
