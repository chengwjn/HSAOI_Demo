#include "JsonParse.h"
#include "log_singleton.h"
#include <QString>

JsonParse::JsonParse(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    ReadParamsFromFile();
}

void createNestedJsonObject(QJsonObject& parentObject, const QList<QString>& keys, int depth, QString finalValue)
{
    if (depth >= keys.size()) {
        return;
    }

    QString currentKey = keys.at(depth);
    if (depth == keys.size() - 1) {
        parentObject[currentKey] = finalValue;
    } else {
        if (!parentObject.contains(currentKey)) {
            parentObject[currentKey] = QJsonObject();
        }

        QJsonObject currentObject = parentObject[currentKey].toObject();
        createNestedJsonObject(currentObject, keys, depth + 1, finalValue);

        parentObject[currentKey] = currentObject;
    }
}

int JsonParse::SaveParamsToFile()
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
        Parents.append(Origin);
        createNestedJsonObject(jsonObject, Parents, 0, i.value().value);
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

int JsonParse::ReadParamsFromFile()
{
    int ret = ParseJsonFile(m_filepath);
    return ret;
}

int JsonParse::ChangeParams(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    HASHTABLE.clear();
    if (ReadParamsFromFile())
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

int JsonParse::ParseJsonFile(QString FileName)
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
    ParseJsonObject(jsonDocument.object());

    //    for (auto it = HASHTABLE.constBegin(); it != HASHTABLE.constEnd(); ++it) {
    //        qDebug() << it.key() << ":" << it.value().value;
    //    }
    return 0;
}

QString CurrentKey;
void JsonParse::ParseJsonObject(const QJsonObject& jsonObj)
{
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        CurrentKey += it.key();
        QJsonValue currentValue = it.value();

        if (currentValue.isObject()) {
            CurrentKey += ".";
            ParseJsonObject(currentValue.toObject());
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
                qDebug() << LastValue;
                element.value = LastValue;
                element.valType = J4_QSTRING;
            }
            HASHTABLE.insert(CurrentKey, element); //至此为止参数全部写入Hash表
            CurrentKey.chop(it.key().length());
        }
    }
}
