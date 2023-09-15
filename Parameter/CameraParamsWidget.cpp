#include "CameraParamsWidget.h"
#include <QWidget>

CameraParamsWidget::CameraParamsWidget(QWidget* parent)
    : QWidget(parent)
{
//    CurrentRecipe = RecipeParse;
    InitWidgetLayout();
    InitTreeWidget();
    connect(TreeWidget, &QTreeWidget::itemDoubleClicked, this, &CameraParamsWidget::slot_ItemDoubleClicked);
}

void CameraParamsWidget::InitWidgetLayout()
{
    QHBoxLayout* layout0 = new QHBoxLayout(this);
    layout0->setContentsMargins(10, 10, 10, 10);

    TreeWidget = new QTreeWidget(this);

    QVBoxLayout* layout1 = new QVBoxLayout(this);
    layout1->setContentsMargins(10, 10, 10, 10);

    this->setLayout(layout0);
    layout0->addWidget(TreeWidget);
    layout0->addLayout(layout1);

    btn_Read = new QPushButton(this);
    btn_Read->setText("读取");
    connect(btn_Read, SIGNAL(clicked()), this, SLOT(ReadValue2Tree()));

    btn_Save = new QPushButton(this);
    btn_Save->setText("保存");
    connect(btn_Save, SIGNAL(clicked()), this, SLOT(slot_SaveValue2Recipe()));

    layout1->addWidget(btn_Read);
    layout1->addWidget(btn_Save);
    layout1->setAlignment(Qt::AlignTop);
}

void CameraParamsWidget::InitTreeWidget()
{
    QStringList HStrList;
    HStrList.push_back("参数");
    HStrList.push_back("数值");
    int HlableCnt = HStrList.count();

    TreeWidget->setColumnCount(HlableCnt);
    TreeWidget->setHeaderLabels(HStrList);
    TreeWidget->setColumnWidth(0, 200);
    rootItem0 = new QTreeWidgetItem(TreeWidget);
    rootItem0->setText(0, "相机0");
    rootItem1 = new QTreeWidgetItem(TreeWidget);
    rootItem1->setText(0, "相机1");
    rootItem2 = new QTreeWidgetItem(TreeWidget);
    rootItem2->setText(0, "相机2");
    rootItem3 = new QTreeWidgetItem(TreeWidget);
    rootItem3->setText(0, "相机3");

    TreeWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ReadValue2Tree();
    TreeWidget->expandAll();
}

void CameraParamsWidget::ReadValue2Tree()
{
    //刷新前先清空
    while (rootItem0->childCount() > 0) {
        QTreeWidgetItem* child = rootItem0->takeChild(0);
        delete child;
    }
    while (rootItem1->childCount() > 0) {
        QTreeWidgetItem* child = rootItem1->takeChild(0);
        delete child;
    }
    while (rootItem2->childCount() > 0) {
        QTreeWidgetItem* child = rootItem2->takeChild(0);
        delete child;
    }
    while (rootItem3->childCount() > 0) {
        QTreeWidgetItem* child = rootItem3->takeChild(0);
        delete child;
    }
//    SetValue2Tree(QString::fromLocal8Bit("拍照行数"), QString::number(CurrentRecipe->Camera_LineNum[0]), rootItem0);
//    SetValue2Tree(QString::fromLocal8Bit("相机增益"), QString::number(CurrentRecipe->Camera_Gain[0]), rootItem0);
//    SetValue2Tree(QString::fromLocal8Bit("帧次"), QString::number(CurrentRecipe->Camera_FrameCount[0]), rootItem0);
//    SetValue2Tree(QString::fromLocal8Bit("曝光时间"), QString::number(CurrentRecipe->Camera_ExposureTime[0]), rootItem0);

//    SetValue2Tree(QString::fromLocal8Bit("拍照行数"), QString::number(CurrentRecipe->Camera_LineNum[1]), rootItem1);
//    SetValue2Tree(QString::fromLocal8Bit("相机增益"), QString::number(CurrentRecipe->Camera_Gain[1]), rootItem1);
//    SetValue2Tree(QString::fromLocal8Bit("帧次"), QString::number(CurrentRecipe->Camera_FrameCount[1]), rootItem1);
//    SetValue2Tree(QString::fromLocal8Bit("曝光时间"), QString::number(CurrentRecipe->Camera_ExposureTime[1]), rootItem1);

//    SetValue2Tree(QString::fromLocal8Bit("拍照行数"), QString::number(CurrentRecipe->Camera_LineNum[2]), rootItem2);
//    SetValue2Tree(QString::fromLocal8Bit("相机增益"), QString::number(CurrentRecipe->Camera_Gain[2]), rootItem2);
//    SetValue2Tree(QString::fromLocal8Bit("帧次"), QString::number(CurrentRecipe->Camera_FrameCount[2]), rootItem2);
//    SetValue2Tree(QString::fromLocal8Bit("曝光时间"), QString::number(CurrentRecipe->Camera_ExposureTime[2]), rootItem2);

//    SetValue2Tree(QString::fromLocal8Bit("拍照行数"), QString::number(CurrentRecipe->Camera_LineNum[3]), rootItem3);
//    SetValue2Tree(QString::fromLocal8Bit("相机增益"), QString::number(CurrentRecipe->Camera_Gain[3]), rootItem3);
//    SetValue2Tree(QString::fromLocal8Bit("帧次"), QString::number(CurrentRecipe->Camera_FrameCount[3]), rootItem3);
//    SetValue2Tree(QString::fromLocal8Bit("曝光时间"), QString::number(CurrentRecipe->Camera_ExposureTime[3]), rootItem3);
}

