///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： ninepatchpainter.h
// 文件摘要： 九宫格边框绘制
// 创建作者： 曾日希
// 创建时间： 2020-04-02 10:13:38
//
///////////////////////////////////////////////////////////////////////////////
#ifndef NINEPATCHPAINTER_H
#define NINEPATCHPAINTER_H

#include <QRect>
#include <QMargins>
#include <QPainter>
#include <QPixmap>

class NinePatchPainterPrivate;

/**
 * @brief NinePatchPainter 用于九宫格的方式绘图，当背景图和需要绘制的范围不一样大时，能够最大限度的保证绘制出来的效果和背景图接近.
 *
 * 需要提供 QPixmap 的背景图和九宫格的 4 个变宽来创建 NinePatchPainter 对象，绘图的接口很简单，只有 2 个参数，QPainter 和 QRect，
 * 调用 NinePatchPainter.paint(painter, rect) 就使用了九宫格的方式绘图，不需要其他的操作.
 */
class NinePatchPainter
{
public:
    /**
     * @brief 使用 pixmap, 九宫格的 4 个边宽，水平和垂直的缩放方式创建 NinePatchPainter 对象.
     *
     * @param background 背景图
     * @param left   左边宽
     * @param top    上边高
     * @param right  右边宽
     * @param bottom 下边高
     * @param horizontal_stretch 水平方向是否使用拉伸绘制，默认为 true
     * @param vertical_stretch   垂直方向是否使用拉伸绘制，默认为 true
     */
    NinePatchPainter(const QPixmap &background,
        int left,
        int top,
        int right,
        int bottom,
        bool horizontal_stretch = true,
        bool vertical_stretch = true);
    ~NinePatchPainter();

    /**
     * @brief 在 rect 中使用九宫格的方式进行绘图.
     */
    void paint(QPainter *painter, const QRect &rect) const;

private:
    NinePatchPainterPrivate *d_;
};

#endif // NINEPATCHPAINTER_H