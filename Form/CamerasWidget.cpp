#include "CamerasWidget.h"
#include "Global.h"
#include "ui_CamerasWidget.h"

CamerasWidget::CamerasWidget(QWidget* parent, DushenBasicFunc* Camera0,
    DushenBasicFunc* Camera1, DushenBasicFunc* Camera2,
    DushenBasicFunc* Camera3)
    : QWidget(parent)
    , ui(new Ui::CamerasWidget)
{
    ui->setupUi(this);

    m_Camera0 = Camera0;
    m_Camera1 = Camera1;
    m_Camera2 = Camera2;
    m_Camera3 = Camera3;

    hbox_layout = new QHBoxLayout(this);
    InitCameras();
    //    this->setFixedSize(QSize(1750, 400));
    this->setLayout(hbox_layout);
}

CamerasWidget::~CamerasWidget() { delete ui; }

void CamerasWidget::InitCameras()
{
    CameraWidget0 = new DushenCameraWidget(this, Global::Camera0Name, 0, m_Camera0);
    CameraWidget1 = new DushenCameraWidget(this, Global::Camera1Name, 1, m_Camera1);
    CameraWidget2 = new DushenCameraWidget(this, Global::Camera2Name, 2, m_Camera2);
    CameraWidget3 = new DushenCameraWidget(this, Global::Camera3Name, 3, m_Camera3);

    hbox_layout->addWidget(CameraWidget0);
    hbox_layout->addWidget(CameraWidget1);
    hbox_layout->addWidget(CameraWidget2);
    hbox_layout->addWidget(CameraWidget3);
}
