/*******************************************
    @ClassName   : CameraParamsWidget
    @Description : 相机操作界面
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-09-14
********************************************/
#ifndef CAMERAPARAMSWIDGET_H
#define CAMERAPARAMSWIDGET_H

//#include "Parameter/JsonRecipeParse.h"
#include "Parameter/JsonParse2Map.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

class CameraParamsWidget : public QWidget {
    Q_OBJECT
public:
    //    explicit CameraParamsWidget(QWidget* parent = nullptr, JsonRecipeParse* RecipeParse = nullptr);
    explicit CameraParamsWidget(QWidget* parent = nullptr, JsonParse2Map* RecipeParse = nullptr);
    //    JsonRecipeParse* CurrentRecipe;

private:
    JsonParse2Map* Recipe;

    QPushButton* btn_Save;
    QPushButton* btn_Read;

    QTreeWidget* TreeWidget;

    QTreeWidgetItem* rootItem0;
    QTreeWidgetItem* rootItem1;
    QTreeWidgetItem* rootItem2;
    QTreeWidgetItem* rootItem3;

    QList<Key2Value> Params4Camera0;
    QList<Key2Value> Params4Camera1;
    QList<Key2Value> Params4Camera2;
    QList<Key2Value> Params4Camera3;

    void ReadParamsFromRecipe();

    void InitWidgetLayout();
    void InitTreeWidget();

    void SetValue2Tree(QString paramName, QString Value, QTreeWidgetItem* ParentItem);
signals:
public slots:
    void slot_SaveValue2Recipe();
    //    void slot_ReadValue2Recipe();
    void ReadValue2Tree();
    void slot_ChangeRecipe();
private slots:
    void slot_ItemDoubleClicked(QTreeWidgetItem* item, int column);
};

#endif // CAMERAPARAMSWIDGET_H
