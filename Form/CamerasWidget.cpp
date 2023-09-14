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

    connect(this, SIGNAL(sig_CameraStart()), CameraWidget0, SLOT(slot_StartCamera()));
    connect(this, SIGNAL(sig_CameraStart()), CameraWidget1, SLOT(slot_StartCamera()));
    connect(this, SIGNAL(sig_CameraStart()), CameraWidget2, SLOT(slot_StartCamera()));
    connect(this, SIGNAL(sig_CameraStart()), CameraWidget3, SLOT(slot_StartCamera()));

    connect(this, SIGNAL(sig_CameraStop()), CameraWidget0, SLOT(slot_CameraStop()));
    connect(this, SIGNAL(sig_CameraStop()), CameraWidget1, SLOT(slot_CameraStop()));
    connect(this, SIGNAL(sig_CameraStop()), CameraWidget2, SLOT(slot_CameraStop()));
    connect(this, SIGNAL(sig_CameraStop()), CameraWidget3, SLOT(slot_CameraStop()));

    hbox_layout->addWidget(CameraWidget0);
    hbox_layout->addWidget(CameraWidget1);
    hbox_layout->addWidget(CameraWidget2);
    hbox_layout->addWidget(CameraWidget3);
}

void CamerasWidget::slot_CameraStart()
{
    emit sig_CameraStart();
}

void CamerasWidget::slot_CameraStop()
{
    emit sig_CameraStop();
}
