#include "XmlParse.h"

XmlParse::XmlParse(QString FileName)
{
    m_filename = FileName;
    InitParams();
}

int XmlParse::SaveParasToFile()
{
    int ret = 0;
    QFile file(m_filename);
    if (!file.open(QFile::ReadWrite /*|QFile::Truncate*/))
        return -1;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return -1;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.isElement()) //如果节点是元素
    {
        QDomElement e = root;
        if (!e.tagName().compare("ProcessParas")) {
            QDomNodeList list = e.childNodes();
            for (int i = 0; i < list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n = list.at(i);
                if (n.isElement()) {
                    QDomElement element = n.toElement();
                    QString node_name = element.tagName();
                    bool b_ret = m_val_hashtable.contains(node_name);
                    if (true == b_ret) {
                        QHash<QString, VALUE_ELEMENT>::iterator _iter;
                        _iter = m_val_hashtable.find(node_name);
                        if (_iter.value().bValChanged) {
                            element.setAttribute("value", _iter.value().value);
                        }
                        _iter.value().bValChanged = false;
                    } else {
                        ret = -2; //有变量名重名或命名不合适
                    }
                }
            }
        }
    }

    QFile out_file(m_filename);
    if (!out_file.open(QFile::ReadWrite | QFile::Truncate))
        return -1;

    QTextStream out_stream(&out_file);
    doc.save(out_stream, 4); //缩进4格
    out_file.close();
    doc.clear();
    return ret;
}

int XmlParse::InitParams()
{
    int ret = parse_app_xml_file(m_filename);
    return ret;
}

#pragma region "setParameter" {

bool XmlParse::setParameter(QString name, char& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, unsigned char& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, short& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, unsigned short& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, int& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, unsigned int& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, long long& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, unsigned long long& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, float& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, double& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    }
    return b_ret;
}

bool XmlParse::setParameter(QString name, QString& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        _iter.value().value = value;
        _iter.value().bValChanged = true;
    }
    return b_ret;
}
#pragma endregion }

#pragma region "getParameter" {
bool XmlParse::getParameter(QString name, char& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toInt(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, unsigned char& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toUInt(&b_ret);
        qDebug() << "Find Success";
    } else {
        qDebug() << "No such element";
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, short& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toInt(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, unsigned short& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toUInt(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, int& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toInt(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, unsigned int& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toUInt(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, long long& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toLongLong(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, unsigned long long& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toULongLong(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, float& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toFloat(&b_ret);
    }
    return b_ret;
    //问题:如何保留4位小数
}

bool XmlParse::getParameter(QString name, double& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value.toDouble(&b_ret);
    }
    return b_ret;
}

bool XmlParse::getParameter(QString name, QString& value)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        value = _iter.value().value;
    }
    return b_ret;
}

bool XmlParse::getAddress(QString name, int& Addr)
{
    bool b_ret = m_val_hashtable.contains(name);
    if (b_ret) {
        QHash<QString, VALUE_ELEMENT>::iterator _iter;
        _iter = m_val_hashtable.find(name);
        Addr = _iter.value().address.toInt(&b_ret, 16);
    }
    return b_ret;
}
#pragma endregion }

int XmlParse::parse_app_xml_file(QString FileName)
{
    QFile file(FileName);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "File Open Error";
        return -1;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return -1;
    }
    file.close();
    QDomElement root = doc.documentElement();

    if (root.isElement()) //如果节点是元素
    {
        QDomElement e = root;
        if (!e.tagName().compare("ProcessParas")) {
            QDomNodeList list = e.childNodes();
            for (int i = 0; i < list.count(); i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n = list.at(i);
                if (n.isElement()) {
                    QDomElement element = n.toElement();
                    QString node_name = element.tagName();
                    bool b_ret = m_val_hashtable.contains(node_name);
                    if (false == b_ret) {
                        QString type_name = element.attribute("type");
                        VALUE_ELEMENT t_element;
                        t_element.name = node_name;
                        t_element.valType = ELE_TYPE(getValType(type_name));
                        t_element.bValChanged = false;
                        t_element.value = element.attribute("value");
                        if (element.hasAttribute("addr"))
                            t_element.address = element.attribute("addr");
                        //                        qDebug() << t_element.value;//在此处仍然有4位小数
                        m_val_hashtable.insert(node_name, t_element); //数据插入hashtable中
                    } else {
                        doc.clear();
                        return -2; //有变量名重名或命名不合适
                    }
                }
            }
        }
    }

    return 0;
}

unsigned char XmlParse::getValType(QString str)
{
    unsigned char type = M_QSTRING;

    if (str == "INT8") {
        type = M_INT8;
    } else if (str == "UINT8") {
        type = M_UINT8;
    } else if (str == "INT16") {
        type = M_INT16;
    } else if (str == "UINT16") {
        type = M_UINT16;
    } else if (str == "INT32") {
        type = M_INT32;
    } else if (str == "UINT32") {
        type = M_UINT32;
    } else if (str == "INT64") {
        type = M_INT64;
    } else if (str == "UINT64") {
        type = M_UINT64;
    } else if (str == "FLOAT32") {
        type = M_FLOAT32;
    } else if (str == "FLOAT64") {
        type = M_FLOAT64;
    } else {
        type = M_QSTRING;
    }

    return type;
}
