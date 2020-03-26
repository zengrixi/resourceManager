///////////////////////////////////////////////////////////////////////////////
//
// 版权声明： Copyright (c) 2020 曾日希. All rights reserved.
// 文件名称： xmlmap.h
// 文件摘要： xml文件解析类。
// 创建作者： 曾日希
// 创建时间： 2020-03-16 09:51:29
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XMLMAP_H
#define XMLMAP_H

#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>

class XmlMap
{
public:
    explicit XmlMap(QString xml_path);
    explicit XmlMap(QDomNode node);

    // QDomDocument  d;
    QDomNode n;        // node
    QDomElement e;     // element
    QList<XmlMap *> c; // children
    XmlMap *p;         // parent

    QFile *file_;

    void loadFromNode(QDomNode node);
    int loadChildren();
    void setParent(XmlMap *parent);

    /**
     * @brief 查找具有此类标记名的第一个元素
     */
    XmlMap *findOneByTag(QString tag_name);
    /**
     * @brief 只查找第一代孩子
     */
    XmlMap *findChildrenByTag(QString tag_name);
    /**
     * @brief 查找所有的孩子
     */
    XmlMap *findAllByTag(QString tag_name);

    // 与上面相同
    XmlMap *findOneByAttrName(QString attr_name);
    XmlMap *findChildrenByAttrName(QString attr_name);
    XmlMap *findAllByAttrName(QString tag_name);

    /**
     * @brief 查找第一个元素
     * 根据传入的属性字段名和相对应的属性字段值找到第一个符合的元素
     * @param attr_name 属性字段名
     * @param attr_value 属性字段值
     * @return 如果找到则返回该元素指针，否则返回NULL
     */
    XmlMap *findOneByAttrValue(QString attr_name, QString attr_value);
    XmlMap *findChildrenByAttrValue(QString attr_name, QString attr_value);
    XmlMap *findAllByAttrValue(QString attr_name, QString attr_value);

    XmlMap *$(QString search_string);
};

#endif // XMLMAP_H
