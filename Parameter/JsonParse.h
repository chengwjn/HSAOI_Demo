/*******************************************
    @ClassName   : JsonParse
    @Description : 操作json文档，目前为了适配halcon的dict文件，仅用作参数设置
    @Description2: Qt中读写使用英文
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-20
********************************************/
#ifndef JSONPARSE_H
#define JSONPARSE_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTextStream>

typedef enum _ELE_TYPE4JSON {
    J4_INT8 = 1,
    J4_UINT8 = 2,
    J4_INT16 = 3,
    J4_UINT16 = 4,
    J4_INT32 = 5,
    J4_UINT32 = 6,
    J4_INT64 = 7,
    J4_UINT64 = 8,
    J4_FLOAT32 = 9,
    J4_FLOAT64 = 10,
    J4_QSTRING = 11,
} _ELE_TYPE4JSON;

typedef struct _VALUE_ELEMENT4JSON {
    QString name;
    _ELE_TYPE4JSON valType;
    bool bValChanged;
    QString parent;
    QString value;
} _VALUE_ELEMENT4JSON;

class JsonParse {
public:
    JsonParse(QString FilePath);

    int SaveParasToFile(); //只有修改了值的变量保存
    int InitParams(); //初始化参数

    //name读写时格式为"parent.name"
    bool setParameter(QString name, double& value);
    bool setParameter(QString name, int& value);
    bool setParameter(QString name, QString& value);

    //name读写时格式为"parent.name"
    bool getParameter(QString name, double& value);
    bool getParameter(QString name, int& value);
    bool getParameter(QString name, QString& value);

private:
    unsigned char getValType(QString str);

    QString m_filepath;
    QHash<QString, _VALUE_ELEMENT4JSON> m_val_hashtable;

    //以下均为处理json文件最后存入Hash表中
    int parse_app_json_file(QString FileName);
    void parseJsonObject(const QJsonObject& jsonObj);
    void parseNestedJsonObject(const QJsonObject& jsonObj, const QString& parentKey);
};

#endif // JSONPARSE_H
