#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QColor>
#include <QMap>
#include <QString>
#include <QVector3D>
#include <QVector>

class xPos {
public:
    double x;
    double y;
    double z;
};

class TargetData {
public:
    char* title;       //资源名称
    char* id;          //资源编号
    int type;          //资源类型
    int auth_status;   //授权状态
    int equi_status;   //装备状态
    int commun_status; //通信状态
    double pos_x;      //阵地位置-经度
    double pos_y;      //阵地位置-纬度
    double pos_z;      //阵地位置-高度
    int count;         //使用此资源设备的目标数目
};

#endif // DATAMODEL_H
