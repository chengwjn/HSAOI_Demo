#include "JsonRecipeWidget.h"
#include "Global.h"
#include "log_singleton.h"
#include "math.h"
#include "ui_JsonRecipeWidget.h"

JsonRecipeWidget::JsonRecipeWidget(QWidget* parent, JsonParse2Map* RecipeParse)
    : QWidget(parent)
    , ui(new Ui::JsonRecipeWidget)
{
    ui->setupUi(this);
    CurrentRecipe = RecipeParse;

    InitWidgetLayout();
    this->setWindowTitle(Global::CurrentRecipe);
    InitRecipesInFiles();
    InitTreeWidget();
    connect(TreeWidget, &QTreeWidget::itemDoubleClicked, this, &JsonRecipeWidget::slot_ItemDoubleClicked);
    connect(TreeWidget, &QTreeWidget::itemClicked, this, &JsonRecipeWidget::slot_ItemSelected);
}

JsonRecipeWidget::~JsonRecipeWidget()
{
    delete ui;
}

void JsonRecipeWidget::InitTreeWidget()
{
    QStringList HStrList;
    HStrList.push_back("参数");
    HStrList.push_back("数值");
    int HlableCnt = HStrList.count();

    TreeWidget->setColumnCount(HlableCnt);
    TreeWidget->setHeaderLabels(HStrList);
    TreeWidget->setColumnWidth(0, 200);
    rootItem4GlassMeasure = new QTreeWidgetItem(TreeWidget);
    rootItem4GlassMeasure->setText(0, "尺寸测量");
    rootItem4FlawDetect = new QTreeWidgetItem(TreeWidget);
    rootItem4FlawDetect->setText(0, "缺陷检测");
    rootItem2 = new QTreeWidgetItem(TreeWidget);
    rootItem2->setText(0, "None");

    //    rootItem4GlassMeasure->setFlags(rootItem4GlassMeasure->flags() & ~(Qt::ItemIsEditable));
    //    rootItem4FlawDetect->setFlags(rootItem4FlawDetect->flags() & ~(Qt::ItemIsEditable));

    TreeWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ReadValue2Tree();
    TreeWidget->expandAll();
}

void JsonRecipeWidget::InitRecipesInFiles()
{
    cbx_RecipeSelect->clear();
    QString FoldPath = "Recipes";
    QDir Folder(FoldPath);
    QStringList Filters;
    Filters << "*.json";
    Folder.setNameFilters(Filters);

    QStringList FileNames;
    foreach (QString fileName, Folder.entryList(QDir::Files)) {
        QString baseName = QFileInfo(fileName).baseName();
        FileNames.append(baseName);
    }
    foreach (QString FileName, FileNames) {
        cbx_RecipeSelect->addItem(FileName);
    }
    int SelectIndex = cbx_RecipeSelect->findText(Global::CurrentRecipe);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
}

void JsonRecipeWidget::InitWidgetLayout()
{
    cbx_RecipeSelect = new QComboBox(this);
    ui->Layout_head->setContentsMargins(10, 10, 10, 0);
    ui->Layout_head->addWidget(cbx_RecipeSelect);

    TreeWidget = new QTreeWidget(this);
    ui->Layout_table->setContentsMargins(10, 10, 10, 10);
    ui->Layout_table->addWidget(TreeWidget);

    btn_SelectRecipe = new QPushButton(this);
    btn_SelectRecipe->setText("选择");
    connect(btn_SelectRecipe, SIGNAL(clicked()), this, SLOT(SelectRecipe()));

    btn_NewRecipe = new QPushButton(this);
    btn_NewRecipe->setText("新建");
    connect(btn_NewRecipe, SIGNAL(clicked()), this, SLOT(CreateNewRecipe()));

    btn_DeleteRecipe = new QPushButton(this);
    btn_DeleteRecipe->setText("删除");
    connect(btn_DeleteRecipe, SIGNAL(clicked()), this, SLOT(DeleteRecipe()));

    btn_Read = new QPushButton(this);
    btn_Read->setText("读取");
    connect(btn_Read, SIGNAL(clicked()), this, SLOT(ReadValue2Tree()));

    btn_Save = new QPushButton(this);
    btn_Save->setText("保存");
    connect(btn_Save, SIGNAL(clicked()), this, SLOT(SaveValue2tree()));

    btn_NewParam = new QPushButton(this);
    btn_NewParam->setText("新建参数");
    connect(btn_NewParam, SIGNAL(clicked()), this, SLOT(GetNewParam()));

    btn_DeleteSingleParam = new QPushButton(this);
    btn_DeleteSingleParam->setText("删除元素");
    connect(btn_DeleteSingleParam, SIGNAL(clicked()), this, SLOT(DeleteSingleParam()));

    ui->Layout_btns->setContentsMargins(10, 10, 10, 10);
    ui->Layout_btns->addWidget(btn_SelectRecipe);
    ui->Layout_btns->addWidget(btn_NewRecipe);
    ui->Layout_btns->addWidget(btn_DeleteRecipe);
    ui->Layout_btns->addWidget(btn_Read);
    ui->Layout_btns->addWidget(btn_Save);
    ui->Layout_btns->addWidget(btn_NewParam);
    ui->Layout_btns->addWidget(btn_DeleteSingleParam);
    ui->Layout_btns->setAlignment(Qt::AlignTop);

    lbl_OperationResult = new QLabel(this);
    ui->Layout_bottom->setContentsMargins(10, 0, 10, 0);
    ui->Layout_bottom->addWidget(lbl_OperationResult);
}

