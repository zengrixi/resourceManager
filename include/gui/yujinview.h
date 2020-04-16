///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： yujinview.h
// 文件摘要： 预警系统资源状态显示面板
// 创建作者： 曾日希
// 创建时间： 2020-04-14 17:00:40
//
///////////////////////////////////////////////////////////////////////////////
#ifndef YUJINVIEW_H
#define YUJINVIEW_H

#include <QWidget>

namespace Ui
{
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
