#include "JsonRecipeWidget.h"
#include "log_singleton.h"
#include "math.h"
#include "ui_JsonRecipeWidget.h"

JsonRecipeWidget::JsonRecipeWidget(QWidget* parent, JsonRecipeParse* RecipeParse)
    : QWidget(parent)
    , ui(new Ui::JsonRecipeWidget)
{
    ui->setupUi(this);
    CurrentRecipe = RecipeParse;

    InitWidgetLayout();
    this->setWindowTitle(CurrentRecipe->m_RecipeName);
    InitRecipesInFiles();
    InitTreeWidget();
    connect(TreeWidget, &QTreeWidget::itemDoubleClicked, this, &JsonRecipeWidget::slot_ItemDoubleClicked);
}

JsonRecipeWidget::~JsonRecipeWidget()
{
    delete ui;
}

void JsonRecipeWidget::InitTreeWidget()
{
    QStringList HStrList;
    HStrList.push_back(QString::fromLocal8Bit("参数"));
    HStrList.push_back(QString::fromLocal8Bit("数值"));
    int HlableCnt = HStrList.count();

    TreeWidget->setColumnCount(HlableCnt);
    TreeWidget->setHeaderLabels(HStrList);
    TreeWidget->setColumnWidth(0, 200);
    rootItem = new QTreeWidgetItem(TreeWidget);
    rootItem->setText(0, QString::fromLocal8Bit("尺寸测量"));
    rootItem1 = new QTreeWidgetItem(TreeWidget);
    rootItem1->setText(0, QString::fromLocal8Bit("缺陷检测"));
    rootItem2 = new QTreeWidgetItem(TreeWidget);
    rootItem2->setText(0, "None");

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
    int SelectIndex = cbx_RecipeSelect->findText(CurrentRecipe->m_RecipeName);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
}

QString JsonRecipeWidget::SetItemName(int ParamName)
{
    switch (ParamName) {
    case 0:
        return QString::fromLocal8Bit("长度(mm)");
        break;
    case 1:
        return QString::fromLocal8Bit("长度_误差(mm)");
        break;
    case 2:
        return QString::fromLocal8Bit("宽度(mm)");
        break;
    case 3:
        return QString::fromLocal8Bit("宽度_误差(mm)");
        break;
    case 4:
        return QString::fromLocal8Bit("对角线1(mm)");
        break;
    case 5:
        return QString::fromLocal8Bit("对角线1_误差(mm)");
        break;
    case 6:
        return QString::fromLocal8Bit("对角线2(mm)");
        break;
    case 7:
        return QString::fromLocal8Bit("对角线2_误差(mm)");
        break;
    case 8:
        return "Length";
        break;
    case 9:
        return "LengthError";
        break;
    case 10:
        return "Width";
        break;
    case 11:
        return "WidthError";
        break;
    case 12:
        return "Diagonal1";
        break;
    case 13:
        return "Diagonal1Error";
        break;
    case 14:
        return "Diagonal2";
        break;
    case 15:
        return "Diagonal2Error";
        break;
    }
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
    btn_SelectRecipe->setText(QString::fromLocal8Bit("选择"));
    connect(btn_SelectRecipe, SIGNAL(clicked()), this, SLOT(SelectRecipe()));

    btn_NewRecipe = new QPushButton(this);
    btn_NewRecipe->setText(QString::fromLocal8Bit("新建"));
    connect(btn_NewRecipe, SIGNAL(clicked()), this, SLOT(CreateNewRecipe()));

    btn_DeleteRecipe = new QPushButton(this);
    btn_DeleteRecipe->setText(QString::fromLocal8Bit("删除"));
    connect(btn_DeleteRecipe, SIGNAL(clicked()), this, SLOT(DeleteRecipe()));

    btn_Read = new QPushButton(this);
    btn_Read->setText(QString::fromLocal8Bit("读取"));
    connect(btn_Read, SIGNAL(clicked()), this, SLOT(ReadValue2Tree()));

    btn_Save = new QPushButton(this);
    btn_Save->setText(QString::fromLocal8Bit("保存"));
    connect(btn_Save, SIGNAL(clicked()), this, SLOT(SaveValue2tree()));

    ui->Layout_btns->setContentsMargins(10, 10, 10, 10);
    ui->Layout_btns->addWidget(btn_SelectRecipe);
    ui->Layout_btns->addWidget(btn_NewRecipe);
    ui->Layout_btns->addWidget(btn_DeleteRecipe);
    ui->Layout_btns->addWidget(btn_Read);
    ui->Layout_btns->addWidget(btn_Save);
    ui->Layout_btns->setAlignment(Qt::AlignTop);

    lbl_OperationResult = new QLabel(this);
    ui->Layout_bottom->setContentsMargins(10, 0, 10, 0);
    ui->Layout_bottom->addWidget(lbl_OperationResult);
}

