#include "xmlmap.h"

XmlMap::XmlMap(QString xml_path)
{
    QDomDocument d;
    file_ = new QFile(xml_path);
    if (file_->open(QFile::ReadOnly))
    {
        if (d.setContent(file_))
        {
            if (d.firstChild().childNodes().length() == 0)
                d.removeChild(d.firstChild());
            loadFromNode(d.firstChild());
        }
    }
    else
    {
        qDebug() << "xml file error!";
    }
    file_->close();
}

XmlMap::XmlMap(QDomNode node)
{
    loadFromNode(node);
}

void XmlMap::loadFromNode(QDomNode node)
{
    n = node;
    if (n.isElement())
    {
        e = n.toElement();
    }
    loadChildren();
    return;
}

int XmlMap::loadChildren()
{
    QDomNodeList children = n.childNodes();
    if (children.length() > 0)
        for (int i = 0; i < children.length(); i++)
        {
            c.append(new XmlMap(children.at(i)));
            c.at(i)->setParent(this);
        }
    return c.length();
}

void XmlMap::setParent(XmlMap *parent)
{
    p = parent;
}

XmlMap *XmlMap::findOneByTag(QString tag_name)
{
    if (e.tagName() == tag_name)
    {
        return this;
    }
    else
    {
        for (int i = 0; i < c.length(); i++)
        {
            XmlMap *found = c.at(i)->findOneByTag(tag_name);
            if (found != nullptr)
                return found;
            delete found;
        }
    }
    return nullptr;
}

XmlMap *XmlMap::findChildrenByTag(QString tag_name)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    for (int i = 0; i < c.length(); i++)
    {
        if (c.at(i)->e.tagName() == tag_name)
        {
            found->c.append(c.at(i));
        }
    }
    return found;
}

XmlMap *XmlMap::findAllByTag(QString tag_name)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    ;
    for (int i = 0; i < c.length(); i++)
    {
        found->c.append(c.at(i)->findAllByTag(tag_name)->c);
    }
    if (e.tagName() == tag_name)
        found->c.append(this);
    return found;
}

XmlMap *XmlMap::findOneByAttrName(QString attr_name)
{
    if (e.hasAttribute(attr_name))
    {
        return this;
    }
    else
    {
        for (int i = 0; i < c.length(); i++)
        {
            XmlMap *found = c.at(i)->findOneByAttrName(attr_name);
            if (found != nullptr)
                return found;
            delete found;
        }
    }
    return nullptr;
}

XmlMap *XmlMap::findChildrenByAttrName(QString attr_name)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    for (int i = 0; i < c.length(); i++)
    {
        if (c.at(i)->e.hasAttribute(attr_name))
        {
            found->c.append(c.at(i));
        }
    }
    return found;
}

XmlMap *XmlMap::findAllByAttrName(QString attr_name)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    ;
    for (int i = 0; i < c.length(); i++)
    {
        found->c.append(c.at(i)->findAllByAttrName(attr_name)->c);
    }
    if (e.hasAttribute(attr_name))
        found->c.append(this);
    return found;
}

XmlMap *XmlMap::findOneByAttrValue(QString attr_name, QString attr_value)
{
    if (e.attribute(attr_name) == attr_value)
    {
        return this;
    }
    else
    {
        for (int i = 0; i < c.length(); i++)
        {
            XmlMap *found = c.at(i)->findOneByAttrValue(attr_name, attr_value);
            if (found != nullptr)
                return found;
            delete found;
        }
    }
    return nullptr;
}

XmlMap *XmlMap::findChildrenByAttrValue(QString attr_name, QString attr_value)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    for (int i = 0; i < c.length(); i++)
    {
        if (c.at(i)->e.attribute(attr_name) == attr_value)
        {
            found->c.append(c.at(i));
        }
    }
    return found;
}

XmlMap *XmlMap::findAllByAttrValue(QString attr_name, QString attr_value)
{
    XmlMap *found = new XmlMap(*new QDomNode());
    for (int i = 0; i < c.length(); i++)
    {
        found->c.append(c.at(i)->findAllByAttrValue(attr_name, attr_value)->c);
    }
    if (e.attribute(attr_name) == attr_value)
        found->c.append(this);
    return found;
}

XmlMap *XmlMap::$(QString search_string)
{
    search_string = search_string.split("\\>").join("$gt$");
    XmlMap *found = this;
    QString query;
    QString end;
    QStringList split;
    // TODO: qt style traversing the container.
    foreach (query, search_string.split(">"))
    {

        // TODO: c++ style traversing the container.
        // QStringList search_string_split = search_string.split(">");
        // QStringList::iterator iter = search_string_split.begin();
        // for (; iter != search_string_split.end(); iter++)
        // {
        //     query = *iter;
        query = query.split("$gt$").join(">");
        end = query.at(query.length() - 1);
        if ("." == end || "*" == end)
        {
            query = query.mid(0, query.length() - 1);
        }

        if ('@' == query.at(0))
        {
            query = query.mid(1, query.length() - 1);
            split = query.split("=");
            if (split.length() > 2)
            {
                return found;
            }
            if (split.length() == 2)
            {
                if ("." == end)
                {
                    found = found->findChildrenByAttrValue(split.at(0), split.at(1));
                }
                else if ("*" == end)
                {
                    found = found->findAllByAttrValue(split.at(0), split.at(1));
                }
                else
                {
                    found = found->findOneByAttrValue(split.at(0), split.at(1));
                }
            }
            else
            {
                if ("." == end)
                {
                    found = found->findChildrenByAttrName(split.at(0));
                }
                else if ("*" == end)
                {
                    found = found->findAllByAttrName(split.at(0));
                }
                else
                {
                    found = found->findOneByAttrName(split.at(0));
                }
            }
        }
        else
        {
            if ("." == end)
            {
                found = found->findChildrenByTag(query);
            }
            else if ("*" == end)
            {
                found = found->findAllByTag(query);
            }
            else
            {
                found = found->findOneByTag(query);
            }
        }
    }

    if (found == nullptr)
    {
        return new XmlMap(*new QDomNode());
    }

    return found;
}
