#ifndef FILEBROWSE_H
#define FILEBROWSE_H

#include <QDialog>
#include <QDir>

struct FileProperty
{
    QString file_name; // 文件名
    QString created;   // 创建日期
    QString last_read; // 最后一次修改日期
    QString remark;    // 备注
};

namespace Ui
{
class FileBrowse;
}

class FileBrowse : public QDialog
{
    Q_OBJECT
public:
    explicit FileBrowse(QWidget *parent = nullptr);
    ~FileBrowse();

private:
    // 初始化表格样式
    void initTableWidget();
    void showIs();

    // 获取目录下某种类型的问题
    bool scanDataFile(const QDir &from_dir, const QStringList &filters);
    // 表格添加条目
    void addTableWidgetRow(const QStringList &data);

Q_SIGNALS:
    void onClickOK();
    void onClickCancel();

private:
    Ui::FileBrowse *ui;

    QStringList file_name_list_;
    FileProperty *file_property_;
};

#endif // FILEBROWSE_H
