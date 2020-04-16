#ifndef ZHIKONGVIEW_H
#define ZHIKONGVIEW_H

#include <QWidget>

namespace Ui {
class ZhiKongView;
}

class ZhiKongView : public QWidget
{
    Q_OBJECT

public:
    explicit ZhiKongView(QWidget *parent = nullptr);
    ~ZhiKongView();

private:
    Ui::ZhiKongView *ui;
};

#endif // ZHIKONGVIEW_H
