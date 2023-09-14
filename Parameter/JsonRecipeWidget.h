/*******************************************
    @ClassName   : JsonRecipeWidget
    @Description : Json配方参数管理界面类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-25
********************************************/
#ifndef JSONRECIPEWIDGET_H
#define JSONRECIPEWIDGET_H

#include "Parameter/JsonParse.h"
#include "Parameter/JsonRecipeParse.h"
#include "Parameter/RecipeWidget.h"
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class JsonRecipeWidget;
}

class JsonRecipeWidget : public QWidget {
    Q_OBJECT

public:
    explicit JsonRecipeWidget(QWidget* parent = nullptr, JsonRecipeParse* RecipeParse = nullptr);
    ~JsonRecipeWidget();

    JsonRecipeParse* CurrentRecipe;

private:
    Ui::JsonRecipeWidget* ui;

    void InitTreeWidget();
    void InitRecipesInFiles();
    QString SetItemName(int ParamName);
    void InitWidgetLayout();

    //窗口控件
    QPushButton* btn_Save;
    QPushButton* btn_Read;
    QPushButton* btn_SelectRecipe;
    QPushButton* btn_NewRecipe;
    QPushButton* btn_DeleteRecipe;

    QComboBox* cbx_RecipeSelect;
    QLabel* lbl_OperationResult;
    QTreeWidget* TreeWidget;

    QTreeWidgetItem* rootItem;
    QTreeWidgetItem* rootItem1;
    QTreeWidgetItem* rootItem2;

    bool isNeedReplot = false;

public slots:
    void SelectRecipe();
    void CreateNewRecipe();
    void DeleteRecipe();
    void slot_RecipeChanged(JsonRecipeParse* m_RecipeChanged);

    void ReadValue2Tree();
    void SaveValue2tree();
    void SetValue2Tree(int paramName, QString Value, QTreeWidgetItem* ParentItem);
signals:
    void sig_DeliverName(QString RecipeChanged);
    void sig_CameraParamsChangeRecipe();
    void sig_FlawWidgetShouldReplot();
private slots:
    void slot_ItemDoubleClicked(QTreeWidgetItem* item, int column);
};

#endif // JSONRECIPEWIDGET_H
