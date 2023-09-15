#include "LightControl.h"
#include "ui_LightControl.h"
#include <QMessageBox>
#include <QTimer>

LightControl::LightControl(RegParasComm& sig_comm, QWidget* parent)
    : QWidget(parent)
    , m_pSig_comm(sig_comm)
    , ui(new Ui::LightControl)
{

    ui->setupUi(this);

    ui->treeWidget->setColumnWidth(0, 150);

    Layout0 = new QHBoxLayout(this);
    Layout1 = new QVBoxLayout(this);

    this->setLayout(Layout0);
    Layout0->addWidget(ui->treeWidget);

    Layout0->addLayout(Layout1);

    Layout1->addWidget(ui->Get);
    Layout1->addWidget(ui->Set);
    Layout1->addWidget(ui->Save);
    Layout1->setAlignment(Qt::AlignTop);

    ui->Get->setText("获取参数");
    ui->Set->setText("设置参数");
    ui->Save->setText("保存");

    specificItem0 = ui->treeWidget->topLevelItem(0);
    childItem0 = specificItem0->child(0);
    childItem1 = specificItem0->child(1);
    childItem2 = specificItem0->child(2);
    childItem3 = specificItem0->child(3);
    childItem4 = specificItem0->child(4);
    childItem5 = specificItem0->child(5);
    childItem6 = specificItem0->child(6);
    childItem7 = specificItem0->child(7);

    specificItem1 = ui->treeWidget->topLevelItem(1);
    childItem8 = specificItem1->child(0);
    childItem9 = specificItem1->child(1);
    childItem10 = specificItem1->child(2);
    childItem11 = specificItem1->child(3);
    childItem12 = specificItem1->child(4);
    childItem13 = specificItem1->child(5);
    childItem14 = specificItem1->child(6);
    childItem15 = specificItem1->child(7);
    childItem16 = specificItem1->child(8);
    childItem17 = specificItem1->child(9);
    childItem18 = specificItem1->child(10);

    specificItem2 = ui->treeWidget->topLevelItem(2);
    childItem19 = specificItem2->child(0);
    childItem20 = specificItem2->child(1);
    childItem21 = specificItem2->child(2);
    childItem22 = specificItem2->child(3);
    childItem23 = specificItem2->child(4);
    childItem24 = specificItem2->child(5);
    childItem25 = specificItem2->child(6);
    childItem26 = specificItem2->child(7);
    childItem27 = specificItem2->child(8);
    childItem28 = specificItem2->child(9);
    childItem29 = specificItem2->child(10);
    childItem30 = specificItem2->child(11);
    childItem31 = specificItem2->child(12);
    childItem32 = specificItem2->child(13);

    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &LightControl::onItemDoubleClicked);

    connect(ui->Set, SIGNAL(clicked()), this, SLOT(slot_setButton_clicked()));
    connect(ui->Get, SIGNAL(clicked()), this, SLOT(slot_getButton_clicked()));
    connect(ui->Save, SIGNAL(clicked()), this, SLOT(slot_saveButton_clicked()));

    slot_getButton_clicked();
    ui->treeWidget->expandAll();
}

void LightControl::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (column == 1) { // Check if the clicked column is not the second column
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
}

LightControl::~LightControl()
{
    delete ui;
}

