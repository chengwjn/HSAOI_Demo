#include "DushenCameraWidget.h"
#include "ui_DushenCameraWidget.h"
#include <QThread>
#include <Windows.h>

DushenCameraWidget::DushenCameraWidget(QWidget* parent, QString CameraName, int CameraNum, DushenBasicFunc* Camera)
    : QWidget(parent)
    , ui(new Ui::DushenCameraWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0); //tabWidget优先显示第一页

    //创建相机
    CameraBase = Camera;
    RealCameraName = CameraName;
    m_CameraNum = CameraNum;
    CameraFieldNum = Global::CameraField[CameraNum];
    for (dvpUint32 i = 0; i < Global::CameraCounts; i++) {
        ui->comboBox_Devices->addItem(tr(Global::info[i].FriendlyName));
    }

    //创建显示容器
    scene = new QGraphicsScene();
    ui->graphicsView_Image->setScene(scene);
    scene->clear();

    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_trigger->setEnabled(false);
    ui->pushButton_Property->setEnabled(false);
    ui->pushButton_Saveini->setEnabled(false);
    ui->pushButton_Loadini->setEnabled(false);
    ui->pushButton_Save->setEnabled(false);
    ui->comboBox_MultiFieldSelect->setEnabled(false);
    ui->pushButton_MultiFieldSelect->setEnabled(false);

    ui->tabWidget->setTabText(0, QString::fromLocal8Bit("显示"));
    ui->tabWidget->setTabText(1, QString::fromLocal8Bit("设置"));
    ui->cbx_SoftTrigger->setText(QString::fromLocal8Bit("触发使能"));
    ui->pushButton_trigger->setText(QString::fromLocal8Bit("触发"));
    ui->pushButton_Scan->setText(QString::fromLocal8Bit("扫描"));
    ui->pushButton_Property->setText(QString::fromLocal8Bit("属性"));
    ui->pushButton_Open->setText(QString::fromLocal8Bit("打开"));
    ui->pushButton_Start->setText(QString::fromLocal8Bit("准备采集"));
    ui->pushButton_Save->setText(QString::fromLocal8Bit("保存"));
    ui->pushButton_Loadini->setText(QString::fromLocal8Bit("加载配置"));
    ui->pushButton_Saveini->setText(QString::fromLocal8Bit("保存配置"));
    ui->pushButton_MultiFieldSelect->setText(QString::fromLocal8Bit("选择"));
    ui->lbl_multifield->setText(QString::fromLocal8Bit("多场选择"));

    for (int i = 0; i < 6; i++) {
        QString Text = QString::number(i + 1);
        ui->comboBox_MultiFieldSelect->addItem(Text);
    }
    int Index4combox_MultiFieldSelect = ui->comboBox_MultiFieldSelect->findText(QString::number(CameraFieldNum));
    ui->comboBox_MultiFieldSelect->setCurrentIndex(Index4combox_MultiFieldSelect);

    //开机自动启动相机
    if (Global::IsScanned) {
        AutoOpen();
        thread()->sleep(1);
        if (CameraBase->IsOpened) {
            //设置为点击触发模式
            ui->cbx_SoftTrigger->setChecked(true);
            on_pushButton_Start_clicked();
        }
    }
}

DushenCameraWidget::~DushenCameraWidget()
{
    //防止下次开启相机无法采集
    if (Global::IsScanned) {
        if (CameraBase->IsStarted) {
            CameraBase->slot_StopFunc();
            thread()->sleep(1);
            CameraBase->slot_Closefunc(RealCameraName);
        } else if (CameraBase->IsOpened) {
            CameraBase->slot_Closefunc(RealCameraName);
        }
    }
    delete ui;
}

void DushenCameraWidget::UpdateControls()
{
}

void DushenCameraWidget::on_pushButton_Scan_clicked()
{
    Global::IsScanned = false;
    CameraBase->slot_ScanFunc();
    ui->comboBox_Devices->clear();
    for (dvpUint32 i = 0; i < Global::CameraCounts; i++) {
        ui->comboBox_Devices->addItem(tr(Global::info[i].FriendlyName));
    }
}

