#include "Global.h"
#include "log_singleton.h"

void Global::InitGlobalParam()
{
    CameraCounts = 0;
    IsScanned = false;

    XmlParam.getParameter("CurrentRecipe", CurrentRecipe);
    XmlParam.getParameter("SystemName", SystemName);

    QString CurrentRecipeNameLog = "获得当前工单: " + CurrentRecipe;
    QString SystemNameLog = "获得当前项目名: " + SystemName;
    log_singleton::Write_Log(CurrentRecipeNameLog, Log_Level::General);
    log_singleton::Write_Log(SystemNameLog, Log_Level::General);

    ReadCameraParam();
    ReadLightControllerParam();
}

void Global::SaveXml()
{
    XmlParam.setParameter("CurrentRecipe", CurrentRecipe);
    XmlParam.SaveParasToFile();

    QString SaveXmlLog = "工单参数已设置完成 ";
    log_singleton::Write_Log(SaveXmlLog, Log_Level::Urgent);
}

void Global::ReadCameraParam()
{
    XmlParam.getParameter("Camera0", Camera0Name);
    XmlParam.getParameter("Camera1", Camera1Name);
    XmlParam.getParameter("Camera2", Camera2Name);
    XmlParam.getParameter("Camera3", Camera3Name);

    XmlParam.getParameter("Camera0Field", CameraField[0]);
    XmlParam.getParameter("Camera1Field", CameraField[1]);
    XmlParam.getParameter("Camera2Field", CameraField[2]);
    XmlParam.getParameter("Camera3Field", CameraField[3]);
}

void Global::ReadLightControllerParam()
{
    XmlParam.getParameter("serverIp", serverIp);
    XmlParam.getParameter("RegParaPort", RegParaPort);

    XmlParam.getAddress("LightField1DelayTime", Addr_LightField1DelayTime);
    XmlParam.getParameter("LightField1DelayTime", Value_LightField1DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField1DelayTime, 16) << ",value = " << Value_LightField1DelayTime;

    XmlParam.getAddress("LightField1GlowTime", Addr_LightField1GlowTime);
    XmlParam.getParameter("LightField1GlowTime", Value_LightField1GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField1GlowTime, 16) << ",value = " << Value_LightField1GlowTime;

    XmlParam.getAddress("LightField2DelayTime", Addr_LightField2DelayTime);
    XmlParam.getParameter("LightField2DelayTime", Value_LightField2DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField2DelayTime, 16) << ",value = " << Value_LightField2DelayTime;

    XmlParam.getAddress("LightField2GlowTime", Addr_LightField2GlowTime);
    XmlParam.getParameter("LightField2GlowTime", Value_LightField2GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField2GlowTime, 16) << ",value = " << Value_LightField2GlowTime;

    XmlParam.getAddress("LightField3DelayTime", Addr_LightField3DelayTime);
    XmlParam.getParameter("LightField3DelayTime", Value_LightField3DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField3DelayTime, 16) << ",value = " << Value_LightField3DelayTime;

    XmlParam.getAddress("LightField3GlowTime", Addr_LightField3GlowTime);
    XmlParam.getParameter("LightField3GlowTime", Value_LightField3GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField3GlowTime, 16) << ",value = " << Value_LightField3GlowTime;

    XmlParam.getAddress("LightField4DelayTime", Addr_LightField4DelayTime);
    XmlParam.getParameter("LightField4DelayTime", Value_LightField4DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField4DelayTime, 16) << ",value = " << Value_LightField4DelayTime;

    XmlParam.getAddress("LightField4GlowTime", Addr_LightField4GlowTime);
    XmlParam.getParameter("LightField4GlowTime", Value_LightField4GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField4GlowTime, 16) << ",value = " << Value_LightField4GlowTime;

    XmlParam.getAddress("LightField5DelayTime", Addr_LightField5DelayTime);
    XmlParam.getParameter("LightField5DelayTime", Value_LightField5DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField5DelayTime, 16) << ",value = " << Value_LightField5DelayTime;

    XmlParam.getAddress("LightField5GlowTime", Addr_LightField5GlowTime);
    XmlParam.getParameter("LightField5GlowTime", Value_LightField5GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField5GlowTime, 16) << ",value = " << Value_LightField5GlowTime;

    XmlParam.getAddress("LightField6DelayTime", Addr_LightField6DelayTime);
    XmlParam.getParameter("LightField6DelayTime", Value_LightField6DelayTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField6DelayTime, 16) << ",value = " << Value_LightField6DelayTime;

    XmlParam.getAddress("LightField6GlowTime", Addr_LightField6GlowTime);
    XmlParam.getParameter("LightField6GlowTime", Value_LightField6GlowTime);
    //    qDebug() << "Addr = " << QString::number(Addr_LightField6GlowTime, 16) << ",value = " << Value_LightField6GlowTime;

    XmlParam.getAddress("CameraAndLightFieldControl", Addr_CameraAndLightFieldControl);
    XmlParam.getParameter("CameraAndLightFieldControl", Value_CameraAndLightFieldControl);
    //    qDebug() << "Addr = " << QString::number(Addr_CameraAndLightFieldControl, 16) << ",value = " << Value_CameraAndLightFieldControl;
}

//定义静态成员变量
dvpCameraInfo Global::info[16];
dvpUint32 Global::CameraCounts; //相机数量
bool Global::IsScanned; //是否已扫描
XmlParse Global::XmlParam("SystemParam/SystemParam.xml");
QString Global::CurrentRecipe;
QString Global::SystemName;
QString Global::Camera0Name;
QString Global::Camera1Name;
QString Global::Camera2Name;
QString Global::Camera3Name;
int Global::CameraField[4];

QString Global::serverIp;
int Global::RegParaPort;

int Global::Addr_LightField1DelayTime;
int Global::Value_LightField1DelayTime;

int Global::Addr_LightField1GlowTime;
int Global::Value_LightField1GlowTime;

int Global::Addr_LightField2DelayTime;
int Global::Value_LightField2DelayTime;

int Global::Addr_LightField2GlowTime;
int Global::Value_LightField2GlowTime;

int Global::Addr_LightField3DelayTime;
int Global::Value_LightField3DelayTime;

int Global::Addr_LightField3GlowTime;
int Global::Value_LightField3GlowTime;

int Global::Addr_LightField4DelayTime;
int Global::Value_LightField4DelayTime;

int Global::Addr_LightField4GlowTime;
int Global::Value_LightField4GlowTime;

int Global::Addr_LightField5DelayTime;
int Global::Value_LightField5DelayTime;

int Global::Addr_LightField5GlowTime;
int Global::Value_LightField5GlowTime;

int Global::Addr_LightField6DelayTime;
int Global::Value_LightField6DelayTime;

int Global::Addr_LightField6GlowTime;
int Global::Value_LightField6GlowTime;

int Global::Addr_CameraAndLightFieldControl;
int Global::Value_CameraAndLightFieldControl;