void LightControl::slot_getButton_clicked()
{
    unsigned int temp[33];

    m_pSig_comm.GetRegs(ADDR0, ADDR0, &temp[0]);
    m_pSig_comm.GetRegs(ADDR0, ADDR0, &temp[0]);
    m_pSig_comm.GetRegs(ADDR1, ADDR1, &temp[1]);
    m_pSig_comm.GetRegs(ADDR2, ADDR2, &temp[2]);
    m_pSig_comm.GetRegs(ADDR3, ADDR3, &temp[3]);
    m_pSig_comm.GetRegs(ADDR4, ADDR4, &temp[4]);
    m_pSig_comm.GetRegs(ADDR5, ADDR5, &temp[5]);
    m_pSig_comm.GetRegs(ADDR6, ADDR6, &temp[6]);
    m_pSig_comm.GetRegs(ADDR7, ADDR7, &temp[7]);
    m_pSig_comm.GetRegs(ADDR8, ADDR8, &temp[8]);
    m_pSig_comm.GetRegs(ADDR9, ADDR9, &temp[9]);
    m_pSig_comm.GetRegs(ADDR10, ADDR10, &temp[10]);
    m_pSig_comm.GetRegs(ADDR11, ADDR11, &temp[11]);
    m_pSig_comm.GetRegs(ADDR12, ADDR12, &temp[12]);
    m_pSig_comm.GetRegs(ADDR13, ADDR13, &temp[13]);
    m_pSig_comm.GetRegs(ADDR14, ADDR14, &temp[14]);
    m_pSig_comm.GetRegs(ADDR15, ADDR15, &temp[15]);
    m_pSig_comm.GetRegs(ADDR16, ADDR16, &temp[16]);
    m_pSig_comm.GetRegs(ADDR17, ADDR17, &temp[17]);
    m_pSig_comm.GetRegs(ADDR18, ADDR18, &temp[18]);
    m_pSig_comm.GetRegs(ADDR19, ADDR19, &temp[19]);
    m_pSig_comm.GetRegs(ADDR20, ADDR20, &temp[20]);
    m_pSig_comm.GetRegs(ADDR21, ADDR21, &temp[21]);
    m_pSig_comm.GetRegs(ADDR22, ADDR22, &temp[22]);
    m_pSig_comm.GetRegs(ADDR23, ADDR23, &temp[23]);
    m_pSig_comm.GetRegs(ADDR24, ADDR24, &temp[24]);
    m_pSig_comm.GetRegs(ADDR25, ADDR25, &temp[25]);
    m_pSig_comm.GetRegs(ADDR26, ADDR26, &temp[26]);
    m_pSig_comm.GetRegs(ADDR27, ADDR27, &temp[27]);
    m_pSig_comm.GetRegs(ADDR28, ADDR28, &temp[28]);
    m_pSig_comm.GetRegs(ADDR29, ADDR29, &temp[29]);
    m_pSig_comm.GetRegs(ADDR30, ADDR30, &temp[30]);
    m_pSig_comm.GetRegs(ADDR31, ADDR31, &temp[31]);
    m_pSig_comm.GetRegs(ADDR32, ADDR32, &temp[32]);
    childItem0->setText(1, QString::number(temp[0]));
    childItem1->setText(1, QString::number(temp[1]));
    childItem2->setText(1, QString::number(temp[2]));
    childItem3->setText(1, QString::number(temp[3]));
    childItem4->setText(1, QString::number(temp[4]));
    childItem5->setText(1, QString::number(temp[5]));
    childItem6->setText(1, QString::number(temp[6]));
    childItem7->setText(1, QString::number(temp[7]));
    childItem8->setText(1, QString::number(temp[8]));
    childItem9->setText(1, QString::number(temp[9]));
    childItem10->setText(1, QString::number(temp[10]));
    childItem11->setText(1, QString::number(temp[11]));
    childItem12->setText(1, QString::number(temp[12]));
    childItem13->setText(1, QString::number(temp[13]));
    childItem14->setText(1, QString::number(temp[14]));
    childItem15->setText(1, QString::number(temp[15]));
    childItem16->setText(1, QString::number(temp[16]));
    childItem17->setText(1, QString::number(temp[17]));
    childItem18->setText(1, QString::number(temp[18]));
    childItem19->setText(1, QString::number(temp[19]));
    childItem20->setText(1, QString::number(temp[20]));
    childItem21->setText(1, QString::number(temp[21]));
    childItem22->setText(1, QString::number(temp[22]));
    childItem23->setText(1, QString::number(temp[23]));
    childItem24->setText(1, QString::number(temp[24]));
    childItem25->setText(1, QString::number(temp[25]));
    childItem26->setText(1, QString::number(temp[26]));
    childItem27->setText(1, QString::number(temp[27]));
    childItem28->setText(1, QString::number(temp[28]));
    childItem29->setText(1, QString::number(temp[29]));
    childItem30->setText(1, QString::number(temp[30]));
    childItem31->setText(1, QString::number(temp[31]));
    childItem32->setText(1, QString::number(temp[32]));
}

