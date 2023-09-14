/*******************************************
    @ClassName   : XmlParse
    @Description : xml文档处理类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-04
********************************************/
#ifndef XMLPARSE_H
#define XMLPARSE_H

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QString>
#include <QTextStream>
#include <QtXml/QDomDocument>

typedef enum _ELE_TYPE {
    M_INT8 = 1,
    M_UINT8 = 2,
    M_INT16 = 3,
    M_UINT16 = 4,
    M_INT32 = 5,
    M_UINT32 = 6,
    M_INT64 = 7,
    M_UINT64 = 8,
    M_FLOAT32 = 9,
    M_FLOAT64 = 10,
    M_QSTRING = 11,
} ELE_TYPE;

typedef struct _VALUE_ELEMENT {
    QString name;
    ELE_TYPE valType;
    bool bValChanged;
    QString value;
    QString address;
} VALUE_ELEMENT;

class XmlParse {
public:
    XmlParse(QString FileName);

    int SaveParasToFile(); //只有修改了值的变量保存
    int InitParams(); //初始化参数

    bool setParameter(QString name, char& value);
    bool setParameter(QString name, unsigned char& value);
    bool setParameter(QString name, short& value);
    bool setParameter(QString name, unsigned short& value);
    bool setParameter(QString name, int& value);
    bool setParameter(QString name, unsigned int& value);
    bool setParameter(QString name, long long& value);
    bool setParameter(QString name, unsigned long long& value);
    bool setParameter(QString name, float& value);
    bool setParameter(QString name, double& value);
    bool setParameter(QString name, QString& value);

    bool getParameter(QString name, char& value);
    bool getParameter(QString name, unsigned char& value);
    bool getParameter(QString name, short& value);
    bool getParameter(QString name, unsigned short& value);
    bool getParameter(QString name, int& value);
    bool getParameter(QString name, unsigned int& value);
    bool getParameter(QString name, long long& value);
    bool getParameter(QString name, unsigned long long& value);
    bool getParameter(QString name, float& value);
    bool getParameter(QString name, double& value);
    bool getParameter(QString name, QString& value);

    bool getAddress(QString name, int& Addr);

private:
    int parse_app_xml_file(QString FileName);
    unsigned char getValType(QString str);

    QString m_filename;
    QHash<QString, VALUE_ELEMENT> m_val_hashtable;
};

#endif // XMLPARSE_H
