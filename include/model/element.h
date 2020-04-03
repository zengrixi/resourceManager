///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： element.h
// 文件摘要： 程序所用到的数据类型定义
// 创建作者： 曾日希
// 创建时间： 2020-04-02 16:57:30
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

// 位置信息
struct Pos
{
    double location_longitude; // 阵地位置-经度
    double location_latitude;  // 阵地位置-纬度
    double location_highly;    // 阵地位置-高度
};

// 资源信息
struct ResourceData
{
    QString name; // 资源名称
    QString id;   // 资源编号
    int type;     // 资源类型，用于区分资源是预警卫星、预警雷达、识别雷达、空基探测、中段阵地、末高阵地等
    int authorization;     // 授权状态，0 未授权 1已授权
    int equipment_state;   // 装备状态，0 待机 1 准备 2 正常运行 3 表示故障等
    int communicate_state; // 通信状态，0 未通信 1 正在通信
    Pos position_;         // 阵地位置
};

#endif // ELEMENT_H