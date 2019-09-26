#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent) {}

TreeWidget::~TreeWidget() {}

QTreeWidgetItem *TreeWidget::add_root_node(QString title) {
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0, title);
    root_items_.insert(title, item);

    return item;
}

bool TreeWidget::add_child_node(QTreeWidgetItem *root, QString title) {
    if (root == nullptr) {
        qDebug() << "faild, root is null!";
        return false;
    }
    QTreeWidgetItem *item = new QTreeWidgetItem(root);
    item->setText(0, title);

    return true;
}
