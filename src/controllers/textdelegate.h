#ifndef CTEXTDELEGATE_H
#define CTEXTDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>

/**
 * @brief The TextDelegate class
 * 表格代理功能
 * 提供颜色更改和表格操作
 */
class TextDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit TextDelegate(QWidget *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:

public slots:
};

#endif // CTEXTDELEGATE_H
