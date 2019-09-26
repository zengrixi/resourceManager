#include "textdelegate.h"

#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QCheckBox>
#include <QPainter>
#include <QTextDocument>

TextDelegate::TextDelegate(QWidget *parent) : QStyledItemDelegate(parent) {}

void TextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem view_option(option);
    initStyleOption(&view_option, index);
    if (option.state.testFlag(QStyle::State_HasFocus)) view_option.state = view_option.state ^ QStyle::State_HasFocus;

    // 设置显示文本为空，使用默认样式
    QStyle *style = view_option.widget ? view_option.widget->style() : QApplication::style();
    view_option.text = "";
    style->drawControl(QStyle::CE_ItemViewItem, &view_option, painter, view_option.widget);

    QString text;
    QRect text_rect;

    if (index.column() == 2) {
        if (index.data().toBool()) {
            text = tr("已授权");
            painter->setPen(Qt::blue);
        } else {
            text = tr("未授权");
            painter->setPen(Qt::yellow);
        }

        text_rect = style->subElementRect(QStyle::SE_ItemViewItemText, &view_option);
    } else if (index.column() == 3) {
        if (index.data().toInt() == 0) {
            text = tr("待机");
            painter->setPen(Qt::blue);
        } else if (index.data().toInt() == 1) {
            text = tr("准备");
            painter->setPen(Qt::yellow);
        } else if (index.data().toInt() == 2) {
            text = tr("正常运行");
            painter->setPen(Qt::green);
        } else if (index.data().toInt() == 3) {
            text = tr("故障");
            painter->setPen(Qt::red);
        } else {
            text = tr("");
        }

        text_rect = style->subElementRect(QStyle::SE_ItemViewItemText, &view_option);
    } else if (index.column() == 4) {
        if (index.data().toBool()) {
            text = tr("正在通信");
            painter->setPen(Qt::green);
        } else {
            text = tr("未通信");
            painter->setPen(Qt::red);
        }

        text_rect = style->subElementRect(QStyle::SE_ItemViewItemText, &view_option);
    } else {
        QStyledItemDelegate::paint(painter, view_option, index);
        return;
    }

    /* 绘制工作 */
    painter->save();
    // 坐标变换，将左上角设置为原点
    painter->translate(text_rect.topLeft());
    // 设置文本绘制区域
    painter->setClipRect(text_rect.translated(-text_rect.topLeft()));

    painter->drawText(0, 0, text_rect.width(), text_rect.height(), Qt::AlignCenter, text);
    painter->restore();
}

void TextDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {}
