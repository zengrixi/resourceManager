///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： messagebox.h
// 文件摘要： 消息窗体的封装
// 创建作者： 曾日希
// 创建时间： 2020-04-02 10:13:00
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

class TopWindow;
namespace Ui
{
class MessageBox;
}

/**
 * 自定义消息对话框，提供普通消息对话框和确认消息对话框，使用方式如下:
 *     MessageBox::message("Your Message")
 *     if (MessageBox::confirm("确定要删除 XX 吗?")) {}
 */
class MessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox(const QString &message, bool cancel_button_visible = true);
    ~MessageBox();

    /**
     * @brief 显示模态消息对话框，但是不会阻塞当前线程。
     *        消息可以是普通文本，也可以是 HTML(可以有 <img><font> 等标签，能够显示丰富的消息样式)
     *        可以指定宽度和高度，如果宽度和高度小于 sizeHint() 给出的大小，则使用 sizeHint()，
     *        如果大于 sizeHint() 则使用我们指定的宽度和高度
     *
     * @param msg    要显示的消息
     * @param width  消息对话框的宽度
     * @param height 消息对话框的高度
     * @param window_paddings // 参考 TopWindow 的构造函数参数说明，一下几个参数也是一样的
     * @param border_image_borders
     * @param border_image_path
     * @param border_image_horizontal_stretch
     * @param border_image_vertical_stretch
     */
    static void message(const QString &msg,
        int width = 300,
        int height = 150,
        const QMargins &window_paddings = QMargins(13, 13, 13, 13),
        const QMargins &border_image_borders = QMargins(18, 18, 18, 18),
        const QString &border_image_path = QString(":/img/top-window/colorful-border.png"),
        bool border_image_horizontal_stretch = false,
        bool border_image_vertical_stretch = false);

    /**
     * @brief 显示模态确认对话框，会阻塞当前线程。
     *        消息可以是普通文本，也可以是 HTML(可以有 <img><font> 等标签，能够显示丰富的消息样式)
     *        可以指定宽度和高度，如果宽度和高度小于 sizeHint() 给出的大小，则使用 sizeHint()，
     *        如果大于 sizeHint() 则使用我们指定的宽度和高度
     *
     * @param msg    要显示的消息
     * @param width  消息对话框的宽度
     * @param height 消息对话框的高度
     * @param window_paddings  // 参考 TopWindow 的构造函数参数说明，一下几个参数也是一样的
     * @param border_image_borders
     * @param border_image_path
     * @param border_image_horizontal_stretch
     * @param border_image_vertical_stretch
     * @return 点击确认返回 true，点击取消返回 false
     */
    static bool confirm(const QString &msg,
        int width = 300,
        int height = 150,
        const QMargins &window_paddings = QMargins(13, 13, 13, 13),
        const QMargins &border_image_borders = QMargins(18, 18, 18, 18),
        const QString &border_image_path = QString(":/img/top-window/colorful-border.png"),
        bool border_image_horizontal_stretch = false,
        bool border_image_vertical_stretch = false);

private:
    static void setWindowForMessageBox(TopWindow *window, int width, int height); // 设置 TopWindow 的属性

    Ui::MessageBox *ui;
    bool result_ = false;
};

#endif // MESSAGEBOX_H
