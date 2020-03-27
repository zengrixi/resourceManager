#include "ninepatchpainter.h"

#include <QList>

/*-----------------------------------------------------------------------------|
 |                           NinePatchPainterPrivate                           |
 |----------------------------------------------------------------------------*/
class NinePatchPainterPrivate
{
public:
    NinePatchPainterPrivate(const QPixmap &background, int left, int top, int right, int bottom, bool horizontal_stretch, bool vertical_stretch);

    // 根据九宫格 4 边的宽度把 rect 按九宫格分割为 9 个 rect: 左、左上、上、右上、右、右下、下、左下、中间
    QList<QRect> calculateNinePatchRects(const QRect &rect) const;

    // 对图片进行缩放
    QPixmap scalePixmap(const QPixmap &pixmap, const QSize &size) const;

public:
    int left_;                // 左边的宽
    int top_;                 // 上边的宽
    int right_;               // 右边的宽
    int bottom_;              // 下边的宽
    bool horizontal_stretch_; // 水平方向是否使用拉伸绘制
    bool vertical_stretch_;   // 垂直方向是否使用拉伸绘制

    QPixmap left_pixmap_;         // 左边的子图
    QPixmap top_left_pixmap_;     // 左上角的子图
    QPixmap top_pixmap_;           // 顶部的子图
    QPixmap top_right_pixmap_;    // 右上角的子图
    QPixmap right_pixmap_;         // 右边的子图
    QPixmap bottom_left_pixmap_;  // 左下角的子图
    QPixmap bottom_pixmap_;       // 底部的子图
    QPixmap bottom_right_pixmap_; // 右下角的子图
    QPixmap center_pixmap_;       // 中间的子图
};

NinePatchPainterPrivate::NinePatchPainterPrivate(const QPixmap &background,
    int left,
    int top,
    int right,
    int bottom,
    bool horizontal_stretch,
    bool vertical_stretch)
    : left_(left), top_(top), right_(right), bottom_(bottom), horizontal_stretch_(horizontal_stretch), vertical_stretch_(vertical_stretch)
{

    // 把 background 分割成 9 个子图，程序运行期间不会变，所以缓存起来
    QRect pixmapRect(0, 0, background.width(), background.height());
    QList<QRect> rects = calculateNinePatchRects(pixmapRect);

    left_pixmap_ = background.copy(rects.at(0));
    top_left_pixmap_ = background.copy(rects.at(1));
    top_pixmap_ = background.copy(rects.at(2));
    top_right_pixmap_ = background.copy(rects.at(3));
    right_pixmap_ = background.copy(rects.at(4));
    bottom_right_pixmap_ = background.copy(rects.at(5));
    bottom_pixmap_ = background.copy(rects.at(6));
    bottom_left_pixmap_ = background.copy(rects.at(7));
    center_pixmap_ = background.copy(rects.at(8));
}

QList<QRect> NinePatchPainterPrivate::calculateNinePatchRects(const QRect &rect) const
{
    int x = rect.x();
    int y = rect.y();
    int cw = rect.width() - left_ - right_;  // 中间部分的宽
    int ch = rect.height() - top_ - bottom_; // 中间部分的高

    // 根据把 rect 分割成 9 个部分: 左、左上、上、右上、右、右下、下、左下、中间
    QRect left_rect(x, y + top_, left_, ch);
    QRect top_left_rect(x, y, left_, top_);
    QRect top_rect(x + left_, y, cw, top_);
    QRect top_right_rect(x + left_ + cw, y, right_, top_);
    QRect right_rect(x + left_ + cw, y + top_, right_, ch);
    QRect bottom_right_rect(x + left_ + cw, y + top_ + ch, right_, bottom_);
    QRect bottom_rect(x + left_, y + top_ + ch, cw, bottom_);
    QRect bottom_left_rect(x, y + top_ + ch, left_, bottom_);
    QRect center_rect(x + left_, y + top_, cw, ch);

    return QList<QRect>() << left_rect << top_left_rect << top_rect << top_right_rect << right_rect << bottom_right_rect << bottom_rect
                          << bottom_left_rect << center_rect;
}