void JsonRecipeWidget::ReadParamsFromRecipe()
{
    CurrentRecipe->GetValueFromRecipe("尺寸测量", Params4GlassMeasure);
    CurrentRecipe->GetValueFromRecipe("缺陷检测", Params4FlawDetect);
}

void JsonRecipeWidget::SelectRecipe()
{
    if (cbx_RecipeSelect->currentText() == Global::CurrentRecipe) {
        lbl_OperationResult->setText("无需操作");
        return;
    }
    this->setWindowTitle(cbx_RecipeSelect->currentText());
    emit sig_DeliverName(cbx_RecipeSelect->currentText());
}

void JsonRecipeWidget::CreateNewRecipe()
{
    QDialog GetRecipeNameDialog;
    QLineEdit* lineEdit = new QLineEdit(&GetRecipeNameDialog);
    QPushButton* Btn_Yes = new QPushButton("确定", &GetRecipeNameDialog);
    QString InputText = "";

    QObject::connect(Btn_Yes, &QPushButton::clicked, [&]() {
        InputText = lineEdit->text();
        QString Inputlog = "用户输入: " + InputText;
        log_singleton::Write_Log(Inputlog, Log_Level::General);
        GetRecipeNameDialog.close();
    });

    QVBoxLayout* layout = new QVBoxLayout(&GetRecipeNameDialog);
    layout->addWidget(lineEdit);
    layout->addWidget(Btn_Yes);

    // 显示对话框
    GetRecipeNameDialog.exec();

    //    qDebug() << InputText;

    if (InputText == "") {
        log_singleton::Write_Log("输入为空!", Log_Level::Error);
        return;
    }

    QString SourceFilePath = "Recipes/" + Global::CurrentRecipe + ".json";
    QString DestFilePath = "Recipes/" + InputText + ".json";

    log_singleton::Write_Log(SourceFilePath, Log_Level::General);
    if (QFile::copy(SourceFilePath, DestFilePath)) {
        log_singleton::Write_Log("文件复制成功", Log_Level::General);
        if (!QFile::exists(DestFilePath))
            log_singleton::Write_Log("文件不存在", Log_Level::Error);
    } else {
        log_singleton::Write_Log("文件复制失败", Log_Level::Error);
        return;
    }
    InitRecipesInFiles();
    int SelectIndex = cbx_RecipeSelect->findText(InputText);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
    btn_SelectRecipe->click();
}

void JsonRecipeWidget::DeleteRecipe()
{
    if (Global::CurrentRecipe != cbx_RecipeSelect->currentText()) {

        QString filePath = "Recipes/" + cbx_RecipeSelect->currentText() + ".json"; // 文件路径
        QFile file(filePath);
        if (file.remove()) {
            lbl_OperationResult->setText("文件删除成功");
            log_singleton::Write_Log("文件删除成功", Log_Level::General);
        } else {
            lbl_OperationResult->setText("文件删除失败");
            log_singleton::Write_Log("文件删除失败", Log_Level::Error);
        }
        InitRecipesInFiles();
    } else {
        lbl_OperationResult->setText("不可删除当前工单!!!");
        log_singleton::Write_Log("不可删除当前工单!!!", Log_Level::Error);
    }
}

void JsonRecipeWidget::slot_RecipeChanged(JsonParse2Map* m_RecipeChanged)
{
    CurrentRecipe = m_RecipeChanged;

    //写入参数
    ReadValue2Tree();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    QString Timelog = "当前时间: " + currentDateTimeString;
    log_singleton::Write_Log(Timelog, Log_Level::General);
    //到此为止切换配方完成
    emit sig_CameraParamsChangeRecipe();
}

