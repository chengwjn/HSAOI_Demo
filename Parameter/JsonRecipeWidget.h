/*******************************************
    @ClassName   : JsonRecipeWidget
    @Description : Json工单参数管理界面类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-25
********************************************/
#ifndef JSONRECIPEWIDGET_H
#define JSONRECIPEWIDGET_H

//#include "Parameter/JsonParse.h"
#include "Parameter/JsonParse2Map.h"
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
    explicit JsonRecipeWidget(QWidget* parent = nullptr, JsonParse2Map* Recipe = nullptr);
    ~JsonRecipeWidget();

    //    JsonParse* CurrentRecipe;
    JsonParse2Map* CurrentRecipe;

private:
    Ui::JsonRecipeWidget* ui;

    void InitTreeWidget();
    void InitRecipesInFiles();
    void InitWidgetLayout();

    //窗口控件
    QPushButton* btn_Save;
    QPushButton* btn_Read;
    QPushButton* btn_SelectRecipe;
    QPushButton* btn_NewRecipe;
    QPushButton* btn_DeleteRecipe;
    QPushButton* btn_NewParam;
    QPushButton* btn_DeleteSingleParam;

    QComboBox* cbx_RecipeSelect;
    QLabel* lbl_OperationResult;
    QTreeWidget* TreeWidget;

    QTreeWidgetItem* rootItem4GlassMeasure;
    QTreeWidgetItem* rootItem4FlawDetect;
    QTreeWidgetItem* rootItem2;

    QList<Key2Value> Params4GlassMeasure;
    QList<Key2Value> Params4FlawDetect;

    void ReadParamsFromRecipe();

    QString SelectedName;
    QString SelectedValue;
    QString SelectedParent;
    bool SelectedisRootItem = false;
public slots:
    void SelectRecipe();
    void CreateNewRecipe();
    void DeleteRecipe();
    void slot_RecipeChanged(JsonParse2Map* m_RecipeChanged);

    void ReadValue2Tree();
    void SaveValue2tree();
    void GetNewParam();
    void DeleteSingleParam();
signals:
    void sig_DeliverName(QString RecipeChanged);
    void sig_CameraParamsChangeRecipe();
private slots:
    void slot_ItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slot_ItemSelected(QTreeWidgetItem* item, int column);
};

#endif // JSONRECIPEWIDGET_H
