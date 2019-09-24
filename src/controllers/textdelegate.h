#ifndef CTEXTDELEGATE_H
#define CTEXTDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>

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
