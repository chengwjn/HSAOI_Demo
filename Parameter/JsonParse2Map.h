#ifndef JSONPARSE2MAP_H
#define JSONPARSE2MAP_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTextStream>

typedef struct Key2Value {
    QString Name;
    double Value;
} Key2Value;

typedef enum _ELE_TYPE4JSON_MAP {
    J4_INT8_MAP = 1,
    J4_UINT8_MAP = 2,
    J4_INT16_MAP = 3,
    J4_UINT16_MAP = 4,
    J4_INT32_MAP = 5,
    J4_UINT32_MAP = 6,
    J4_INT64_MAP = 7,
    J4_UINT64_MAP = 8,
    J4_FLOAT32_MAP = 9,
    J4_FLOAT64_MAP = 10,
    J4_QSTRING_MAP = 11,
} _ELE_TYPE4JSON_MAP;

typedef struct _VALUE_ELEMENT4JSON_MAP {
    QString name;
    QString value;
    _ELE_TYPE4JSON_MAP valType;
    bool bValChanged;
} _VALUE_ELEMENT4JSON_MAP;

class JsonParse2Map {
public:
    JsonParse2Map(QString FileName);
    QMap<QString, _VALUE_ELEMENT4JSON_MAP> MAPTABLE;

    int SaveParamsToFile(); //只有修改了值的变量保存
    int ReadParamsFromFile(); //初始化参数
    int ChangeParams(QString FileName);

    //name读写时格式为"parent.name"
    bool setParameter(QString name, double& value);
    bool setParameter(QString name, QString& value);

    //name读写时格式为"parent.name"
    bool getParameter(QString name, double& value);
    bool getParameter(QString name, QString& value);

    bool DeleteParameter(QString name);

    void GetValueFromRecipe(QString KeyWord, QList<Key2Value>& ParamsList);
    void SetValue2Recipe(QString KeyWord, QList<Key2Value>& ParamList);

private:
    QString m_filepath;
    QString CurrentKey = "";

    //以下均为处理json文件最后存入Hash表中
    int ParseJsonFile(QString FileName);
    void ParseJsonObject(const QJsonObject& jsonObj);
};

#endif // JSONPARSE2MAP_H
