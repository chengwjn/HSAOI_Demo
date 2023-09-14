#include "JsonRecipeParse.h"

JsonRecipeParse::JsonRecipeParse(QObject* parent, QString RecipeName)
    : QObject(parent)
{
    ChangeParams(RecipeName);
}

void JsonRecipeParse::InitParams()
{
    ReadParams();
    ReadCamerasParam();
}

void JsonRecipeParse::ReadParams()
{
    QString parent4GlassMeasure = QString::fromLocal8Bit("尺寸测量");
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("长度"), Length);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("宽度"), Width);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线1"), Diagonal1);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线2"), Diagonal2);

    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("长度_误差"), LengthError);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("宽度_误差"), WidthError);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线1_误差"), Diagonal1Error);
    RecipeJson->getParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线2_误差"), Diagonal2Error);

    QString parent4GlassMeasure2 = "GlassMeasure2";
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Length_2", Length_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Width_2", Width_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Diagonal1_2", Diagonal1_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Diagonal2_2", Diagonal2_2);

    RecipeJson->getParameter(parent4GlassMeasure2 + ".LengthError_2", LengthError_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".WidthError_2", WidthError_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Diagonal1Error_2", Diagonal1Error_2);
    RecipeJson->getParameter(parent4GlassMeasure2 + ".Diagonal2Error_2", Diagonal2Error_2);

    RecipeParamCount = 16;
}

void JsonRecipeParse::WriteParams()
{
    QString parent4GlassMeasure = QString::fromLocal8Bit("尺寸测量");
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("长度"), Length);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("宽度"), Width);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线1"), Diagonal1);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线2"), Diagonal2);

    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("长度_误差"), LengthError);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("宽度_误差"), WidthError);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线1_误差"), Diagonal1Error);
    RecipeJson->setParameter(parent4GlassMeasure + "." + QString::fromLocal8Bit("对角线2_误差"), Diagonal2Error);

    QString parent4GlassMeasure2 = "GlassMeasure2";
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Length_2", Length_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Width_2", Width_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Diagonal1_2", Diagonal1_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Diagonal2_2", Diagonal2_2);

    RecipeJson->setParameter(parent4GlassMeasure2 + ".LengthError_2", LengthError_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".WidthError_2", WidthError_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Diagonal1Error_2", Diagonal1Error_2);
    RecipeJson->setParameter(parent4GlassMeasure2 + ".Diagonal2Error_2", Diagonal2Error_2);

    RecipeJson->SaveParasToFile();
}

void JsonRecipeParse::ReadCamerasParam()
{
    QString parent4Camera0 = QString::fromLocal8Bit("相机0");
    RecipeJson->getParameter(parent4Camera0 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[0]);
    RecipeJson->getParameter(parent4Camera0 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[0]);
    RecipeJson->getParameter(parent4Camera0 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[0]);
    RecipeJson->getParameter(parent4Camera0 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[0]);

    QString parent4Camera1 = QString::fromLocal8Bit("相机1");
    RecipeJson->getParameter(parent4Camera1 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[1]);
    RecipeJson->getParameter(parent4Camera1 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[1]);
    RecipeJson->getParameter(parent4Camera1 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[1]);
    RecipeJson->getParameter(parent4Camera1 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[1]);

    QString parent4Camera2 = QString::fromLocal8Bit("相机2");
    RecipeJson->getParameter(parent4Camera2 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[2]);
    RecipeJson->getParameter(parent4Camera2 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[2]);
    RecipeJson->getParameter(parent4Camera2 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[2]);
    RecipeJson->getParameter(parent4Camera2 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[2]);

    QString parent4Camera3 = QString::fromLocal8Bit("相机3");
    RecipeJson->getParameter(parent4Camera3 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[3]);
    RecipeJson->getParameter(parent4Camera3 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[3]);
    RecipeJson->getParameter(parent4Camera3 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[3]);
    RecipeJson->getParameter(parent4Camera3 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[3]);
}

void JsonRecipeParse::WriteCamerasParam()
{
    QString parent4Camera0 = QString::fromLocal8Bit("相机0");
    RecipeJson->setParameter(parent4Camera0 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[0]);
    RecipeJson->setParameter(parent4Camera0 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[0]);
    RecipeJson->setParameter(parent4Camera0 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[0]);
    RecipeJson->setParameter(parent4Camera0 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[0]);

    QString parent4Camera1 = QString::fromLocal8Bit("相机1");
    RecipeJson->setParameter(parent4Camera1 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[1]);
    RecipeJson->setParameter(parent4Camera1 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[1]);
    RecipeJson->setParameter(parent4Camera1 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[1]);
    RecipeJson->setParameter(parent4Camera1 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[1]);

    QString parent4Camera2 = QString::fromLocal8Bit("相机2");
    RecipeJson->setParameter(parent4Camera2 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[2]);
    RecipeJson->setParameter(parent4Camera2 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[2]);
    RecipeJson->setParameter(parent4Camera2 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[2]);
    RecipeJson->setParameter(parent4Camera2 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[2]);

    QString parent4Camera3 = QString::fromLocal8Bit("相机3");
    RecipeJson->setParameter(parent4Camera3 + "." + QString::fromLocal8Bit("拍照行数"), Camera_LineNum[3]);
    RecipeJson->setParameter(parent4Camera3 + "." + QString::fromLocal8Bit("相机增益"), Camera_Gain[3]);
    RecipeJson->setParameter(parent4Camera3 + "." + QString::fromLocal8Bit("帧次"), Camera_FrameCount[3]);
    RecipeJson->setParameter(parent4Camera3 + "." + QString::fromLocal8Bit("曝光时间"), Camera_ExposureTime[3]);

    RecipeJson->SaveParasToFile();
}

void JsonRecipeParse::ChangeParams(QString RecipeName)
{
    m_RecipeName = RecipeName;
    QString Recipe_Addr = "Recipes/" + m_RecipeName + ".json";
    if (RecipeJson != nullptr)
        delete RecipeJson;
    RecipeJson = new JsonParse(Recipe_Addr);
    InitParams();
}
