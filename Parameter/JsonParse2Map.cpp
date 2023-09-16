#include "JsonParse2Map.h"

JsonParse2Map::JsonParse2Map(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    ReadParamsFromFile();
    //    SaveParamsToFile();
}

void createNestedJsonObject2(QJsonObject& parentObject, const QList<QString>& keys, int depth, QString finalValue, int ValueType)
{
    if (depth >= keys.size()) {
        return;
    }

    QString currentKey = keys.at(depth);
    if (depth == keys.size() - 1) {

        if (ValueType == J4_FLOAT64_MAP)
            parentObject[currentKey] = finalValue.toDouble();
        else
            parentObject[currentKey] = finalValue;
    } else {
        if (!parentObject.contains(currentKey)) {
            parentObject[currentKey] = QJsonObject();
        }
        QJsonObject currentObject = parentObject[currentKey].toObject();
        createNestedJsonObject2(currentObject, keys, depth + 1, finalValue, ValueType);

        parentObject[currentKey] = currentObject;
    }
}

int JsonParse2Map::SaveParamsToFile()
{
    QJsonObject jsonObject;
    QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator i;

    for (i = MAPTABLE.begin(); i != MAPTABLE.end(); i++) {

        QString Origin = i.key();
        QList<QString> Parents;
        while (Origin.contains(".")) {
            int DotIndex = Origin.indexOf(".");
            if (DotIndex != -1) {
                QString extractedString = Origin.left(DotIndex);
                Parents.append(extractedString);
                Origin = Origin.mid(DotIndex + 1);
            }
        }
        Parents.append(Origin);
        createNestedJsonObject2(jsonObject, Parents, 0, i.value().value, i.value().valType);
    }

    QJsonDocument jsonDoc(jsonObject);

    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    QFile jsonFile(m_filepath);
    if (jsonFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&jsonFile);
        stream.setCodec("UTF-8");
        stream << jsonString;
        jsonFile.close();
    } else {
        qDebug() << "写入Json文件错误";
    }
    return 0;
}

int JsonParse2Map::ReadParamsFromFile()
{
    int ret = ParseJsonFile(m_filepath);
    return ret;
}

int JsonParse2Map::ChangeParams(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    MAPTABLE.clear();
    if (ReadParamsFromFile())
        return 0;
    else
        return -1;
}

bool JsonParse2Map::setParameter(QString name, double& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    } else {
        _VALUE_ELEMENT4JSON_MAP element;
        QString key = name;
        while (name.contains(".")) {
            int DotIndex = name.indexOf(".");
            if (DotIndex != -1) {
                name = name.mid(DotIndex + 1);
            }
        }
        element.name = name;
        element.value = QString::number(value);
        element.valType = J4_FLOAT64_MAP;
        element.bValChanged = true;
        MAPTABLE.insert(key, element);
    }
    return b_ret;
}

bool JsonParse2Map::setParameter(QString name, QString& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        _iter.value().value = value;
        _iter.value().bValChanged = true;
    } else {
        _VALUE_ELEMENT4JSON_MAP element;
        QString key = name;
        while (name.contains(".")) {
            int DotIndex = name.indexOf(".");
            if (DotIndex != -1) {
                name = name.mid(DotIndex + 1);
            }
        }
        element.name = name;
        element.value = value;
        element.valType = J4_QSTRING_MAP;
        element.bValChanged = true;
        MAPTABLE.insert(key, element);
    }
    return b_ret;
}

bool JsonParse2Map::getParameter(QString name, double& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        value = _iter.value().value.toDouble(&b_ret);
    } else
        qDebug() << "获取Json参数错误";
    return b_ret;
}

bool JsonParse2Map::DeleteParameter(QString name)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        MAPTABLE.remove(name);
    } else {
        qDebug() << "Json文件中不存在此元素，删除失败";
    }
    return b_ret;
}

void JsonParse2Map::GetValueFromRecipe(QString KeyWord, QList<Key2Value>& ParamsList)
{
    if (!ParamsList.isEmpty())
        ParamsList.clear();
    for (auto it = MAPTABLE.constBegin(); it != MAPTABLE.constEnd(); ++it) {
        if (it.key().contains(KeyWord)) {
            Key2Value singlevalue;
            singlevalue.Name = it.value().name;
            singlevalue.Value = it.value().value.toDouble();
            ParamsList.append(singlevalue);
        }
    }
}

void JsonParse2Map::SetValue2Recipe(QString KeyWord, QList<Key2Value>& ParamList)
{
    for (int i = 0; i < ParamList.count(); i++) {
        QString key = KeyWord + "." + ParamList[i].Name;
        setParameter(key, ParamList[i].Value);
    }
}

int JsonParse2Map::ParseJsonFile(QString FileName)
{
    QFile file(FileName);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        qDebug() << "文件打开错误";
        return -1;
    }
    QString jsonString = QString(file.readAll());
    //    qDebug() << jsonString;
    file.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug() << "Json文件读取 错误";
        return -1;
    }
    ParseJsonObject(jsonDocument.object());
    return 0;
}

void JsonParse2Map::ParseJsonObject(const QJsonObject& jsonObj)
{
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        CurrentKey += it.key();
        QJsonValue currentValue = it.value();

        if (currentValue.isObject()) {
            CurrentKey += ".";
            ParseJsonObject(currentValue.toObject());
            CurrentKey.chop(it.key().length() + 1);
        } else {
            _VALUE_ELEMENT4JSON_MAP element;
            element.name = it.key();
            if (currentValue.isDouble()) {
                double LastValue = currentValue.toDouble();
                element.value = QString::number(LastValue);
                element.valType = J4_FLOAT64_MAP;
            } else if (currentValue.isString()) {
                QString LastValue = currentValue.toString();
                element.value = LastValue;
                element.valType = J4_QSTRING_MAP;
            }
            //            qDebug() << CurrentKey << " , " << element.name << " , " << element.value << " , " << element.valType; //不是按照顺序读取的json文件
            MAPTABLE.insert(CurrentKey, element); //至此为止参数全部写入Hash表
            CurrentKey.chop(it.key().length());
        }
    }
}
