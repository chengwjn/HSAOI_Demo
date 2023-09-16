#include "mainwindow.h"
#include "QLabel"
#include "math.h"
#include "stdlib.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <halconcpp/HalconCpp.h>
#include <hdevengine/HDevEngineCpp.h>

using namespace HalconCpp;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , JsonRecipeView(NULL)
    , SystemSettings(NULL)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    Recipe = new JsonParse2Map(Global::CurrentRecipe);

    initCamera();
    initSignalPlatform();
    initMenu();
    initWindow();
    initLayout();

    this->showMaximized();

    //加定时器隔段时间刷新
    time_1 = new QTimer(this);
    //    time_1->start(100);
    connect(time_1, &QTimer::timeout, this, &MainWindow::slot_CreateNewInfo);
    //       connect(time_1, &QTimer::timeout, m_FlawShowWidget, &FlawShowWidget::slot_resize);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    m_pExit = new QAction("&退出", this);
    m_pExit->setShortcut(QKeySequence::Quit);
    m_pExit->setToolTip(tr("Exit System."));
    m_pExit->setIcon(QIcon(":/toolbar/icons/exit.png"));
    connect(m_pExit, SIGNAL(triggered()), this, SLOT(slot_CloseSystem()));
    ui->toolBar->addAction(m_pExit);

    m_pSettings = new QAction("&设置", this);
    m_pSettings->setToolTip(tr("Device Settings."));
    m_pSettings->setIcon(QIcon(":/toolbar/icons/setup.png"));
    connect(m_pSettings, SIGNAL(triggered()), this, SLOT(slot_ShowSystemSettingForm()));
    ui->toolBar->addAction(m_pSettings);

    m_pStart = new QAction("&开始", this);
    m_pStart->setToolTip(tr("Start."));
    m_pStart->setIcon(QIcon(":/toolbar/icons/start_icon.png"));
    connect(m_pStart, SIGNAL(triggered()), this, SLOT(slot_ActionStart()));
    ui->toolBar->addAction(m_pStart);

    m_pStop = new QAction("&停止", this);
    m_pStop->setToolTip(tr("Stop."));
    m_pStop->setIcon(QIcon(":/toolbar/icons/Stop.png"));
    connect(m_pStop, SIGNAL(triggered()), this, SLOT(slot_ActionStop()));
    ui->toolBar->addAction(m_pStop);
    m_pStop->setEnabled(false);

    m_pCameraSettings = new QAction("&相机", this);
    m_pCameraSettings->setToolTip(tr("CameraSet."));
    m_pCameraSettings->setIcon(QIcon(":/toolbar/icons/cameraIcon.png"));
    connect(m_pCameraSettings, SIGNAL(triggered()), this, SLOT(slot_CameraShow()));
    ui->toolBar->addAction(m_pCameraSettings);

    ui->toolBar->setIconSize(QSize(40, 40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->toggleViewAction()->setEnabled(false);
    ui->toolBar->setFloatable(false);
    ui->toolBar->setMovable(false);
}

void MainWindow::initWindow()
{
    Create_FlawShowWidget();
    Create_GlassStatisticsTable();
    Create_SingleFlawShow();
    Create_CameraShow();
}

void MainWindow::initLayout()
{
    addDockWidget(Qt::TopDockWidgetArea, Dock_FlawShowView);
    Dock_FlawShowView->setMaximumHeight(450);
    Dock_FlawShowView->setMinimumHeight(450);
    Dock_FlawShowView->setAllowedAreas(Qt::TopDockWidgetArea);

    addDockWidget(Qt::TopDockWidgetArea, Dock_CameraShow);
    Dock_CameraShow->setMaximumHeight(450);
    Dock_CameraShow->setMinimumHeight(450);
    Dock_CameraShow->setAllowedAreas(Qt::TopDockWidgetArea);

    tabifyDockWidget(Dock_FlawShowView, Dock_CameraShow);
    Dock_FlawShowView->raise(); //显示第一个tab页

    addDockWidget(Qt::BottomDockWidgetArea, Dock_SingleFlawShowView);
    Dock_SingleFlawShowView->setMinimumHeight(450);
    Dock_SingleFlawShowView->setMaximumHeight(450);
    Dock_SingleFlawShowView->setAllowedAreas(Qt::BottomDockWidgetArea);

    addDockWidget(Qt::BottomDockWidgetArea, Dock_GlassStatisticsTableView);
    Dock_GlassStatisticsTableView->setMinimumHeight(450);
    Dock_GlassStatisticsTableView->setMaximumHeight(450);
    Dock_GlassStatisticsTableView->setAllowedAreas(Qt::BottomDockWidgetArea);

    tabifyDockWidget(Dock_GlassStatisticsTableView, Dock_SingleFlawShowView);
    Dock_GlassStatisticsTableView->raise();
}

void MainWindow::initSignalPlatform()
{
    sig_comm = new RegParasComm();
    sig_comm->InitSock(Global::serverIp.toStdString().c_str(), Global::RegParaPort);
    //    sig_comm->ConnectToServer();
}

void MainWindow::Create_FlawShowWidget()
{
    Dock_FlawShowView = new QDockWidget(this);
    Dock_FlawShowView->setObjectName("FlawShow");
    Dock_FlawShowView->setWindowTitle(QString::fromLocal8Bit("缺陷示意图"));
    Dock_FlawShowView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_FlawShowWidget = new FlawShowWidget(Dock_FlawShowView, Recipe);
    Dock_FlawShowView->setWidget(m_FlawShowWidget);
    Dock_FlawShowView->setFeatures(QDockWidget::DockWidgetFloatable);
    connect(this, SIGNAL(sig_FlawWidgetChange()), m_FlawShowWidget, SLOT(slot_ChangeFlawShow()));
    connect(this, SIGNAL(sig_DeliverGlassInfo2Table(GLASSINFO*)), m_FlawShowWidget, SLOT(slot_GetGlassSize(GLASSINFO*)));
    connect(this, SIGNAL(sig_DeliverFlawPoints2Widget(QList<FlawPoint>*)), m_FlawShowWidget, SLOT(slot_GetFlawPoints(QList<FlawPoint>*)));
}

void MainWindow::Create_GlassStatisticsTable()
{
    Dock_GlassStatisticsTableView = new QDockWidget(this);
    Dock_GlassStatisticsTableView->setObjectName("GlassStatisticsTable");
    Dock_GlassStatisticsTableView->setWindowTitle("数据统计");
    Dock_GlassStatisticsTableView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_GlassStatisticTable = new GlassStatisticTableWidget(Dock_GlassStatisticsTableView);
    Dock_GlassStatisticsTableView->setWidget(m_GlassStatisticTable);
    Dock_GlassStatisticsTableView->setFeatures(QDockWidget::DockWidgetFloatable);
    connect(this, SIGNAL(sig_DeliverGlassInfo2Table(GLASSINFO*)), m_GlassStatisticTable, SLOT(slot_insertRowData(GLASSINFO*)));
}

void MainWindow::Create_SingleFlawShow()
{
    Dock_SingleFlawShowView = new QDockWidget(this);
    Dock_SingleFlawShowView->setObjectName("SingleFlaw");
    Dock_SingleFlawShowView->setWindowTitle("单个缺陷");
    Dock_SingleFlawShowView->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_SingleFlawShow = new SingleFlawShowWidget(Qt::Horizontal, Qt::Horizontal, Dock_SingleFlawShowView);
    Dock_SingleFlawShowView->setWidget(m_SingleFlawShow);
    Dock_SingleFlawShowView->setFeatures(QDockWidget::DockWidgetFloatable);
}

void MainWindow::Create_CameraShow()
{
    Dock_CameraShow = new QDockWidget(this);
    Dock_CameraShow->setObjectName("CameraShow");
    Dock_CameraShow->setWindowTitle("相机");
    Dock_CameraShow->setAllowedAreas(Qt::AllDockWidgetAreas);
    Camera_widget = new CamerasWidget(Dock_CameraShow, Camera0, Camera1, Camera2, Camera3);
    Dock_CameraShow->setWidget(Camera_widget);
    Dock_CameraShow->setFeatures(QDockWidget::DockWidgetFloatable);
    connect(this, &MainWindow::sig_StartButton2CameraStart, Camera_widget, &CamerasWidget::slot_CameraStart);
    connect(this, &MainWindow::sig_StopButton2CameraStop, Camera_widget, &CamerasWidget::slot_CameraStop);
}

void MainWindow::initCamera()
{
    Camera0 = new DushenBasicFunc(this, 0, Recipe);
    Camera1 = new DushenBasicFunc(this, 1, Recipe);
    Camera2 = new DushenBasicFunc(this, 2, Recipe);
    Camera3 = new DushenBasicFunc(this, 3, Recipe);
}

void MainWindow::slot_CloseSystem()
{
    close();
    qApp->exit(0);
}

void MainWindow::slot_ShowSystemSettingForm()
{
    if (SystemSettings == NULL) {
        SystemSettings = new SystemSettingForm(*sig_comm, *Recipe);
        connect(SystemSettings, SIGNAL(sig_Deliver_NewRecipeName2mainWindow(QString)),
            this, SLOT(slot_ChangeRecipe(QString)));
        connect(this, SIGNAL(sig_DeliverNewRecipe(JsonParse2Map*)),
            SystemSettings, SLOT(slot_JsonRecipe_Changed(JsonParse2Map*)));
    }
    SystemSettings->setWindowFlags(Qt::Window);
    SystemSettings->setWindowIcon(QIcon(":/toolbar/icons/setup.ico"));
    SystemSettings->setWindowTitle("系统设置");
    SystemSettings->show();
}

void MainWindow::slot_ActionStart()
{
    if (SystemStatus == 0) {
        log_singleton::Write_Log("开始检测!", Log_Level::General);
        SystemStatus = 1;
        emit sig_StartButton2CameraStart();
        time_1->start(50);
        m_pStart->setEnabled(false);
        m_pStop->setEnabled(true);
    }
}

void MainWindow::slot_ActionStop()
{
    if (SystemStatus == 1) {
        log_singleton::Write_Log("停止检测", Log_Level::General);
        SystemStatus = 0;
        emit sig_StopButton2CameraStop();
        time_1->stop();
        m_pStart->setEnabled(true);
        m_pStop->setEnabled(false);
    }
}

void MainWindow::slot_CameraShow()
{
    Dock_CameraShow->raise();
}

//不启用，已集成到内部
void MainWindow::slot_SaveCamera(QString CameraNum, QString CameraName)
{
    Global::XmlParam.setParameter(CameraNum, CameraName);
    Global::XmlParam.SaveParasToFile();
    qDebug() << "Camera Name saved " << CameraNum << " = " << CameraName;
}

void MainWindow::slot_ChangeRecipe(QString RecipeName)
{
    QString recipelog = "获得新工单名: " + RecipeName;
    log_singleton::Write_Log(recipelog, Log_Level::General);
    Recipe->ChangeParams(RecipeName);
    log_singleton::Write_Log("新工单已被选择", Log_Level::General);
    Global::CurrentRecipe = RecipeName;
    Global::SaveXml();
    emit sig_DeliverNewRecipe(Recipe);
    emit sig_FlawWidgetChange();
}

int OriginNum = 0;
GLASSINFO* newInfo = new GLASSINFO();
QList<FlawPoint>* FlawPointList = new QList<FlawPoint>();

void MainWindow::slot_CreateNewInfo()
{
    OriginNum++;
    newInfo->GlassID = rand();
    newInfo->isOK = OriginNum % 2 == 0 ? true : false;
    newInfo->isSizeOK = OriginNum % 3 == 0 ? true : false;

    double length;
    Recipe->getParameter("尺寸测量.长度", length);
    double width;
    Recipe->getParameter("尺寸测量.宽度", width);

    newInfo->GlassLength = (OriginNum % 3 + length);
    newInfo->GlassWidth = (OriginNum % 7 + width);
    //    newInfo->Diagonal1 = OriginNum % 3 + JsonRecipeParam->Diagonal1;
    //    newInfo->Diagonal2 = OriginNum % 7 + JsonRecipeParam->Diagonal2;
    //    newInfo->GlassLength = rand() % (int)(length)*0.95;
    //    newInfo->GlassWidth = rand() % (int)(width)*0.95;
    //    newInfo->GlassLength = 1000;
    //    newInfo->GlassWidth = 500;

    newInfo->Diagonal1 = sqrt(newInfo->GlassLength * newInfo->GlassLength + newInfo->GlassWidth * newInfo->GlassWidth) + 0.5;
    newInfo->Diagonal2 = sqrt(newInfo->GlassLength * newInfo->GlassLength + newInfo->GlassWidth * newInfo->GlassWidth) - 0.3;

    newInfo->FlawCount = OriginNum * 7 + 21;
    newInfo->isFlawOK = OriginNum % 5 == 0 ? true : false;

    newInfo->Flaw1 = OriginNum;
    newInfo->Flaw2 = OriginNum + 1;
    newInfo->Flaw3 = OriginNum + 2;
    newInfo->Flaw4 = OriginNum + 3;
    newInfo->Flaw5 = OriginNum + 4;
    newInfo->Flaw6 = OriginNum + 5;
    newInfo->Flaw7 = OriginNum + 6;

    if (OriginNum > 15)
        OriginNum = 0;
    //    qDebug() << QString::number(OriginNum) << "," << QString::number(newInfo->GlassID);

    FlawPointList->clear();

    //    InfoMutex.lock();

    for (int i = 0; i < 14; i++) {
        FlawPoint point;
        //        point.x = (i + 10) * (i + 10) + OriginNum * 30;
        //        point.y = (i + 20) * (2 + 10) + OriginNum * 40;

        point.x = rand() % (int)(newInfo->GlassLength);
        point.y = rand() % (int)(newInfo->GlassWidth);

        point.FlawType = i % 7;
        FlawPointList->append(point);
    }

    //    InfoMutex.unlock();
    emit sig_DeliverGlassInfo2Table(newInfo);
    emit sig_DeliverFlawPoints2Widget(FlawPointList);
    m_FlawShowWidget->slot_resize();
}

void MainWindow::CalcPoints(double length, double width)
{
    for (int i = 0; i < 14; i++) {
        FlawPoint point;
        point.x = (rand() % (int)(length));
        point.y = (rand() % (int)(width));
        point.FlawType = i % 7;
        FlawPointList->append(point);
    }
}
