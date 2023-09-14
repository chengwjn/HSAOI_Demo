/*******************************************
    @ClassName   : Global
    @Description : 全局变量,静态变量
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-03
********************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "Camera/DushenSample/DVPCamera.h"
#include "Parameter/XmlParse.h"
#include "log_singleton.h"

typedef struct GLASSINFO {
    int GlassID;
    bool isOK;
    bool isSizeOK;
    double GlassLength;
    double GlassWidth;
    double Diagonal1;
    double Diagonal2;
    int FlawCount;
    bool isFlawOK;
    int Flaw1;
    int Flaw2;
    int Flaw3;
    int Flaw4;
    int Flaw5;
    int Flaw6;
    int Flaw7;
} GLASSINFO;

typedef struct FlawPoint {
    double x;
    double y;
    int FlawType;
} FlawPoint;

class Global {

public:
    static void InitGlobalParam();
    static void SaveXml();
    static void ReadCameraParam();
    static void ReadLightControllerParam();

    static dvpCameraInfo info[16]; //相机信息数组
    static dvpUint32 CameraCounts; //相机数量
    static bool IsScanned; //是否已扫描

    static XmlParse XmlParam;
    static QString CurrentRecipe;

    static QString SystemName;
    static QString Camera0Name;
    static QString Camera1Name;
    static QString Camera2Name;
    static QString Camera3Name;

    static int CameraField[4];

    static QString serverIp;
    static int RegParaPort;

    //光源控制参数
    static int Addr_LightField1DelayTime;
    static int Value_LightField1DelayTime;

    static int Addr_LightField1GlowTime;
    static int Value_LightField1GlowTime;

    static int Addr_LightField2DelayTime;
    static int Value_LightField2DelayTime;

    static int Addr_LightField2GlowTime;
    static int Value_LightField2GlowTime;

    static int Addr_LightField3DelayTime;
    static int Value_LightField3DelayTime;

    static int Addr_LightField3GlowTime;
    static int Value_LightField3GlowTime;

    static int Addr_LightField4DelayTime;
    static int Value_LightField4DelayTime;

    static int Addr_LightField4GlowTime;
    static int Value_LightField4GlowTime;

    static int Addr_LightField5DelayTime;
    static int Value_LightField5DelayTime;

    static int Addr_LightField5GlowTime;
    static int Value_LightField5GlowTime;

    static int Addr_LightField6DelayTime;
    static int Value_LightField6DelayTime;

    static int Addr_LightField6GlowTime;
    static int Value_LightField6GlowTime;

    static int Addr_CameraAndLightFieldControl;
    static int Value_CameraAndLightFieldControl;

signals:
};

#endif // GLOBAL_H
