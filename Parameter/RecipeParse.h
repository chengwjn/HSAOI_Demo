/*******************************************
    @ClassName   : RecipeParse
    @Description : 配方参数处理类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-05
********************************************/
#ifndef RECIPEPARSE_H
#define RECIPEPARSE_H

#include "Parameter/XmlParse.h"
#include <QObject>
#include <QString>

class RecipeParse : public QObject {
    Q_OBJECT
public:
    explicit RecipeParse(QObject* parent = nullptr, QString RecipeName = "");

    XmlParse* RecipeXml;

    QString m_RecipeName;
    //尺寸参数
    float Read_Length;
    float Read_Width;
    float Read_Diagonal1;
    float Read_Diagonal2;

    //尺寸误差
    float Read_LengthError;
    float Read_WidthError;
    float Read_Diagonal1Error;
    float Read_Diagonal2Error;

private:
    void InitParams();

public:
    void ReadParams();
    void WriteParams();
signals:
};

#endif // RECIPEPARSE_H