void LightControl::slot_setButton_clicked()
{

    unsigned int temp[33];
    temp[0] = childItem0->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR0, ADDR0, &temp[0]);
    temp[1] = childItem1->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR1, ADDR1, &temp[1]);
    temp[2] = childItem2->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR2, ADDR2, &temp[2]);
    temp[3] = childItem3->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR3, ADDR3, &temp[3]);
    temp[4] = childItem4->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR4, ADDR4, &temp[4]);
    temp[5] = childItem5->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR5, ADDR5, &temp[5]);
    temp[6] = childItem6->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR6, ADDR6, &temp[6]);
    temp[7] = childItem7->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR7, ADDR7, &temp[7]);
    temp[8] = childItem8->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR8, ADDR8, &temp[8]);
    temp[9] = childItem9->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR9, ADDR9, &temp[9]);
    temp[10] = childItem10->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR10, ADDR10, &temp[10]);
    temp[11] = childItem11->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR11, ADDR11, &temp[11]);
    temp[12] = childItem12->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR12, ADDR12, &temp[12]);
    temp[13] = childItem13->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR13, ADDR13, &temp[13]);
    temp[14] = childItem14->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR14, ADDR14, &temp[14]);
    temp[15] = childItem15->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR15, ADDR15, &temp[15]);
    temp[16] = childItem16->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR16, ADDR16, &temp[16]);
    //    temp[17] = childItem17->text(1).toInt();
    //    m_pSig_comm.SetRegs(ADDR17, ADDR17, &temp[17]);
    //    temp[18] = childItem18->text(1).toInt();
    //    m_pSig_comm.SetRegs(ADDR18, ADDR18, &temp[18]);
    temp[19] = childItem19->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR19, ADDR19, &temp[19]);
    temp[20] = childItem20->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR20, ADDR20, &temp[20]);
    temp[21] = childItem21->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR21, ADDR21, &temp[21]);
    temp[22] = childItem22->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR22, ADDR22, &temp[22]);
    temp[23] = childItem23->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR23, ADDR23, &temp[23]);
    temp[24] = childItem24->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR24, ADDR24, &temp[24]);
    temp[25] = childItem25->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR25, ADDR25, &temp[25]);
    temp[26] = childItem26->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR26, ADDR26, &temp[26]);
    temp[27] = childItem27->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR27, ADDR27, &temp[27]);
    temp[28] = childItem28->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR28, ADDR28, &temp[28]);
    temp[29] = childItem29->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR29, ADDR29, &temp[29]);
    temp[30] = childItem30->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR30, ADDR30, &temp[30]);
    //    temp[31] = childItem31->text(1).toInt();
    //    unsigned int  tt;
    //    tt = 255;
    //    m_pSig_comm.SetRegs(ADDR31, ADDR31, &tt);
    temp[32] = childItem32->text(1).toInt();
    m_pSig_comm.SetRegs(ADDR32, ADDR32, &temp[32]);

    Global::XmlParam.setParameter("EncodeScalePermm", temp[0]);
    Global::XmlParam.setParameter("EncodePulseFilter", temp[1]);
    Global::XmlParam.setParameter("Encode1EndingSign", temp[2]);
    Global::XmlParam.setParameter("Encode1Value", temp[3]);
    Global::XmlParam.setParameter("Encode2EndingSign", temp[4]);
    Global::XmlParam.setParameter("Encode2Value", temp[5]);
    Global::XmlParam.setParameter("EncodePulseCount", temp[6]);
    Global::XmlParam.setParameter("CodeChannelChoose", temp[7]);
    Global::XmlParam.setParameter("PixelAccuracy", temp[8]);
    Global::XmlParam.setParameter("EndingFeedback", temp[9]);
    Global::XmlParam.setParameter("PhotoPulseFilter", temp[10]);
    Global::XmlParam.setParameter("CamTrigPulseTime", temp[11]);
    Global::XmlParam.setParameter("PhotoToCamPos", temp[12]);
    Global::XmlParam.setParameter("CamFrameStart", temp[13]);
    Global::XmlParam.setParameter("FrameDuration", temp[14]);
    Global::XmlParam.setParameter("ModuleEnableSignal", temp[15]);
    Global::XmlParam.setParameter("LightField1DelayTime", temp[16]);
    Global::XmlParam.setParameter("LightField1GlowTime", temp[17]);
    Global::XmlParam.setParameter("LightField2DelayTime", temp[18]);
    Global::XmlParam.setParameter("LightField2GlowTime", temp[19]);
    Global::XmlParam.setParameter("LightField3DelayTime", temp[20]);
    Global::XmlParam.setParameter("LightField3GlowTime", temp[21]);
    Global::XmlParam.setParameter("LightField4DelayTime", temp[22]);
    Global::XmlParam.setParameter("LightField4GlowTime", temp[23]);
    Global::XmlParam.setParameter("LightField5DelayTime", temp[24]);
    Global::XmlParam.setParameter("LightField5GlowTime", temp[25]);
    Global::XmlParam.setParameter("LightField6DelayTime", temp[26]);
    Global::XmlParam.setParameter("LightField6GlowTime", temp[27]);
    Global::XmlParam.setParameter("CameraAndLightFieldControl", temp[28]);
    m_pSig_comm.SaveRegs();

    Global::XmlParam.SaveParasToFile();
}

void LightControl::slot_saveButton_clicked()
{

    if (m_pSig_comm.SaveRegs() <= 0)
        qDebug() << "Save all params failed!!!";
    else
        qDebug() << "Save all params success!!!";
}
