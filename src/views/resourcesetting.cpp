#include "resourcesetting.h"

ResourceSetting::ResourceSetting(const QString &title, QWidget *parent)
    : QDialog(parent), grid_layout_(new QGridLayout(this)), title_(title) {
    setWindowTitle(title);

    table_ = new QTableWidget(this);
    sure_ = new QPushButton(this);
    cancel_ = new QPushButton(this);
}
