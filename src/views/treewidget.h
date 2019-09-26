#ifndef THREEWIDGET_H
#define THREEWIDGET_H

#include <QDebug>
#include <QTreeWidget>

class TreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget() override;

    QTreeWidgetItem *add_root_node(QString title = "");
    bool add_child_node(QTreeWidgetItem *root, QString title = "");

private:
    QMap<QString, QTreeWidgetItem *> root_items_;
};

#endif // THREEWIDGET_H
