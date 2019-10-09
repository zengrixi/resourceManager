#ifndef LOADSRCWIDGET_H
#define LOADSRCWIDGET_H

#include <QDialog>
#include <QPainter>

#include "src/utils/ninepatchpainter.h"

class LoadSrcDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoadSrcDialog(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *) override;

signals:

public slots:

private:
    NinePatchPainter *nine_patch_painter_;
};

#endif // LOADSRCWIDGET_H
