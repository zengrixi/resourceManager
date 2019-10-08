#include "NinePatchPainter.h"

#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QRect>

/*-----------------------------------------------------------------------------|
 |                           NinePatchPainterPrivate                           |
 |----------------------------------------------------------------------------*/
class NinePatchPainterPrivate {
public:
    NinePatchPainterPrivate(const QPixmap &background, int left, int top, int right, int bottom,
                            bool horizontal_stretch, bool vertical_stretch);

    // 根据九宫格 4 边的宽度把 rect 按九宫格分割为 9 个 rect: 左、左上、上、右上、右、右下、下、左下、中间
    QList<QRect> calculate_nine_patch_rects(const QRect &rect) const;

    // 对图片进行缩放
    QPixmap scale_pixmap(const QPixmap &pixmap, const QSize &size) const;

public:
    int left;                // 左边的宽
    int top;                 // 上边的宽
    int right;               // 右边的宽
    int bottom;              // 下边的宽
    bool horizontal_stretch; // 水平方向是否使用拉伸绘制
    bool vertical_stretch;   // 垂直方向是否使用拉伸绘制

    QPixmap left_pixmap;         // 左边的子图
    QPixmap topLeft_pixmap;      // 左上角的子图
    QPixmap top_pixmap;          // 顶部的子图
    QPixmap top_right_pixmap;    // 右上角的子图
    QPixmap right_pixmap;        // 右边的子图
    QPixmap bottom_left_pixmap;  // 左下角的子图
    QPixmap bottom_pixmap;       // 底部的子图
    QPixmap bottom_right_pixmap; // 右下角的子图
    QPixmap center_pixmap;       // 中间的子图
};

NinePatchPainterPrivate::NinePatchPainterPrivate(const QPixmap &background, int left, int top, int right, int bottom,
                                                 bool horizontal_stretch, bool vertical_stretch)
    : left(left)
    , top(top)
    , right(right)
    , bottom(bottom)
    , horizontal_stretch(horizontal_stretch)
    , vertical_stretch(vertical_stretch) {
    // 把 background 分割成 9 个子图，程序运行期间不会变，所以缓存起来
    QRect pixmap_rect(0, 0, background.width(), background.height());
    QList<QRect> rects = calculate_nine_patch_rects(pixmap_rect);

    left_pixmap = background.copy(rects.at(0));
    topLeft_pixmap = background.copy(rects.at(1));
    top_pixmap = background.copy(rects.at(2));
    top_right_pixmap = background.copy(rects.at(3));
    right_pixmap = background.copy(rects.at(4));
    bottom_right_pixmap = background.copy(rects.at(5));
    bottom_pixmap = background.copy(rects.at(6));
    bottom_left_pixmap = background.copy(rects.at(7));
    center_pixmap = background.copy(rects.at(8));
}

QList<QRect> NinePatchPainterPrivate::calculate_nine_patch_rects(const QRect &rect) const {
    int x = rect.x();
    int y = rect.y();
    int cw = rect.width() - left - right;  // 中间部分的宽
    int ch = rect.height() - top - bottom; // 中间部分的高

    // 根据把 rect 分割成 9 个部分: 左、左上、上、右上、右、右下、下、左下、中间
    QRect left_rect(x, y + top, left, ch);
    QRect top_left_rect(x, y, left, top);
    QRect top_rect(x + left, y, cw, top);
    QRect top_right_rect(x + left + cw, y, right, top);
    QRect right_rect(x + left + cw, y + top, right, ch);
    QRect bottom_right_rect(x + left + cw, y + top + ch, right, bottom);
    QRect bottom_rect(x + left, y + top + ch, cw, bottom);
    QRect bottom_left_rect(x, y + top + ch, left, bottom);
    QRect center_rect(x + left, y + top, cw, ch);

    return QList<QRect>() << left_rect << top_left_rect << top_rect << top_right_rect << right_rect << bottom_right_rect
                          << bottom_rect << bottom_left_rect << center_rect;
}

