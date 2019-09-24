#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QLabel>
#include <QWidget>

class QPushButton;
class QHBoxLayout;

class TitleBar : public QWidget {
    Q_OBJECT

public:
    TitleBar(QWidget *parent = nullptr);
    virtual ~TitleBar() override;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_clicked();

private:
    void update_maximize();
    void init_control();

private:
    int title_height_;
    QLabel *picon_label_;
    QLabel *ptitle_label_;
    QHBoxLayout *playout_;
    QPushButton *pminimize_btn_;
    QPushButton *pmaximize_btn_;
    QPushButton *pclose_button_;
};

#endif // TITLEBAR_H