void JsonRecipeWidget::SelectRecipe()
{
    if (cbx_RecipeSelect->currentText() == CurrentRecipe->m_RecipeName) {
        lbl_OperationResult->setText(QString::fromLocal8Bit("无需操作"));
        return;
    }
    this->setWindowTitle(cbx_RecipeSelect->currentText());
    emit sig_DeliverName(cbx_RecipeSelect->currentText());
}

void JsonRecipeWidget::CreateNewRecipe()
{
    QDialog GetRecipeNameDialog;
    QLineEdit* lineEdit = new QLineEdit(&GetRecipeNameDialog);
    QPushButton* Btn_Yes = new QPushButton(QString::fromLocal8Bit("确定"), &GetRecipeNameDialog);
    QString InputText = "";

    QObject::connect(Btn_Yes, &QPushButton::clicked, [&]() {
        InputText = lineEdit->text();
        QString Inputlog = QString::fromLocal8Bit("用户输入: ") + InputText;
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
        log_singleton::Write_Log(QString::fromLocal8Bit("输入为空!"), Log_Level::Error);
        return;
    }

    QString SourceFilePath = "Recipes/" + CurrentRecipe->m_RecipeName + ".json";
    QString DestFilePath = "Recipes/" + InputText + ".json";

    log_singleton::Write_Log(SourceFilePath, Log_Level::General);
    //    qDebug() << SourceFilePath;
    //    qDebug() << DestFilePath;
    if (QFile::copy(SourceFilePath, DestFilePath)) {
        log_singleton::Write_Log(QString::fromLocal8Bit("文件复制成功"), Log_Level::General);
        if (!QFile::exists(DestFilePath))
            log_singleton::Write_Log(QString::fromLocal8Bit("文件不存在"), Log_Level::Error);
    } else {
        log_singleton::Write_Log(QString::fromLocal8Bit("文件复制失败"), Log_Level::Error);
        return;
    }
    InitRecipesInFiles();
    int SelectIndex = cbx_RecipeSelect->findText(InputText);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
    btn_SelectRecipe->click();
}

void JsonRecipeWidget::DeleteRecipe()
{
    if (CurrentRecipe->m_RecipeName != cbx_RecipeSelect->currentText()) {

        QString filePath = "Recipes/" + cbx_RecipeSelect->currentText() + ".json"; // 文件路径
        QFile file(filePath);
        if (file.remove()) {
            lbl_OperationResult->setText(QString::fromLocal8Bit("文件删除成功"));
            log_singleton::Write_Log(QString::fromLocal8Bit("文件删除成功"), Log_Level::General);
        } else {
            lbl_OperationResult->setText(QString::fromLocal8Bit("文件删除失败"));
            log_singleton::Write_Log(QString::fromLocal8Bit("文件删除失败"), Log_Level::Error);
        }
        InitRecipesInFiles();
    } else {
        lbl_OperationResult->setText(QString::fromLocal8Bit("不可删除当前工单!!!"));
        log_singleton::Write_Log(QString::fromLocal8Bit("不可删除当前工单!!!"), Log_Level::Error);
    }
}

void JsonRecipeWidget::slot_RecipeChanged(JsonRecipeParse* m_RecipeChanged)
{
    CurrentRecipe = m_RecipeChanged;
    TreeWidget->clear();
    CurrentRecipe->ReadParams();

    InitTreeWidget();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    QString Timelog = QString::fromLocal8Bit("当前时间: ") + currentDateTimeString;
    log_singleton::Write_Log(Timelog, Log_Level::General);
    //到此为止切换配方完成
    emit sig_CameraParamsChangeRecipe();
}

void JsonRecipeWidget::ReadValue2Tree()
{
    //刷新前先清空
    while (rootItem->childCount() > 0) {
        QTreeWidgetItem* child = rootItem->takeChild(0);
        delete child;
    }
    while (rootItem1->childCount() > 0) {
        QTreeWidgetItem* child = rootItem1->takeChild(0);
        delete child;
    }

    SetValue2Tree(ParamType::LENGTH, QString::number(CurrentRecipe->Length), rootItem);
    SetValue2Tree(ParamType::LENGTH_ERROR, QString::number(CurrentRecipe->LengthError), rootItem);
    SetValue2Tree(ParamType::WIDTH, QString::number(CurrentRecipe->Width), rootItem);
    SetValue2Tree(ParamType::WIDTH_ERROR, QString::number(CurrentRecipe->WidthError), rootItem);
    SetValue2Tree(ParamType::DIAGONAL1, QString::number(CurrentRecipe->Diagonal1), rootItem);
    SetValue2Tree(ParamType::DIAGONAL1_ERROR, QString::number(CurrentRecipe->Diagonal1Error), rootItem);
    SetValue2Tree(ParamType::DIAGONAL2, QString::number(CurrentRecipe->Diagonal2), rootItem);
    SetValue2Tree(ParamType::DIAGONAL2_ERROR, QString::number(CurrentRecipe->Diagonal2Error), rootItem);

    SetValue2Tree(ParamType::LENGTH_2, QString::number(CurrentRecipe->Length_2), rootItem1);
    SetValue2Tree(ParamType::LENGTH_ERROR_2, QString::number(CurrentRecipe->LengthError_2), rootItem1);
    SetValue2Tree(ParamType::WIDTH_2, QString::number(CurrentRecipe->Width_2), rootItem1);
    SetValue2Tree(ParamType::WIDTH_ERROR_2, QString::number(CurrentRecipe->WidthError_2), rootItem1);
    SetValue2Tree(ParamType::DIAGONAL1_2, QString::number(CurrentRecipe->Diagonal1_2), rootItem1);
    SetValue2Tree(ParamType::DIAGONAL1_ERROR_2, QString::number(CurrentRecipe->Diagonal1Error_2), rootItem1);
    SetValue2Tree(ParamType::DIAGONAL2_2, QString::number(CurrentRecipe->Diagonal2_2), rootItem1);
    SetValue2Tree(ParamType::DIAGONAL2_ERROR_2, QString::number(CurrentRecipe->Diagonal2Error_2), rootItem1);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + QString::fromLocal8Bit(" 工单: ") + cbx_RecipeSelect->currentText() + QString::fromLocal8Bit(" 参数已读取");
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::SaveValue2tree()
{
    if (abs(CurrentRecipe->Length - rootItem->child(0)->text(1).toDouble()) > 200 || abs(CurrentRecipe->Width - rootItem->child(2)->text(1).toDouble()) > 100)
        isNeedReplot = true;

    CurrentRecipe->Length = rootItem->child(0)->text(1).toDouble();
    CurrentRecipe->LengthError = rootItem->child(1)->text(1).toDouble();
    CurrentRecipe->Width = rootItem->child(2)->text(1).toDouble();
    CurrentRecipe->WidthError = rootItem->child(3)->text(1).toDouble();
    CurrentRecipe->Diagonal1 = rootItem->child(4)->text(1).toDouble();
    CurrentRecipe->Diagonal1Error = rootItem->child(5)->text(1).toDouble();
    CurrentRecipe->Diagonal2 = rootItem->child(6)->text(1).toDouble();
    CurrentRecipe->Diagonal2Error = rootItem->child(7)->text(1).toDouble();

    CurrentRecipe->Length_2 = rootItem1->child(0)->text(1).toDouble();
    CurrentRecipe->LengthError_2 = rootItem1->child(1)->text(1).toDouble();
    CurrentRecipe->Width_2 = rootItem1->child(2)->text(1).toDouble();
    CurrentRecipe->WidthError_2 = rootItem1->child(3)->text(1).toDouble();
    CurrentRecipe->Diagonal1_2 = rootItem1->child(4)->text(1).toDouble();
    CurrentRecipe->Diagonal1Error_2 = rootItem1->child(5)->text(1).toDouble();
    CurrentRecipe->Diagonal2_2 = rootItem1->child(6)->text(1).toDouble();
    CurrentRecipe->Diagonal2Error_2 = rootItem1->child(7)->text(1).toDouble();

    CurrentRecipe->WriteParams();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + QString::fromLocal8Bit(" 工单参数已保存");
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    if (isNeedReplot) {
        emit sig_FlawWidgetShouldReplot(); //重绘示意图界面信号
    }
    isNeedReplot = false;

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::SetValue2Tree(int paramName, QString Value, QTreeWidgetItem* ParentItem)
{
    QString Name2String;
    Name2String = SetItemName(paramName);
    QTreeWidgetItem* child = new QTreeWidgetItem(ParentItem);
    child->setText(0, Name2String);
    child->setText(1, Value);
    ParentItem->addChild(child);
}

void JsonRecipeWidget::slot_ItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (column == 1) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }
}
