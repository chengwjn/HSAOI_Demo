/*******************************************
    @ClassName   : DushenBasicFunc
    @Description : 度申相机基类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-06-20
********************************************/
#ifndef DUSHENBASICFUNC_H
#define DUSHENBASICFUNC_H

#include "Camera/DushenSample/ImageAcquisition.h"
#include "Global.h"
//#include "Parameter/JsonRecipeParse.h"
#include "Parameter/JsonParse2Map.h"
#include <QDir>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>

class DushenBasicFunc : public QObject {
    Q_OBJECT
public:
    explicit DushenBasicFunc(QObject* parent = nullptr, int CameraNum = 999, JsonParse2Map* recipe = nullptr);

    //    JsonRecipeParse* CameraParamFromRecipe;
    JsonParse2Map* m_recipe;

    QImageAcquisition* m_AcquireImage; //图像采集线程对象的指针

    bool IsValidHandle(dvpHandle handle); //检查相机是否存在
    void IsMonoCamera(dvpHandle handle); //检查是否为黑白相机
    void InitSpinExpoTime(); //初始化曝光时间
    void InitSpinGain(); //初始化增益
    void InitAEMode();
    void InitAETarget();
    void InitTrigger(); //初始化trigger
    void InitROIMode();
    void InitTargetFormat();
    void InitColorSolution();

    int m_CameraNum;

    double fExpoTime; //曝光时间
    float fAnalogGain; //增益
    dvpQuickRoi QuickRoiDetail;
    QString QuickRoiDetailInfo[16];
    dvpUint32 QuickRoiSel;
    dvpUint32 ColorSolutionSel;
    bool bTrigStatus;
    bool IsOpened = false;
    bool CameraState;
    bool IsStarted = false;

    unsigned int m_DisplayCount;
    unsigned int m_DisplayCountBackUp;
    QString strFrameInfo; // 帧数信息
    bool SoftTriggerFlag; // 软触发信号
    bool bMono;
    QString strFrameCount; // 相机获取到的图像帧数
    QString strFrameRate; // 图像获取帧率

    QString strFilePath; // 保存图像时用到的完整路径
    QString strDir; // 图像保存的路径
    QString strLoadPath;
    QString m_FriendlyName;

    dvpStreamState state;

private:
    dvpHandle m_handle;

    dvpFrameCount FrameCount;

    QThread* m_pThread = nullptr;
    QTimer* m_timer; // 定时器

protected:
    void changeEvent(QEvent* e);
    //    virtual void closeEvent(QEvent* e);
signals:
    void sig_DeliverImage(QImage);
    void sig_DeliverFrameRate(QString);

public:
    bool OpenFunc(QString DeviceName);
private slots:
    bool slot_OpenFunc(QString DeviceName);
public slots:
    void slot_ScanFunc();
    void slot_Closefunc(QString DeviceName);
    void slot_StartFunc();
    void slot_StopFunc();
    void slot_ShowProperty(HWND windowsID);
    void slot_TriggerFunc();

    void slotDispRate();
    void slotDispImage();

    void slot_GetCameraState();

    bool slot_SearchCamera(QString DeviceName);
    bool slot_SaveIni(QString DeviceName);
    bool slot_LoadIni(QString DeviceName);
};

#endif // DUSHENBASICFUNC_H
