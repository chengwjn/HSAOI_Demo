#include "SystemSettingForm.h"
#include "NavigationBar/CNavDelegate.h"
#include "NavigationBar/CNavModel.h"
#include "ui_SystemSettingForm.h"

SystemSettingForm::SystemSettingForm(RegParasComm& sig_comm, JsonParse2Map& JsonRecipe, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SystemSettingForm)
    , m_pSig_comm(sig_comm)
    , JSONRECIPE(JsonRecipe)
{
    ui->setupUi(this);

    stack_widget = new QStackedWidget(this);
    List_View = new QListView(this);

    InitForm();

    QHBoxLayout* hbox = new QHBoxLayout();
    setLayout(hbox);
    hbox->addWidget(List_View);
    hbox->addWidget(stack_widget);

    SetNavigationBar();
}

SystemSettingForm::~SystemSettingForm()
{
    delete ui;
}

void SystemSettingForm::SetNavigationBar()
{
    CNavModel* pNavModel = new CNavModel(this);
    CNavDelegate* pDelegate = new CNavDelegate(this);
    pNavModel->ReadConfig("SystemParam/navigation.xml");
    pNavModel->ExpandAllNodes();

    List_View->setModel(pNavModel);
    List_View->setItemDelegate(pDelegate);

    connect(List_View, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_ListView_Pressed()));
}

void SystemSettingForm::InitForm()
{
    List_View->setFixedWidth(180);
    this_JsonRecipeWidget = new JsonRecipeWidget(this, &JSONRECIPE);
    stack_widget->addWidget(this_JsonRecipeWidget);

    this_CameraParamsWidget = new CameraParamsWidget(this, &JSONRECIPE);
    stack_widget->addWidget(this_CameraParamsWidget);

    LightControlWidget = new LightControl(m_pSig_comm, this);
    stack_widget->addWidget(LightControlWidget);

    connect(this_JsonRecipeWidget, SIGNAL(sig_DeliverName(QString)), this, SLOT(slot_JsonRecipeName_Changed(QString)));
    connect(this, SIGNAL(sig_Deliver_NewRecipe(JsonParse2Map*)), this_JsonRecipeWidget, SLOT(slot_RecipeChanged(JsonParse2Map*)));
    connect(this_JsonRecipeWidget, SIGNAL(sig_CameraParamsChangeRecipe()), this_CameraParamsWidget, SLOT(slot_ChangeRecipe()));
}

void SystemSettingForm::slot_ListView_Pressed()
{
    QModelIndex index = List_View->currentIndex();
    int num = index.row();
    QString text = index.data().toString();

    if (num == 3) {
        stack_widget->setCurrentIndex(2);
    } else if (num == 1) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 2) {
        stack_widget->setCurrentIndex(1);
    } else if (num == 5) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 6) {
        stack_widget->setCurrentIndex(0);
    } else if (num == 4) {
        stack_widget->setCurrentIndex(0);
    } else {
        //stacked_widget->setCurrentIndex(0);
    }
}

void SystemSettingForm::slot_JsonRecipe_Changed(JsonParse2Map* NewRecipe)
{
    emit sig_Deliver_NewRecipe(NewRecipe);
}

void SystemSettingForm::slot_JsonRecipeName_Changed(QString NewRecipeName)
{
    emit sig_Deliver_NewRecipeName2mainWindow(NewRecipeName);
}
