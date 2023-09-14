#include "DushenBasicFunc.h"
#include "log_singleton.h"
#include "mainwindow.h"

/*!
    @Function    : DushenBasicFunc
    @Description : 度申相机基类
    @Author      : Chengwenjie
    @Param1      : parent,父类
    @Param2      : CameraInfo,传入相机信息数组
    @Param3      : CameraNum,相机编号
    @Date        : 2023-07-03
*/
DushenBasicFunc::DushenBasicFunc(QObject* parent, int CameraNum, JsonRecipeParse* recipe)
    : QObject(parent)
{
    CameraParamFromRecipe = recipe;

    m_handle = 0;
    SoftTriggerFlag = false;
    fExpoTime = CameraParamFromRecipe->Camera_ExposureTime[CameraNum];
    fAnalogGain = CameraParamFromRecipe->Camera_Gain[CameraNum]; //double转float可能出现问题
    QuickRoiSel = 0;
    ColorSolutionSel = 0;
    bTrigStatus = false;
    CameraState = false;

    m_CameraNum = CameraNum;

    //预先刷新相机设备
    if (m_CameraNum == 0)
        slot_ScanFunc();
}

bool DushenBasicFunc::IsValidHandle(dvpHandle handle)
{
    bool bValidHandle;
    dvpIsValid(handle, &bValidHandle);
    return bValidHandle;
}

void DushenBasicFunc::IsMonoCamera(dvpHandle handle)
{
    // 判断相机是否为彩色相机
    dvpSensorInfo sSensorInfo;
    dvpStatus status = dvpGetSensorInfo(handle, &sSensorInfo);
    if (status == DVP_STATUS_OK) {
        if (SENSOR_PIXEL_MONO == sSensorInfo.pixel)
            bMono = true;
        else
            bMono = false;
    } else if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Get sensor information fail!");
    }
}

void DushenBasicFunc::InitSpinExpoTime()
{

    dvpDoubleDescr ExpoTimeDescr;
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        status = dvpGetExposureDescr(m_handle, &ExpoTimeDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get exposure time description fail!");
        }
        status = dvpGetExposure(m_handle, &fExpoTime);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get exposure time fail!");
        }
    }
}

void DushenBasicFunc::InitSpinGain()
{
    dvpStatus status;
    dvpFloatDescr AnalogGainDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAnalogGainDescr(m_handle, &AnalogGainDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get analog gain description fail!");
        }
        // 获取模拟增益并设置模拟增益的初始值
        status = dvpGetAnalogGain(m_handle, &fAnalogGain);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get analog gain fail!");
        }
    }
}

void DushenBasicFunc::InitAETarget()
{
    dvpStatus status;
    QString strValue;
    dvpInt32 iAETarget;
    dvpIntDescr sAETargetDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAeTargetDescr(m_handle, &sAETargetDescr);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target description fails!");
        status = dvpGetAeTarget(m_handle, &iAETarget);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target fail!");
    }
}

//初始化triggerflag，使相机进入可触发状态
void DushenBasicFunc::InitTrigger()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpGetTriggerState(m_handle, &SoftTriggerFlag);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get Trigger description fail!");
        }
    }
}

void DushenBasicFunc::InitROIMode()
{

    dvpStatus status;
    dvpSelectionDescr QuickRoiDescr;

    if (IsValidHandle(m_handle)) {
        // 获取相机分辨率索引号
        status = dvpGetQuickRoiSelDescr(m_handle, &QuickRoiDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get quick roi sel description fail!");
        } else {
            for (unsigned int iNum = 0; iNum < QuickRoiDescr.uCount; iNum++) {
                status = dvpGetQuickRoiSelDetail(m_handle, iNum, &QuickRoiDetail);
                QuickRoiDetailInfo[iNum] = (QString)QuickRoiDetail.selection.string;
                //                QuickRoiDetail++; //指针后移
            }
        }
        // 获取分辨率模式索引
        status = dvpGetResolutionModeSel(m_handle, &QuickRoiSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get roi sel fail!");
        }
    }
}

void DushenBasicFunc::InitTargetFormat()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpSetTargetFormat(m_handle, S_BGR24);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set target format fail!");
        }
    }
}

