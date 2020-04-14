#ifndef YUJINVIEW_H
#define YUJINVIEW_H

#include <QWidget>

namespace Ui {
class YuJinView;
}

class YuJinView : public QWidget
{
    Q_OBJECT

public:
    explicit YuJinView(QWidget *parent = nullptr);
    ~YuJinView();

private:
    Ui::YuJinView *ui;
};

#endif // YUJINVIEW_H
