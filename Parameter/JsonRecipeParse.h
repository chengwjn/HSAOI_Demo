/*******************************************
    @ClassName   : JsonRecipeParse
    @Description : Json配方参数处理类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-25
********************************************/
#ifndef JSONRECIPEPARSE_H
#define JSONRECIPEPARSE_H

#include "Parameter/JsonParse.h"
#include <QObject>
#include <QString>

class JsonRecipeParse : public QObject {
    Q_OBJECT
public:
    explicit JsonRecipeParse(QObject* parent = nullptr, QString RecipeName = "DefaultRecipe");
    JsonParse* RecipeJson = nullptr;

    QString m_RecipeName;
    int RecipeParamCount = 0;

    //尺寸参数1
    double Length;
    double Width;
    double Diagonal1;
    double Diagonal2;

    //尺寸误差1
    double LengthError;
    double WidthError;
    double Diagonal1Error;
    double Diagonal2Error;

    //测试:尺寸参数2
    double Length_2;
    double Width_2;
    double Diagonal1_2;
    double Diagonal2_2;

    //测试:尺寸误差2
    double LengthError_2;
    double WidthError_2;
    double Diagonal1Error_2;
    double Diagonal2Error_2;  

    //相机1
    int Camera_LineNum[4] = { 0, 0, 0, 0 };
    double Camera_Gain[4] = { 0, 0, 0, 0 };
    int Camera_FrameCount[4] = { 0, 0, 0, 0 };
    double Camera_ExposureTime[4] = { 0.0, 0.0, 0.0, 0.0 };

private:
    void InitParams();

public:
    void ReadParams();
    void WriteParams();
    void ReadCamerasParam();
    void WriteCamerasParam();
    void ChangeParams(QString RecipeName);

signals:
};

#endif // JSONRECIPEPARSE_H