void DushenBasicFunc::InitColorSolution()
{

    dvpSelection ColorSolutionDetail;
    dvpStatus status;
    dvpSelectionDescr ColorSolutionDescr;

    if (IsValidHandle(m_handle)) {
        if (bMono)
            return;
        // 获取索引号
        status = dvpGetColorSolutionSelDescr(m_handle, &ColorSolutionDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionDescr fail!");
        } else {
            for (unsigned int iNum = 0; iNum < ColorSolutionDescr.uCount; iNum++) {
                status = dvpGetColorSolutionSelDetail(m_handle, iNum, &ColorSolutionDetail);
            }
        }
        // 获取分辨率模式索引
        status = dvpGetColorSolutionSel(m_handle, &ColorSolutionSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionSel fail!");
        }
    }
}

bool DushenBasicFunc::OpenFunc(QString DeviceName)
{
    return slot_OpenFunc(DeviceName) ? true : false;
}

void DushenBasicFunc::slot_ScanFunc()
{
    dvpStatus status;
    dvpUint32 i;

    if (!Global::IsScanned) {
        status = dvpRefresh(&Global::CameraCounts);
        QString cameramountLog = QString::fromLocal8Bit("当前相机数量为 ") + QString::number(Global::CameraCounts);
        log_singleton::Write_Log(cameramountLog, Log_Level::General);

        if (Global::CameraCounts < 1) {
            Global::IsScanned = false;
            return;
        }

        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Refresh fail!");
            Global::IsScanned = false;
            return;
        }

        if (status == DVP_STATUS_OK) {
            if (Global::CameraCounts > 16)
                Global::CameraCounts = 16;
            for (i = 0; i < Global::CameraCounts; i++) {
                //                status = dvpEnum(i, &info[i]);
                //                qDebug() << info[i].FriendlyName; //到此处相机名都未出错
                status = dvpEnum(i, &Global::info[i]);
                qDebug() << Global::info[i].FriendlyName;
            }
            Global::IsScanned = true;
        } else {
            Global::IsScanned = false;
        }
    }
}

bool DushenBasicFunc::slot_OpenFunc(QString DeviceName)
{
    dvpStatus status;

    if (!Global::IsScanned) {
        QMessageBox::about(NULL, "About", "Devices has not been SCANNED");
        return false;
    }

    for (dvpUint32 i = 0; i < Global::CameraCounts; i++) {
        if (DeviceName == tr(Global::info[i].FriendlyName)) {
            break;
        }
        if (i == (Global::CameraCounts - 1)) {
            if (DeviceName != tr(Global::info[i].FriendlyName)) {
                QMessageBox::about(NULL, "About", "No such Devices");
                return false;
            }
        }
    }

    if (!IsValidHandle(m_handle)) {
        status = dvpOpenByName(DeviceName.toLatin1().data(), OPEN_NORMAL, &m_handle);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Open the camera fail!");
            return false;
        }
        m_FriendlyName = DeviceName;

        //此处添加一系列初始化流程
        IsMonoCamera(m_handle);
        InitTrigger();
        InitAETarget();
        InitSpinExpoTime(); //初始化曝光时间
        InitSpinGain(); //初始化增益
        InitROIMode();
        InitTargetFormat();
        InitColorSolution();

        status = dvpGetStreamState(m_handle, &state);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get the stream state fail!");
            return false;
        }
        if (state == STATE_STARTED) {
            status = dvpStop(m_handle);
        }

        IsOpened = true;
        return true;
    } else {
        return false;
    }
}

void DushenBasicFunc::slot_Closefunc(QString DeviceName)
{
    dvpStatus status;

    //    if (!Global::IsScanned) {
    //        QMessageBox::about(NULL, "About", "Devices has not been SCANNED");
    //        return;
    //    }

    //    for (dvpUint32 i = 0; i < Global::CameraCounts; i++) {
    //        if (DeviceName == Global::info[i].FriendlyName) {
    //            break;
    //        }
    //        if (i == (Global::CameraCounts - 1)) {
    //            if (DeviceName != Global::info[i].FriendlyName) {
    //                QMessageBox::about(NULL, "About", "No such Devices");
    //                return;
    //            }
    //        }
    //    }

    if (!IsOpened)
        return;

    status = dvpGetStreamState(m_handle, &state);
    if (state == STATE_STARTED) {

        slot_StopFunc();
        //此处添加停止采集函数
    }
    status = dvpSaveConfig(m_handle, 0);
    status = dvpClose(m_handle);
    m_handle = 0;

    IsOpened = false;
}

