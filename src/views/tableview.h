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
    static TableView *get_instance();

private:
    static TableView *ptable_view;
    TableView(QWidget *parent = nullptr);
    ~TableView();

public slots:
    /*
     * @description: 测试单元
     * @param:
     * @return:
     */
    void add_data();
    void clean_data();

private:
    /*
     * @description: 样式设置
     * @param:
     * @return:
     */
    void set_sty_sheet();

protected:
    /*
     * @description: 加载样式表
     * @param: styleSheetFile 样式表文件
     * @return:
     */
    void load_style_sheet(const QString &styleSheetFile);

    /*
     * @description: 鼠标滚轮事件
     * @param:
     * @return:
     */
    virtual void wheelEvent(QWheelEvent *e) override;

private:
    TableModel *ptabmodel_;
    QList<MsgData> pmsg_list_;

    QScrollBar *phor_scrollbar_;

    int index_;
};

#endif // WIDGET_H
