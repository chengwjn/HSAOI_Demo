#include "JsonParse.h"
#include "log_singleton.h"
#include <QString>

JsonParse::JsonParse(QString FileName)
{
    m_filepath = "Recipes/" + FileName + ".json";
    InitParams();
}

int JsonParse::SaveParasToFile()
{

    QJsonObject jsonObject;

    QHash<QString, _VALUE_ELEMENT4JSON>::iterator i;
    //    for (i = HASHTABLE.begin(); i != HASHTABLE.end(); i++) {
    //        if (!jsonObject.contains(i.value().parent)) {
    //            jsonObject.insert(i.value().parent, QJsonObject());
    //        }
    //        QJsonObject childObject = jsonObject.value(i.value().parent).toObject();
    //        if (i.value().valType == 10) {
    //            childObject.insert(i.value().name, i.value().value.toDouble());
    //        } else
    //            childObject.insert(i.value().name, i.value().value);
    //        jsonObject.insert(i.value().parent, childObject);
    //    }
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
