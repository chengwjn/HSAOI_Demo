/*******************************************
    @ClassName   : SystemSettingForm
    @Description : 设置界面表格
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-08-04
********************************************/
#ifndef SYSTEMSETTINGFORM_H
#define SYSTEMSETTINGFORM_H

#include "Camera/Dushen/DushenCameraWidget.h"
#include "Global.h"
#include "LightControl/LightControl.h"
#include "Parameter/CameraParamsWidget.h"
#include "Parameter/RecipeWidget.h"
#include <Parameter/JsonRecipeParse.h>
#include <Parameter/JsonRecipeWidget.h>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QWidget>

namespace Ui {
class SystemSettingForm;
}

class SystemSettingForm : public QWidget {
    Q_OBJECT

public:
    explicit SystemSettingForm(RegParasComm& sig_comm, JsonRecipeParse& JsonRecipe, QWidget* parent = nullptr);
    ~SystemSettingForm();

private:
    Ui::SystemSettingForm* ui;
    QStackedWidget* stack_widget;
    QListView* List_View;

    JsonRecipeWidget* this_JsonRecipeWidget;
    LightControl* LightControlWidget;
    RegParasComm& m_pSig_comm;
    JsonRecipeParse& m_JsonRecipe;
    CameraParamsWidget* this_CameraParamsWidget;

    void SetNavigationBar();
signals:
    void sig_Deliver_NewRecipe(JsonRecipeParse* m_NewRecipe);
    void sig_Deliver_NewRecipeName2mainWindow(QString m_NewRecipeName);
    void sig_Deliver_FromJsonRecipe_FlawWidgetNeedReplot();
private slots:
    void InitForm();

    void slot_ListView_Pressed();
    void slot_JsonRecipe_Changed(JsonRecipeParse* NewRecipe);
    void slot_JsonRecipeName_Changed(QString NewRecipeName);
    void slot_Deliver_FromJsonRecipe_FlawWidgetNeedReplot();
};

#endif // SYSTEMSETTINGFORM_H
