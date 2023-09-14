/*******************************************
    @ClassName   : DushenCameraWidget
    @Description : 度申相机控件类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-06-25
********************************************/
#ifndef DUSHENCAMERAWIDGET_H
#define DUSHENCAMERAWIDGET_H

#include "Camera/DushenSample/MyGraphicsitem.h"
#include "DushenBasicFunc.h"
#include "Global.h"
#include <QWidget>

namespace Ui {
class DushenCameraWidget;
}

class DushenCameraWidget : public QWidget {
    Q_OBJECT

public:
    explicit DushenCameraWidget(QWidget* parent = nullptr, QString CameraName = "", int CameraNum = 0, DushenBasicFunc* Camera = nullptr);
    ~DushenCameraWidget();

    QString RealCameraName; //相机名称
    int m_CameraNum; //第几个相机

    DushenBasicFunc* CameraBase;
    MyGraphicsItem* loadedPixmapItem;
    QGraphicsScene* scene;

    void UpdateControls();

    int CameraFieldNum;

private slots:
    void on_pushButton_Scan_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Property_clicked();

    void slot_ShowImage(QImage image);

    void slot_ShowFrameRate(QString FrameRate);

    void on_pushButton_trigger_clicked();

    void on_cbx_SoftTrigger_clicked();

    void on_pushButton_Save_clicked();

    void AutoOpen();

    void on_pushButton_Saveini_clicked();

    void on_pushButton_Loadini_clicked();

    void on_pushButton_MultiFieldSelect_clicked();

private:
    Ui::DushenCameraWidget* ui;
signals:
    void sig_SaveCameraName(QString CameraNum, QString CameraName);
};

#endif // DUSHENCAMERAWIDGET_H
