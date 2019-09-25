#ifndef NINEPATCHPAINTER_H
#define NINEPATCHPAINTER_H

#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QRect>

// NinePatchPainterPrivate
class NinePatchPainterPrivate {
public:
    NinePatchPainterPrivate(const QPixmap &background, int left, int top,
                            int right, int bottom, bool horizontal_strech,
                            bool vertical_stretch);

    // 根据九宫格4边的宽度把 rect 按九宫格分割成9个
    // rect：左、左上、上、右上、右、右下、下、左下、中间
    QList<QRect> calculate_nine_patch_rects(const QRect &rect) const;

    // 对图片进行缩放
    QPixmap scale_pixmap(const QPixmap &pixmap, const QSize &size) const;

public:
    int left_; // 左边的宽
    int top_;
    int right_;
    int bottom_;
    bool horizontal_strech_;
    bool vertical_strech_;

    QPixmap left_pixmap_;
    QPixmap top_left_pixmap_;
    QPixmap top_pixmap_;
    QPixmap top_right_pixmap_;
    QPixmap right_pixmap_;
    QPixmap bottom_left_pixmap_;
    QPixmap bottom_pixmap_;
    QPixmap bottom_right_pixmap_;
    QPixmap center_pixmap_;
};

/*
 * @brief NinePatchPainter
 * 用于九宫格的方式绘图，当背景图和需要绘制的范围不一样大时，能够最大限度的保证绘制出来的效果和背景图接近
 *
 * 需要提供 QPixmap 的背景图和九宫格的4个变宽来创建 NinePatchPainter 对象
 * 调用 NinePatchPainter.paint(painter, rect)即可绘制
 */
class NinePatchPainter {
public:
    /*
     * @brief 使用 pixmap, 九宫格的四个边框, 水平和垂直的缩放方式创建
     * NinePatchPainter 对象
     *
     * @Param background 背景图
     * @Param left 左边高
     * @Param top 上边高
     * @Param right 右边高
     * @Param bottom 下边高
     * @Param horizontal_strech 水平方向是否使用拉伸绘制, 默认为 true
     * @Param vertical_stretch 垂直方向是否使用拉伸绘制, 默认为 true
     */
    NinePatchPainter(const QPixmap &background, int left, int top, int right,
                     int bottom, bool horizontal_strech = true,
                     bool vertical_stretch = true);
    ~NinePatchPainter();

    /*
     * @brief 在 rect 中使用九宫格的方式进行绘图
     */
    void paint(QPainter *painter, const QRect &rect) const;

private:
    NinePatchPainterPrivate *d_;
};

#endif // NINEPATCHPAINTER_H