QPixmap NinePatchPainterPrivate::scalePixmap(const QPixmap &pixmap, const QSize &size) const
{
    // 缩放时忽略图片的高宽比，使用平滑缩放的效果
    return pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

/*-----------------------------------------------------------------------------|
 |                              NinePatchPainter                               |
 |----------------------------------------------------------------------------*/
NinePatchPainter::NinePatchPainter(const QPixmap &background,
    int left,
    int top,
    int right,
    int bottom,
    bool horizontal_stretch,
    bool vertical_stretch)
    : d_(new NinePatchPainterPrivate(background, left, top, right, bottom, horizontal_stretch, vertical_stretch))
{
}

NinePatchPainter::~NinePatchPainter()
{
    delete d_;
}

void NinePatchPainter::paint(QPainter *painter, const QRect &rect) const
{
    // 把要绘制的 Rect 分割成 9 个部分，上，右，下，左 4 边的宽和背景图的一样
    QList<QRect> rects = d_->calculateNinePatchRects(rect);

    QRect left_rect = rects.at(0);
    QRect top_left_rect = rects.at(1);
    QRect top_rect = rects.at(2);
    QRect top_right_rect = rects.at(3);
    QRect right_rect = rects.at(4);
    QRect bottom_right_rect = rects.at(5);
    QRect bottom_rect = rects.at(6);
    QRect bottom_left_rect = rects.at(7);
    QRect center_rect = rects.at(8);

    // 绘制 4 个角
    painter->drawPixmap(top_left_rect, d_->top_left_pixmap_);
    painter->drawPixmap(top_right_rect, d_->top_right_pixmap_);
    painter->drawPixmap(bottom_right_rect, d_->bottom_right_pixmap_);
    painter->drawPixmap(bottom_left_rect, d_->bottom_left_pixmap_);

    // 绘制左、右边
    if (d_->horizontal_stretch_)
    {
        // 水平拉伸
        painter->drawPixmap(left_rect, d_->scalePixmap(d_->left_pixmap_, left_rect.size()));
        painter->drawPixmap(right_rect, d_->scalePixmap(d_->right_pixmap_, right_rect.size()));
    }
    else
    {
        // 水平平铺
        painter->drawTiledPixmap(left_rect, d_->left_pixmap_);
        painter->drawTiledPixmap(right_rect, d_->right_pixmap_);
    }

    // 绘制上、下边
    if (d_->vertical_stretch_)
    {
        // 垂直拉伸
        painter->drawPixmap(top_rect, d_->scalePixmap(d_->top_pixmap_, top_rect.size()));
        painter->drawPixmap(bottom_rect, d_->scalePixmap(d_->bottom_pixmap_, bottom_rect.size()));
    }
    else
    {
        // 垂直平铺
        painter->drawTiledPixmap(top_rect, d_->top_pixmap_);
        painter->drawTiledPixmap(bottom_rect, d_->bottom_pixmap_);
    }

    int pmw = d_->center_pixmap_.width();
    int pmh = d_->center_pixmap_.height();
    int crw = center_rect.width();
    int crh = center_rect.height();

    // 绘制中间部分(最简单办法就是中间部分都进行拉伸)
    if (d_->horizontal_stretch_ && d_->vertical_stretch_)
    {
        // 水平和垂直都拉伸
        painter->drawPixmap(center_rect, d_->scalePixmap(d_->center_pixmap_, center_rect.size()));
    }
    else if (d_->horizontal_stretch_ && !d_->vertical_stretch_)
    {
        // 水平拉伸，垂直平铺
        if (crh % pmh != 0)
        {
            pmh = ((float) crh) / (crh / pmh + 1);
        }
        QSize size(crw, pmh);
        QPixmap center_pixmap = d_->scalePixmap(d_->center_pixmap_, size);
        painter->drawTiledPixmap(center_rect, center_pixmap);
    }
    else if (!d_->horizontal_stretch_ && d_->vertical_stretch_)
    {
        // 水平平铺，垂直拉伸
        if (crw % pmw != 0)
        {
            pmw = ((float) crw) / (crw / pmw + 1);
        }
        QSize size(pmw, crh);
        QPixmap center_pixmap = d_->scalePixmap(d_->center_pixmap_, size);
        painter->drawTiledPixmap(center_rect, center_pixmap);
    }
    else
    {
        // 水平和垂直都平铺
        painter->drawTiledPixmap(center_rect, d_->center_pixmap_);
    }
}
