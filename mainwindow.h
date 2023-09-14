#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Camera/Dushen/DushenBasicFunc.h"
#include "Form/CamerasWidget.h"
#include "Form/FlawShowWidget.h"
#include "Form/glassstatictablewidget.h"
#include "Form/singleflawshowwidget.h"
#include "Global.h"
#include "LightControl/LightControl.h"
#include "Parameter/JsonParse.h"
#include "Parameter/JsonRecipeWidget.h"
#include "Parameter/RecipeParse.h"
#include "Parameter/RecipeWidget.h"
#include "SystemSettingForm.h"
#include "log_singleton.h"
#include <QDockWidget>
#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //工单
    JsonRecipeParse* JsonRecipeParam;

    //相机
    DushenBasicFunc* Camera0;
    DushenBasicFunc* Camera1;
    DushenBasicFunc* Camera2;
    DushenBasicFunc* Camera3;

    JsonRecipeWidget* JsonRecipeView;
    SystemSettingForm* SystemSettings;

    int SystemStatus = 0; //0停止，1采集

    RegParasComm* sig_comm;

private:
    Ui::MainWindow* ui;

    void initCamera();

    QAction* m_pExit;
    QAction* m_pSettings;
    QAction* m_pStart;
    QAction* m_pStop;
    QAction* m_pCameraSettings;

    void initMenu(); //初始化菜单
    void initWindow(); //初始化窗口
    void initLayout(); //初始化Widget靠位
    void initSignalPlatform(); //初始化信号平台

    FlawShowWidget* m_FlawShowWidget;
    GlassStatisticTableWidget* m_GlassStatisticTable;
    SingleFlawShowWidget* m_SingleFlawShow;
    CamerasWidget* Camera_widget;

    QDockWidget* Dock_FlawShowView;
    QDockWidget* Dock_GlassStatisticsTableView;
    QDockWidget* Dock_SingleFlawShowView;
    QDockWidget* Dock_CameraShow;

    void Create_FlawShowWidget();
    void Create_GlassStatisticsTable();
    void Create_SingleFlawShow();
    void Create_CameraShow();

    void CalcPoints(double length, double width);
    QMutex InfoMutex;

    QTimer* time_1;
private slots:
    void slot_CloseSystem();
    void slot_ShowSystemSettingForm();
    void slot_ActionStart();
    void slot_ActionStop();
    void slot_CameraShow();

public slots:
    void slot_SaveCamera(QString CameraNum, QString CameraName); //不启用
    void slot_ChangeRecipe(QString RecipeName);

    void slot_CreateNewInfo();
    void slot_FromSystemSettings_FlawWidgetNeedReplot();
signals:
    void sig_DeliverNewRecipe(JsonRecipeParse* Recipe);
    void sig_FlawWidgetChange();

    void sig_DeliverGlassInfo2Table(GLASSINFO* info);
    void sig_DeliverFlawPoints2Widget(QList<FlawPoint>* points);
};
#endif // MAINWINDOW_H
