#ifndef RESOURCESETTING_H
#define RESOURCESETTING_H

#include <QDialog>
#include <QGridLayout>
#include <QObject>
#include <QPushButton>
#include <QTableWidget>

class ResourceSetting : public QDialog {
    Q_OBJECT
public:
    explicit ResourceSetting(const QString &title = "", QWidget *parent = nullptr);

signals:

public slots:

private:
    QGridLayout *grid_layout_;
    QString title_;
    QTableWidget *table_;
    QPushButton *sure_;
    QPushButton *cancel_;
};

#endif // RESOURCESETTING_H