QPixmap NinePatchPainterPrivate::scale_pixmap(const QPixmap &pixmap, const QSize &size) const {
    // 缩放时忽略图片的高宽比，使用平滑缩放的效果
    return pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

/*-----------------------------------------------------------------------------|
 |                              NinePatchPainter                               |
 |----------------------------------------------------------------------------*/
NinePatchPainter::NinePatchPainter(const QPixmap &background, int left, int top, int right, int bottom,
                                   bool horizontal_stretch, bool vertical_stretch)
    : d_(new NinePatchPainterPrivate(background, left, top, right, bottom, horizontal_stretch, vertical_stretch)) {}

NinePatchPainter::~NinePatchPainter() { delete d_; }

void NinePatchPainter::paint(QPainter *painter, const QRect &rect) const {
    // 把要绘制的 Rect 分割成 9 个部分，上，右，下，左 4 边的宽和背景图的一样
    QList<QRect> rects = d_->calculate_nine_patch_rects(rect);

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
    painter->drawPixmap(top_left_rect, d_->topLeft_pixmap);
    painter->drawPixmap(top_right_rect, d_->top_right_pixmap);
    painter->drawPixmap(bottom_right_rect, d_->bottom_right_pixmap);
    painter->drawPixmap(bottom_left_rect, d_->bottom_left_pixmap);

    // 绘制左、右边
    if (d_->horizontal_stretch) {
        // 水平拉伸
        painter->drawPixmap(left_rect, d_->scale_pixmap(d_->left_pixmap, left_rect.size()));
        painter->drawPixmap(right_rect, d_->scale_pixmap(d_->right_pixmap, right_rect.size()));
    } else {
        // 水平平铺
        painter->drawTiledPixmap(left_rect, d_->left_pixmap);
        painter->drawTiledPixmap(right_rect, d_->right_pixmap);
    }

    // 绘制上、下边
    if (d_->vertical_stretch) {
        // 垂直拉伸
        painter->drawPixmap(top_rect, d_->scale_pixmap(d_->top_pixmap, top_rect.size()));
        painter->drawPixmap(bottom_rect, d_->scale_pixmap(d_->bottom_pixmap, bottom_rect.size()));
    } else {
        // 垂直平铺
        painter->drawTiledPixmap(top_rect, d_->top_pixmap);
        painter->drawTiledPixmap(bottom_rect, d_->bottom_pixmap);
    }

    int pmw = d_->center_pixmap.width();
    int pmh = d_->center_pixmap.height();
    int crw = center_rect.width();
    int crh = center_rect.height();

    // 绘制中间部分(最简单办法就是中间部分都进行拉伸)
    if (d_->horizontal_stretch && d_->vertical_stretch) {
        // 水平和垂直都拉伸
        painter->drawPixmap(center_rect, d_->scale_pixmap(d_->center_pixmap, center_rect.size()));
    } else if (d_->horizontal_stretch && !d_->vertical_stretch) {
        // 水平拉伸，垂直平铺
        if (crh % pmh != 0) {
            pmh = ((float)crh) / (crh / pmh + 1);
        }
        QSize size(crw, pmh);
        QPixmap center_pixmap = d_->scale_pixmap(d_->center_pixmap, size);
        painter->drawTiledPixmap(center_rect, center_pixmap);
    } else if (!d_->horizontal_stretch && d_->vertical_stretch) {
        // 水平平铺，垂直拉伸
        if (crw % pmw != 0) {
            pmw = ((float)crw) / (crw / pmw + 1);
        }
        QSize size(pmw, crh);
        QPixmap center_pixmap = d_->scale_pixmap(d_->center_pixmap, size);
        painter->drawTiledPixmap(center_rect, center_pixmap);
    } else {
        // 水平和垂直都平铺
        painter->drawTiledPixmap(center_rect, d_->center_pixmap);
    }
}