void DushenCameraWidget::on_pushButton_Open_clicked()
{
    if (!Global::IsScanned) {
        qDebug() << "Not Scanned";
        return;
    }
    if (!CameraBase->IsOpened) {
        if (CameraBase->OpenFunc(ui->comboBox_Devices->currentText())) {
            loadedPixmapItem = new MyGraphicsItem();
            scene->addItem(loadedPixmapItem);

            connect(CameraBase, SIGNAL(sig_DeliverImage(QImage)), this, SLOT(slot_ShowImage(QImage)));
            connect(CameraBase, SIGNAL(sig_DeliverFrameRate(QString)), this, SLOT(slot_ShowFrameRate(QString)));

            ui->pushButton_Open->setText(QString::fromLocal8Bit("关闭"));
            ui->lbl_CameraName->setText(ui->comboBox_Devices->currentText());
            ui->pushButton_Start->setEnabled(true);
            ui->pushButton_Property->setEnabled(true);
            ui->pushButton_Saveini->setEnabled(true);
            ui->pushButton_Loadini->setEnabled(true);
            ui->pushButton_Save->setEnabled(true);
            ui->comboBox_MultiFieldSelect->setEnabled(true);
            ui->pushButton_MultiFieldSelect->setEnabled(true);

            on_pushButton_Loadini_clicked();
        }
    } else {
        CameraBase->slot_Closefunc(ui->lbl_CameraName->text());
        disconnect(CameraBase, SIGNAL(sig_DeliverImage(QImage)), this, SLOT(slot_ShowImage(QImage)));
        scene->removeItem(loadedPixmapItem);
        delete loadedPixmapItem;

        ui->pushButton_Open->setText(QString::fromLocal8Bit("打开"));
        ui->pushButton_Start->setEnabled(false);
        ui->pushButton_Property->setEnabled(false);
        ui->pushButton_Saveini->setEnabled(false);
        ui->pushButton_Loadini->setEnabled(false);
        ui->pushButton_Save->setEnabled(true);
        ui->comboBox_MultiFieldSelect->setEnabled(false);
        ui->pushButton_MultiFieldSelect->setEnabled(false);
    }
}

void DushenCameraWidget::on_pushButton_Start_clicked()
{
    on_cbx_SoftTrigger_clicked();

    if (!CameraBase->IsStarted) {
        CameraBase->slot_StartFunc();
        ui->pushButton_Start->setText(QString::fromLocal8Bit("停止"));
        ui->pushButton_Open->setEnabled(false);
        ui->cbx_SoftTrigger->setEnabled(false);
        if (ui->cbx_SoftTrigger->isChecked()) {
            ui->pushButton_trigger->setEnabled(true);
            ui->pushButton_trigger->setText(QString::fromLocal8Bit("单次触发"));
        } else {
            ui->pushButton_trigger->setText(QString::fromLocal8Bit("连续触发"));
        }
        ui->comboBox_MultiFieldSelect->setEnabled(false);
        ui->pushButton_MultiFieldSelect->setEnabled(false);
    } else {
        CameraBase->slot_StopFunc();
        ui->pushButton_Start->setText("Start");
        ui->pushButton_Open->setEnabled(true);
        ui->cbx_SoftTrigger->setEnabled(true);
        ui->pushButton_trigger->setEnabled(false);
        ui->comboBox_MultiFieldSelect->setEnabled(true);
        ui->pushButton_MultiFieldSelect->setEnabled(true);
    }
}

void DushenCameraWidget::on_pushButton_Property_clicked()
{
    HWND id = (HWND)this->winId(); //获得本窗口句柄
    CameraBase->slot_ShowProperty(id);
}

void DushenCameraWidget::slot_ShowImage(QImage image)
{
    loadedPixmapItem->loadImage(image);

    //缩放视野
    int nwidth = ui->graphicsView_Image->width(), nheight = ui->graphicsView_Image->height();
    loadedPixmapItem->setQGraphicsViewWH(nwidth, nheight);
    ui->graphicsView_Image->setSceneRect((QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight)));
}

