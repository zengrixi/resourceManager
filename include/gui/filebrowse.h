///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： filebrowse.h
// 文件摘要： 想定文件的浏览窗体
// 创建作者： 曾日希
// 创建时间： 2020-04-02 10:04:27
//
///////////////////////////////////////////////////////////////////////////////
#ifndef FILEBROWSE_H
#define FILEBROWSE_H

#include <QDialog>
#include <QDir>

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

    // 获取文件路劲及文件名
    QString getFilePath() const
    {
        return file_path_;
    }

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

private Q_SLOTS:
    void getSelectedRow();

private:
    Ui::FileBrowse *ui;

    QStringList file_path_list_; // 保存的文件路径
    QString file_path_;          // 选中的文件路径
};

#endif // FILEBROWSE_H
