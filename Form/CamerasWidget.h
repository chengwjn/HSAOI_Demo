/*******************************************
    @ClassName   : CamerasWidget
    @Description : Description
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-09-04
********************************************/
#ifndef CAMERASWIDGET_H
#define CAMERASWIDGET_H

#include "Camera/Dushen/DushenBasicFunc.h"
#include "Camera/Dushen/DushenCameraWidget.h"
#include <QHBoxLayout>
#include <QWidget>

namespace Ui {
class CamerasWidget;
}

class CamerasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CamerasWidget(QWidget* parent = nullptr,
        DushenBasicFunc* Camera0 = nullptr,
        DushenBasicFunc* Camera1 = nullptr,
        DushenBasicFunc* Camera2 = nullptr,
        DushenBasicFunc* Camera3 = nullptr);
    ~CamerasWidget();

private:
    Ui::CamerasWidget* ui;
    //    QGridLayout* grid_layout;
    QHBoxLayout* hbox_layout;

    DushenBasicFunc* m_Camera0;
    DushenBasicFunc* m_Camera1;
    DushenBasicFunc* m_Camera2;
    DushenBasicFunc* m_Camera3;

    DushenCameraWidget* CameraWidget0;
    DushenCameraWidget* CameraWidget1;
    DushenCameraWidget* CameraWidget2;
    DushenCameraWidget* CameraWidget3;

    void InitCameras();

public slots:
    void slot_CameraStart();
    void slot_CameraStop();
signals:
    void sig_CameraStart();
    void sig_CameraStop();
};

#endif // CAMERASWIDGET_H