void DushenBasicFunc::slot_StartFunc()
{
    if (!IsOpened)
        return;

    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        status = dvpGetStreamState(m_handle, &state);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get the stream state fail!");
        }
        if (state == STATE_STOPED) {
            status = dvpGetTriggerState(m_handle, &bTrigStatus);
            if (status != DVP_STATUS_FUNCTION_INVALID) {
                // 在启动视频流之前先设置为触发模式
                status = dvpSetTriggerState(m_handle, SoftTriggerFlag ? true : false);
                if (status != DVP_STATUS_OK) {
                    QMessageBox::about(NULL, "About", "Set status of trigger fail!");
                }
            }
            status = dvpStart(m_handle);
            if (status != DVP_STATUS_OK) {
                QMessageBox::about(NULL, "About", "Start the video stream fail!");
            } else {
                // 创建线程对象
                m_AcquireImage = new QImageAcquisition(m_handle, nullptr, Global::CameraField[m_CameraNum]);
                m_pThread = new QThread();
                m_AcquireImage->moveToThread(m_pThread);
                m_pThread->start(); // 启动采集线程

                //创建定时器
                m_timer = new QTimer(this);
                m_timer->start(1000); // 开启计算显示帧率的定时器 1000ms
                //将定时器超时信号与槽(功能函数)联系起来
                connect(m_timer, SIGNAL(timeout()), this, SLOT(slotDispRate()));
                // 建立图像显示信号和槽函数的联系
                connect(m_AcquireImage, SIGNAL(signalDisplay()), this,
                    SLOT(slotDispImage()));
                IsStarted = true;
            }
        }
    }
}

void DushenBasicFunc::slot_StopFunc()
{
    dvpStatus status = dvpStop(m_handle);
    if (status == DVP_STATUS_OK) {
        if (m_timer->isActive()) {
            m_timer->stop();
        }
        m_pThread->requestInterruption();
        m_pThread->quit();
        m_pThread->wait();
        IsStarted = false;
        //删除线程对象
        if (m_AcquireImage != NULL) {
            delete m_AcquireImage;
            m_AcquireImage = NULL;
        }
    }
}

/*!
    @Function    : slot_ShowProperty
    @Description : 打开相机属性窗口
    @Author      : Chengwenjie
    @Date        : 2023-06-25
*/
void DushenBasicFunc::slot_ShowProperty(HWND windowsID)
{
    if (IsValidHandle(m_handle)) {
        //能否显示待测试
//        QWidget* PropertyWidget = new QWidget();
#ifdef Q_OS_WIN32
        //        dvpShowPropertyModalDialog(m_handle, (HWND)PropertyWidget->winId());
        //        PropertyWidget->show();
        dvpShowPropertyModalDialog(m_handle, windowsID);
#endif
    } else {
        //        QMessageBox::about(NULL, "About", "Show Nothing");
        qDebug() << "Show Nothing";
    }
}

/*!
    @Function    : slot_TriggerFunc
    @Description : 软触发
    @Author      : Chengwenjie
    @Date        : 2023-06-28
*/
void DushenBasicFunc::slot_TriggerFunc()
{
    dvpStatus status;
    bool triggerState;

    status = dvpGetTriggerState(m_handle, &triggerState);
    if (status != DVP_STATUS_FUNCTION_INVALID) {
        status = dvpTriggerFire(m_handle);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Trigger fail!");
        }
    }
}

/*!
    @Function    : slotDispRate
    @Description : 显示帧率函数
    @Author      : Chengwenjie
    @Date        : 2023-06-21
*/
void DushenBasicFunc::slotDispRate()
{
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        //更新帧率信息
        status = dvpGetFrameCount(m_handle, &FrameCount);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get frame count fail!");
        }
        strFrameCount = QString::number(FrameCount.uFrameCount);
        strFrameRate = QString::number(FrameCount.fFrameRate);
        strFrameInfo = "采集帧数 " + strFrameCount + " 采集帧率 " + strFrameRate + " fps 显示帧率 " + QString::number(m_DisplayCount - m_DisplayCountBackUp) + " fps";
        m_DisplayCountBackUp = m_DisplayCount;
        emit sig_DeliverFrameRate(strFrameRate);
        //        QWidget::setWindowTitle(strFrameInfo);
        //        ui->label_fps->setText(strFrameInfo);
        qDebug() << strFrameInfo;
    }
}

