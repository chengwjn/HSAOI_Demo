/*******************************************
    @ClassName   : RecipeWidget
    @Description : 配方参数管理界面类
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-07-10
********************************************/
#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "Parameter/JsonRecipeParse.h"
#include "Parameter/RecipeParse.h"
#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

enum ParamType {
    LENGTH = 0,
    LENGTH_ERROR = 1,
    WIDTH = 2,
    WIDTH_ERROR = 3,
    DIAGONAL1 = 4,
    DIAGONAL1_ERROR = 5,
    DIAGONAL2 = 6,
    DIAGONAL2_ERROR = 7,

    LENGTH_2 = 8,
    LENGTH_ERROR_2 = 9,
    WIDTH_2 = 10,
    WIDTH_ERROR_2 = 11,
    DIAGONAL1_2 = 12,
    DIAGONAL1_ERROR_2 = 13,
    DIAGONAL2_2 = 14,
    DIAGONAL2_ERROR_2 = 15
};

namespace Ui {
class RecipeWidget;
}

class RecipeWidget : public QWidget {
    Q_OBJECT

public:
    explicit RecipeWidget(QWidget* parent = nullptr, RecipeParse* RecipeParse = nullptr);
    ~RecipeWidget();

    RecipeParse* CurrentRecipe;

private:
    Ui::RecipeWidget* ui;
    void InitTableWidget();
    void InitRecipesInFiles();
    QString SetItemName(int ParamName);

    //窗口控件
    QTableWidget* TableWidget;
    QPushButton* btn_Save;
    QPushButton* btn_Read;
    QLabel* lbl_OperationResult;
    QComboBox* cbx_RecipeSelect;
    QPushButton* btn_SelectRecipe;
    QPushButton* btn_NewRecipe;
    QPushButton* btn_DeleteRecipe;

    void InitWidgetLayout();

public slots:
    void SaveTable2Value();
    void ReadValue2Table();
    void SetValue2Table(int ParamName, QString Value);
    void SelectRecipe();
    void CreateNewRecipe();
    void DeleteRecipe();

    void slot_RecipeChanged(RecipeParse* m_RecpipeChanged);
signals:
    void sig_DeliverName(QString RecipeChanged);
};

#endif // RECIPEWIDGET_H
