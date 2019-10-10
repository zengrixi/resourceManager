#ifndef WIDGET_H
#define WIDGET_H

#include <QSortFilterProxyModel>
#include <QTableView>
#include <QWidget>

#include "src/controllers/textdelegate.h"
#include "src/models/tablemodel.h"

class QScrollBar;

class TableView : public QTableView {
    Q_OBJECT

public:
    TableView(QWidget *parent = nullptr);
    ~TableView();

public slots:
    void add_data();
    void clean_data();

private:
    void set_sty_sheet();

protected:
    void load_style_sheet(const QString &styleSheetFile);

    /**
     * @brief wheelEvent 鼠标滚轮操作显示数据
     * @param e
     */
    virtual void wheelEvent(QWheelEvent *e) override;

private:
    TableModel *tabmodel_;
    QList<TargetData> data_list_;

    QScrollBar *hor_scrollbar_;

    int index_;
};

#endif // WIDGET_H
