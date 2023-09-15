#include "JsonParse.h"
#include "log_singleton.h"
#include <QString>

JsonParse::JsonParse(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    InitParams();
    SaveParasToFile();
}

void createNestedJsonObject(QJsonObject& parentObject, const QList<QString>& keys, int depth, QString finalValue)
{
    if (depth >= keys.size()) {
        return;
    }

    QString currentKey = keys.at(depth);

    // 如果是最后一层，设置值为 finalValue
    if (depth == keys.size() - 1) {
        parentObject[currentKey] = finalValue;
    } else {
        // 递归创建下一层
        QJsonObject currentObject;
        createNestedJsonObject(currentObject, keys, depth + 1, finalValue);

        // 如果当前键已存在，合并到数组中
        if (parentObject.contains(currentKey) && parentObject[currentKey].isObject()) {
            QJsonObject existingObject = parentObject[currentKey].toObject();
            // 合并 currentObject 到 existingObject
            for (const auto& key : currentObject.keys()) {
                existingObject[key] = currentObject[key];
            }
            parentObject[currentKey] = existingObject;
        } else {
            parentObject[currentKey] = currentObject;
        }
    }
}

void generateJson(QJsonObject& jsonObject, const QList<QString>& keys, const QString& value)
{
    if (keys.isEmpty()) {
        // 当键列表为空时，将最终值设置为 JSON 属性的值
        jsonObject["value"] = value;
    } else {
        // 取出第一个键
        QString key = keys.first();
        // 剩余的键列表
        QList<QString> remainingKeys = keys;
        remainingKeys.removeFirst();

        // 创建一个嵌套的 JSON 对象
        QJsonObject childObject;
        generateJson(childObject, remainingKeys, value);

        // 将嵌套的 JSON 对象设置为当前 JSON 属性的值
        jsonObject[key] = childObject;
        jsonObject.insert(keys.at(0), childObject);
    }
}

int JsonParse::SaveParasToFile()
{

    QJsonObject jsonObject;
    QHash<QString, _VALUE_ELEMENT4JSON>::iterator i;

    for (i = HASHTABLE.begin(); i != HASHTABLE.end(); i++) {

        QString Origin = i.value().name;
        QList<QString> Parents;
        while (Origin.contains(".")) {
            int DotIndex = Origin.indexOf(".");
            if (DotIndex != -1) {
                QString extractedString = Origin.left(DotIndex);
                Parents.append(extractedString);
                Origin = Origin.mid(DotIndex + 1);
            }
        }
        Parents.append(Origin); //到此为止包含了此元素的所有Parent

        //        createNestedJsonObject(jsonObject, Parents, 0, i.value().value);
        generateJson(jsonObject, Parents, i.value().value);
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
        log_singleton::Write_Log("Writing Json File Error!", Log_Level::Error);
    }

    return 0;
}

int JsonParse::InitParams()
{
    int ret = parse_app_json_file(m_filepath);
    return ret;
}

int JsonParse::ChangeParams(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    HASHTABLE.clear();
    if (InitParams())
        return 0;
    else
        return -1;
}

bool JsonParse::setParameter(QString name, double& value)
{
    bool b_ret = HASHTABLE.contains(name);
    if (b_ret) {
        QHash<QString, _VALUE_ELEMENT4JSON>::iterator _iter;
        _iter = HASHTABLE.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    } else {
        log_singleton::Write_Log("Set json parameter error", Log_Level::Error);
    }
    return b_ret;
}

bool JsonParse::setParameter(QString name, QString& value)
{
    bool b_ret = HASHTABLE.contains(name);
    if (b_ret) {
        QHash<QString, _VALUE_ELEMENT4JSON>::iterator _iter;
        _iter = HASHTABLE.find(name);
        _iter.value().value = value;
        _iter.value().bValChanged = true;
    } else {
        log_singleton::Write_Log("Set json parameter error", Log_Level::Error);
    }
    return b_ret;
}

bool JsonParse::getParameter(QString name, double& value)
{
    bool b_ret = HASHTABLE.contains(name);
    if (b_ret) {
        QHash<QString, _VALUE_ELEMENT4JSON>::iterator _iter;
        _iter = HASHTABLE.find(name);
        value = _iter.value().value.toDouble(&b_ret);
    } else
        log_singleton::Write_Log("Get json parameter error", Log_Level::Error);
    return b_ret;
}

bool JsonParse::getParameter(QString name, QString& value)
{
    bool b_ret = HASHTABLE.contains(name);
    if (b_ret) {
        QHash<QString, _VALUE_ELEMENT4JSON>::iterator _iter;
        _iter = HASHTABLE.find(name);
        value = _iter.value().value;
    } else
        log_singleton::Write_Log("Get json parameter error", Log_Level::Error);
    return b_ret;
}

int JsonParse::parse_app_json_file(QString FileName)
{
    QFile file(FileName);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        log_singleton::Write_Log("File Open Error!", Log_Level::Error);
        return -1;
    }
    QString jsonString = QString(file.readAll());
    file.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDocument.isNull()) {
        log_singleton::Write_Log("JsonFile Read Error!", Log_Level::Error);
        return -1;
    }
    parseJsonObject(jsonDocument.object());

    //    for (auto it = HASHTABLE.constBegin(); it != HASHTABLE.constEnd(); ++it) {
    //        qDebug() << it.key() << ":" << it.value().value;
    //    }
    return 0;
}

QString CurrentKey;
void JsonParse::parseJsonObject(const QJsonObject& jsonObj)
{
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        CurrentKey += it.key();
        QJsonValue currentValue = it.value();

        if (currentValue.isObject()) {
            CurrentKey += ".";
            parseJsonObject(currentValue.toObject());
            CurrentKey.chop(it.key().length() + 1);
        } else {
            _VALUE_ELEMENT4JSON element;
            element.name = CurrentKey;
            if (currentValue.isDouble()) {
                double LastValue = currentValue.toDouble();
                element.value = QString::number(LastValue);
                element.valType = J4_FLOAT64;
            } else if (currentValue.isString()) {
                QString LastValue = currentValue.toString();
                element.value = LastValue;
                element.valType = J4_QSTRING;
            }
            HASHTABLE.insert(CurrentKey, element);
            CurrentKey.chop(it.key().length());
        }
    }
}

void JsonParse::parseNestedJsonObject(const QJsonObject& jsonObj, const QString& parentKey)
{
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        QString currentKey = parentKey + "." + it.key();
        QJsonValue currentValue = it.value();
        _VALUE_ELEMENT4JSON element;
        element.name = it.key();
        if (currentValue.isDouble()) {
            double LastValue = currentValue.toDouble();
            element.value = QString::number(LastValue);
            element.valType = J4_FLOAT64;
        } else if (currentValue.isString()) {
            QString LastValue = currentValue.toString();
            element.value = LastValue;
            element.valType = J4_QSTRING;
        }
        HASHTABLE.insert(currentKey, element);
    }
}