void DushenCameraWidget::slot_ShowFrameRate(QString FrameRate)
{
    ui->lbl_FrameInfo->setText(FrameRate);
}

void DushenCameraWidget::on_pushButton_trigger_clicked()
{
    CameraBase->slot_TriggerFunc();
}

void DushenCameraWidget::on_cbx_SoftTrigger_clicked()
{
    CameraBase->SoftTriggerFlag = ui->cbx_SoftTrigger->isChecked() ? true : false;
}

void DushenCameraWidget::on_pushButton_Save_clicked()
{
    if (!CameraBase->IsOpened) {
        qDebug() << "Camera is not opened";
        return;
    }
    QString t_CameraNum;
    QString t_CameraFieldName;
    switch (m_CameraNum) {
    case 0:
        t_CameraNum = "Camera0";
        t_CameraFieldName = "Camera0Field";
        break;
    case 1:
        t_CameraNum = "Camera1";
        t_CameraFieldName = "Camera1Field";
        break;
    case 2:
        t_CameraNum = "Camera2";
        t_CameraFieldName = "Camera2Field";
        break;
    case 3:
        t_CameraNum = "Camera3";
        t_CameraFieldName = "Camera3Field";
        break;
    }

    QString CurrentName = ui->lbl_CameraName->text();
    Global::XmlParam.setParameter(t_CameraNum, CurrentName);
    Global::XmlParam.setParameter(t_CameraFieldName, Global::CameraField[m_CameraNum]);
    Global::XmlParam.SaveParasToFile();
}

void DushenCameraWidget::AutoOpen()
{
    if (!Global::IsScanned) {
        qDebug() << "Not Scanned";
        return;
    }
    if (!CameraBase->IsOpened) {

        //检索相机是否存在
        if (!CameraBase->slot_SearchCamera(RealCameraName)) {
            RealCameraName = ui->comboBox_Devices->currentText();
            qDebug() << "Default Camera Not matched , use The First Selection";
        }

        if (CameraBase->OpenFunc(RealCameraName)) {
            loadedPixmapItem = new MyGraphicsItem();
            connect(CameraBase, SIGNAL(sig_DeliverImage(QImage)), this, SLOT(slot_ShowImage(QImage)));
            connect(CameraBase, SIGNAL(sig_DeliverFrameRate(QString)), this, SLOT(slot_ShowFrameRate(QString)));
            scene->addItem(loadedPixmapItem);

            ui->pushButton_Open->setText(QString::fromLocal8Bit("关闭"));
            ui->lbl_CameraName->setText(RealCameraName);
            ui->pushButton_Start->setEnabled(true);
            ui->pushButton_Property->setEnabled(true);
            ui->pushButton_Saveini->setEnabled(true);
            ui->pushButton_Loadini->setEnabled(true);
            ui->pushButton_Save->setEnabled(true);
            ui->comboBox_MultiFieldSelect->setEnabled(true);
            ui->pushButton_MultiFieldSelect->setEnabled(true);

            on_pushButton_Loadini_clicked();
        }
    }
}

void DushenCameraWidget::on_pushButton_Saveini_clicked()
{
    if (CameraBase->slot_SaveIni(RealCameraName))
        qDebug() << "Save Ini Success ";
    else
        qDebug() << "Save Ini Failed";
}

void DushenCameraWidget::on_pushButton_Loadini_clicked()
{
    if (CameraBase->slot_LoadIni(RealCameraName))
        qDebug() << "Load Ini Success";
    else
        qDebug() << "Load Ini Failed";
}

void DushenCameraWidget::on_pushButton_MultiFieldSelect_clicked()
{
    //需要在打开相机而未进行采集的状态下修改要拆分的场数
    if (!CameraBase->IsStarted) {
        if (ui->comboBox_MultiFieldSelect->currentText().toInt() == Global::CameraField[m_CameraNum]) {
            qDebug() << "No Need Operation";
            return;
        }
        Global::CameraField[m_CameraNum] = ui->comboBox_MultiFieldSelect->currentText().toInt();
        on_pushButton_Save_clicked();
    }
}
