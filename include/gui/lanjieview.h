#ifndef LANJIEVIEW_H
#define LANJIEVIEW_H

#include <QWidget>

namespace Ui {
class LanjieView;
}

class LanjieView : public QWidget
{
    Q_OBJECT

public:
    explicit LanjieView(QWidget *parent = nullptr);
    ~LanjieView();

private:
    Ui::LanjieView *ui;
};

#endif // LANJIEVIEW_H
