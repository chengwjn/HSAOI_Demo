#include "CameraParamsWidget.h"
#include <QWidget>

CameraParamsWidget::CameraParamsWidget(QWidget* parent, JsonParse2Map* RecipeParse)
    : QWidget(parent)
{
    //    CurrentRecipe = RecipeParse;
    Recipe = RecipeParse;
    InitWidgetLayout();
    InitTreeWidget();
    connect(TreeWidget, &QTreeWidget::itemDoubleClicked, this, &CameraParamsWidget::slot_ItemDoubleClicked);
}

void CameraParamsWidget::ReadParamsFromRecipe()
{
    Recipe->GetValueFromRecipe("相机0", Params4Camera0);
    Recipe->GetValueFromRecipe("相机1", Params4Camera1);
    Recipe->GetValueFromRecipe("相机2", Params4Camera2);
    Recipe->GetValueFromRecipe("相机3", Params4Camera3);
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
    //读取参数
    ReadParamsFromRecipe();
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

    for (int i = 0; i < Params4Camera0.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem0);
        child->setText(0, Params4Camera0[i].Name);
        child->setText(1, QString::number(Params4Camera0[i].Value));
        rootItem0->addChild(child);
    }
    for (int i = 0; i < Params4Camera1.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem1);
        child->setText(0, Params4Camera1[i].Name);
        child->setText(1, QString::number(Params4Camera1[i].Value));
        rootItem1->addChild(child);
    }
    for (int i = 0; i < Params4Camera2.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem2);
        child->setText(0, Params4Camera2[i].Name);
        child->setText(1, QString::number(Params4Camera2[i].Value));
        rootItem2->addChild(child);
    }
    for (int i = 0; i < Params4Camera3.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem3);
        child->setText(0, Params4Camera3[i].Name);
        child->setText(1, QString::number(Params4Camera3[i].Value));
        rootItem3->addChild(child);
    }
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
    for (int i = 0; i < Params4Camera0.size(); ++i) {
        Key2Value& item1 = Params4Camera0[i];
        for (int j = 0; j < rootItem0->childCount(); ++j) {
            QString Name = rootItem0->child(j)->text(0);
            QString Value = rootItem0->child(j)->text(1);
            if (item1.Name == Name) {
                item1.Value = Value.toDouble();
                break;
            }
        }
    }
    for (int i = 0; i < Params4Camera1.size(); ++i) {
        Key2Value& item1 = Params4Camera1[i];
        for (int j = 0; j < rootItem1->childCount(); ++j) {
            QString Name = rootItem1->child(j)->text(0);
            QString Value = rootItem1->child(j)->text(1);
            if (item1.Name == Name) {
                item1.Value = Value.toDouble();
                break;
            }
        }
    }
    for (int i = 0; i < Params4Camera2.size(); ++i) {
        Key2Value& item1 = Params4Camera2[i];
        for (int j = 0; j < rootItem2->childCount(); ++j) {
            QString Name = rootItem2->child(j)->text(0);
            QString Value = rootItem2->child(j)->text(1);
            if (item1.Name == Name) {
                item1.Value = Value.toDouble();
                break;
            }
        }
    }
    for (int i = 0; i < Params4Camera3.size(); ++i) {
        Key2Value& item1 = Params4Camera3[i];
        for (int j = 0; j < rootItem3->childCount(); ++j) {
            QString Name = rootItem3->child(j)->text(0);
            QString Value = rootItem3->child(j)->text(1);
            if (item1.Name == Name) {
                item1.Value = Value.toDouble();
                break;
            }
        }
    }
    Recipe->SetValue2Recipe("相机0", Params4Camera0);
    Recipe->SetValue2Recipe("相机1", Params4Camera1);
    Recipe->SetValue2Recipe("相机2", Params4Camera2);
    Recipe->SetValue2Recipe("相机3", Params4Camera3);
    Recipe->SaveParamsToFile();
    //数值只有在重新打开相机后生效
}

void CameraParamsWidget::slot_ChangeRecipe()
{
    ReadValue2Tree();
}

void CameraParamsWidget::slot_ItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (column == 1) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
}