/*!
    @Function    : slotDispImage
    @Description : 显示图片函数
    @Author      : Chengwenjie
    @Date        : 2023-06-21
*/
void DushenBasicFunc::slotDispImage()
{
    if (m_AcquireImage != NULL) {
        if (!m_AcquireImage->m_ShowImage.isNull() && m_AcquireImage->m_threadMutex.tryLock()) {
            //在此处传递图像
            //            loadedPixmapItem->loadImage(m_AcquireImage->m_ShowImage); //图形窗口加载图像
            emit sig_DeliverImage(m_AcquireImage->m_ShowImage); //带图像数据到显示控件
            m_AcquireImage->m_threadMutex.unlock();
        } else {
            return;
        }
        //        int nwith = ui->graphicsView_PreView->width(), nheight = ui->graphicsView_PreView->height();
        //将界面控件Graphics View的width和height传进类m_Image中
        //        loadedPixmapItem->setQGraphicsViewWH(nwith, nheight);
        //使视窗的大小固定在原始大小，不会随图片的放大而放大（默认状态下图片放大的时候视窗两边会自动出现滚动条，并且视窗内的视野会变大），
        //防止图片放大后重新缩小的时候视窗太大而不方便观察图片
        //        ui->graphicsView_PreView->setSceneRect(QRectF(-(nwith / 2), -(nheight /2), nwith, nheight));
        if (m_DisplayCount >= INT_MAX - 1) //防止m_DisplayCount溢出
        {
            m_DisplayCount = 0;
            m_DisplayCountBackUp = 0;
        }
        m_DisplayCount++;
    }
}

void DushenBasicFunc::slot_GetCameraState()
{
    dvpStatus status;
    dvpStreamState state;

    status = dvpGetStreamState(m_handle, &state);
    if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Get the stream state fail!");
    }

    if (state == STATE_STOPED) {
        qDebug() << "CameraState is STATE_STOPED";
        CameraState = false;
    }
    if (state == STATE_STARTED) {
        qDebug() << "CameraState is STATE_STARTED";
        CameraState = true;
    }
}

bool DushenBasicFunc::slot_SearchCamera(QString DeviceName)
{
    if (!Global::IsScanned) {
        QMessageBox::about(NULL, "About", "Devices has not been SCANNED");
        return false;
    }

    for (dvpUint32 i = 0; i < Global::CameraCounts; i++) {
        if (DeviceName == tr(Global::info[i].FriendlyName)) {
            qDebug() << "We Have This Camera " << DeviceName;
            break;
        }
        if (i == (Global::CameraCounts - 1)) {
            if (DeviceName != tr(Global::info[i].FriendlyName)) {
                qDebug() << "No such Devices";
                return false;
            }
        }
    }
    return true;
}

bool DushenBasicFunc::slot_SaveIni(QString DeviceName)
{
    char* SaveIniPath = NULL;
    QByteArray transiniVar;
    QString strSaveIni;
    dvpStatus status;

    strSaveIni = DeviceName;
    QFileInfo fi = (strSaveIni);

    if ("ini" != fi.suffix()) {
        strSaveIni = strSaveIni + ".ini";
    }

    QString currentPath = QDir::currentPath();

    QString strpath = currentPath + "/SystemParam/" + strSaveIni;
    qDebug() << strpath;

    transiniVar = strpath.toLatin1();
    SaveIniPath = transiniVar.data();

    status = dvpSaveConfig(m_handle, SaveIniPath);

    if (DVP_STATUS_OK != status) {
        QMessageBox::about(NULL, "About", "Save ini file fail!");
        return false;
    }
    return true;
}

bool DushenBasicFunc::slot_LoadIni(QString DeviceName)
{

    char* LoadPath = NULL;
    QByteArray transVar;
    dvpStatus status;

    QString currentPath = QDir::currentPath();

    strLoadPath = currentPath + "/SystemParam/" + DeviceName + ".ini"; // QFileDialog::getOpenFileName(this, tr("Get file name"), ".", tr("Files (*.ini)"));

    transVar = strLoadPath.toLatin1();
    LoadPath = transVar.data();

    status = dvpLoadConfig(m_handle, LoadPath);
    if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Load fail!");
        return false;
    }
    return true;
}