void JsonRecipeWidget::ReadValue2Tree()
{
    //读取参数
    ReadParamsFromRecipe();
    //刷新前先清空
    while (rootItem4GlassMeasure->childCount() > 0) {
        QTreeWidgetItem* child = rootItem4GlassMeasure->takeChild(0);
        delete child;
    }
    while (rootItem4FlawDetect->childCount() > 0) {
        QTreeWidgetItem* child = rootItem4FlawDetect->takeChild(0);
        delete child;
    }

    for (int i = 0; i < Params4GlassMeasure.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem4GlassMeasure);
        child->setText(0, Params4GlassMeasure[i].Name);
        child->setText(1, QString::number(Params4GlassMeasure[i].Value));
        rootItem4GlassMeasure->addChild(child);
    }

    for (int i = 0; i < Params4FlawDetect.count(); i++) {
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem4FlawDetect);
        child->setText(0, Params4FlawDetect[i].Name);
        child->setText(1, QString::number(Params4FlawDetect[i].Value));
        rootItem4FlawDetect->addChild(child);
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 工单: " + cbx_RecipeSelect->currentText() + " 参数已读取";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::SaveValue2tree()
{
    for (int i = 0; i < Params4GlassMeasure.size(); ++i) {
        Key2Value& item1 = Params4GlassMeasure[i];
        // 遍历第二个表，查找相同 Name 的元素
        for (int j = 0; j < rootItem4GlassMeasure->childCount(); ++j) {
            QString Name = rootItem4GlassMeasure->child(j)->text(0);
            QString Value = rootItem4GlassMeasure->child(j)->text(1);
            if (item1.Name == Name) {
                // 如果找到相同的 Name，用第二个表的 Value 替换第一个表中的 Value
                item1.Value = Value.toDouble();
                break;
            }
        }
    }
    for (int i = 0; i < Params4FlawDetect.size(); ++i) {
        Key2Value& item1 = Params4FlawDetect[i];
        for (int j = 0; j < rootItem4FlawDetect->childCount(); ++j) {
            QString Name = rootItem4FlawDetect->child(j)->text(0);
            QString Value = rootItem4FlawDetect->child(j)->text(1);
            if (item1.Name == Name) {
                item1.Value = Value.toDouble();
                break;
            }
        }
    }

    CurrentRecipe->SetValue2Recipe("尺寸测量", Params4GlassMeasure);
    CurrentRecipe->SetValue2Recipe("缺陷检测", Params4FlawDetect);
    CurrentRecipe->SaveParamsToFile();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 工单参数已保存";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::GetNewParam()
{
    QDialog GetNewParamDialog;
    QComboBox* SelectParent = new QComboBox(&GetNewParamDialog);
    SelectParent->addItem("尺寸测量");
    SelectParent->addItem("缺陷检测");
    QLineEdit* InputName_edit = new QLineEdit(&GetNewParamDialog);
    QLineEdit* InputValue_edit = new QLineEdit(&GetNewParamDialog);
    QPushButton* btn_yes = new QPushButton("确定", &GetNewParamDialog);
    QString InputName = "";
    QString InputValue = "";
    int SelectIndex;

    QObject::connect(btn_yes, &QPushButton::clicked, [&]() {
        SelectIndex = SelectParent->currentIndex();
        InputName = InputName_edit->text();
        InputValue = InputValue_edit->text();
        GetNewParamDialog.close();
    });
    QVBoxLayout* layout = new QVBoxLayout(&GetNewParamDialog);
    layout->addWidget(SelectParent);
    layout->addWidget(InputName_edit);
    layout->addWidget(InputValue_edit);
    layout->addWidget(btn_yes);

    GetNewParamDialog.exec();

    Key2Value Newer;
    Newer.Name = InputName;
    Newer.Value = InputValue.toDouble();
    if (SelectIndex == 0) {
        Params4GlassMeasure.append(Newer);
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem4GlassMeasure);
        child->setText(0, InputName);
        child->setText(1, InputValue);
        rootItem4GlassMeasure->addChild(child);
    } else {
        Params4FlawDetect.append(Newer);
        QTreeWidgetItem* child = new QTreeWidgetItem(rootItem4FlawDetect);
        child->setText(0, InputName);
        child->setText(1, InputValue);
        rootItem4FlawDetect->addChild(child);
    }
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 已新建参数，需要点击保存按钮后存入文件";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::DeleteSingleParam()
{
    if (SelectedisRootItem) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 无效操作";
        log_singleton::Write_Log(currentDateTimeString, Log_Level::General);
        lbl_OperationResult->setText(currentDateTimeString);
        lbl_OperationResult->adjustSize();
        return;
    }

    QString ElementDelete = SelectedParent + "." + SelectedName;
    CurrentRecipe->DeleteParameter(ElementDelete);
    CurrentRecipe->SaveParamsToFile();
    ReadValue2Tree();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 已删除元素";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::slot_ItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (column == 1) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
}

void JsonRecipeWidget::slot_ItemSelected(QTreeWidgetItem* item, int column)
{
    SelectedName = item->text(0);
    SelectedValue = item->text(1);
    if (item->parent() != nullptr) {
        SelectedParent = item->parent()->text(0);
        SelectedisRootItem = false;
    } else {
        SelectedParent = "";
        SelectedisRootItem = true;
    }
    qDebug() << SelectedParent << "." << SelectedName << ". " << SelectedValue;
}