void CameraParamsWidget::SetValue2Tree(QString paramName, QString Value, QTreeWidgetItem* ParentItem)
{
    QTreeWidgetItem* child = new QTreeWidgetItem(ParentItem);
    child->setText(0, paramName);
    child->setText(1, Value);
    ParentItem->addChild(child);
}

void CameraParamsWidget::slot_SaveValue2Recipe()
{
//    CurrentRecipe->Camera_LineNum[0] = rootItem0->child(0)->text(1).toInt();
//    CurrentRecipe->Camera_Gain[0] = rootItem0->child(1)->text(1).toDouble();
//    CurrentRecipe->Camera_FrameCount[0] = rootItem0->child(2)->text(1).toInt();
//    CurrentRecipe->Camera_ExposureTime[0] = rootItem0->child(3)->text(1).toDouble();

//    CurrentRecipe->Camera_LineNum[1] = rootItem1->child(0)->text(1).toInt();
//    CurrentRecipe->Camera_Gain[1] = rootItem1->child(1)->text(1).toDouble();
//    CurrentRecipe->Camera_FrameCount[1] = rootItem1->child(2)->text(1).toInt();
//    CurrentRecipe->Camera_ExposureTime[1] = rootItem1->child(3)->text(1).toDouble();

//    CurrentRecipe->Camera_LineNum[2] = rootItem2->child(0)->text(1).toInt();
//    CurrentRecipe->Camera_Gain[2] = rootItem2->child(1)->text(1).toDouble();
//    CurrentRecipe->Camera_FrameCount[2] = rootItem2->child(2)->text(1).toInt();
//    CurrentRecipe->Camera_ExposureTime[2] = rootItem2->child(3)->text(1).toDouble();

//    CurrentRecipe->Camera_LineNum[3] = rootItem3->child(0)->text(1).toInt();
//    CurrentRecipe->Camera_Gain[3] = rootItem3->child(1)->text(1).toDouble();
//    CurrentRecipe->Camera_FrameCount[3] = rootItem3->child(2)->text(1).toInt();
//    CurrentRecipe->Camera_ExposureTime[3] = rootItem3->child(3)->text(1).toDouble();

//    CurrentRecipe->WriteCamerasParam();
    //数值只有在重新打开相机后生效
}

void CameraParamsWidget::slot_ChangeRecipe()
{
    TreeWidget->clear();
//    CurrentRecipe->ReadCamerasParam();

    InitTreeWidget();
}

void CameraParamsWidget::slot_ItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (column == 1) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
}
