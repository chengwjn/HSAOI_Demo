#include "RecipeWidget.h"
#include "ui_RecipeWidget.h"

RecipeWidget::RecipeWidget(QWidget* parent, RecipeParse* RecipeParse)
    : QWidget(parent)
    , ui(new Ui::RecipeWidget)
{
    ui->setupUi(this);
    CurrentRecipe = RecipeParse;

    InitWidgetLayout();
    this->setWindowTitle(CurrentRecipe->m_RecipeName);
    InitRecipesInFiles();
    InitTableWidget();
}

RecipeWidget::~RecipeWidget()
{
    delete ui;
}

void RecipeWidget::SetValue2Table(int ParamName, QString Value)
{
    QString Name2String;
    Name2String = SetItemName(ParamName);

    TableWidget->setItem(ParamName, 0, new QTableWidgetItem(Name2String));
    TableWidget->setItem(ParamName, 1, new QTableWidgetItem(Value));
}

void RecipeWidget::SelectRecipe()
{
    if (cbx_RecipeSelect->currentText() == CurrentRecipe->m_RecipeName) {
        lbl_OperationResult->setText("No Need Operate");
        return;
    }
    this->setWindowTitle(cbx_RecipeSelect->currentText());
    emit sig_DeliverName(cbx_RecipeSelect->currentText());
}

void RecipeWidget::CreateNewRecipe()
{
    QDialog GetRecipeNameDialog;
    QLineEdit* lineEdit = new QLineEdit(&GetRecipeNameDialog);
    QPushButton* Btn_Yes = new QPushButton("确定", &GetRecipeNameDialog);
    QString InputText = "";

    QObject::connect(Btn_Yes, &QPushButton::clicked, [&]() {
        InputText = lineEdit->text();
        qDebug() << "用户输入: " << InputText;
        GetRecipeNameDialog.close();
    });

    QVBoxLayout* layout = new QVBoxLayout(&GetRecipeNameDialog);
    layout->addWidget(lineEdit);
    layout->addWidget(Btn_Yes);

    // 显示对话框
    GetRecipeNameDialog.exec();
    qDebug() << InputText;

    QString SourceFilePath = "Recipes/" + CurrentRecipe->m_RecipeName + ".xml";
    QString DestFilePath = "Recipes/" + InputText + ".xml";

    qDebug() << SourceFilePath;
    qDebug() << DestFilePath;
    if (QFile::copy(SourceFilePath, DestFilePath)) {
        qDebug() << "文件复制成功";
        // 检查文件是否存在
        if (!QFile::exists(DestFilePath))
            qDebug() << "File do not exists";
    } else {
        qDebug() << "文件复制失败";
    }
    InitRecipesInFiles();
    int SelectIndex = cbx_RecipeSelect->findText(InputText);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
    btn_SelectRecipe->click();
}

void RecipeWidget::DeleteRecipe()
{
    if (CurrentRecipe->m_RecipeName != cbx_RecipeSelect->currentText()) {

        QString filePath = "Recipes/" + cbx_RecipeSelect->currentText() + ".xml"; // 文件路径
        // 创建QFile对象
        QFile file(filePath);
        // 删除文件
        if (file.remove()) {
            qDebug() << "文件删除成功";
        } else {
            qDebug() << "文件删除失败";
        }
        InitRecipesInFiles();
    } else {
        lbl_OperationResult->setText("Cannot Delete Current Recipe!!!");
        qDebug() << "Cannot Delete Current Recipe!!!";
    }
}

void RecipeWidget::slot_RecipeChanged(RecipeParse* m_RecpipeChanged)
{
    CurrentRecipe = m_RecpipeChanged;
    TableWidget->clearContents();

    CurrentRecipe->ReadParams();
    ReadValue2Table();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    qDebug() << "Current DateTime:" << currentDateTimeString;
    //到此为止切换配方完成
}

void RecipeWidget::SaveTable2Value()
{
    CurrentRecipe->Read_Length = TableWidget->item(0, 1)->text().toFloat();
    CurrentRecipe->Read_LengthError = TableWidget->item(1, 1)->text().toFloat();
    CurrentRecipe->Read_Width = TableWidget->item(2, 1)->text().toFloat();
    CurrentRecipe->Read_WidthError = TableWidget->item(3, 1)->text().toFloat();

    CurrentRecipe->Read_Diagonal1 = TableWidget->item(4, 1)->text().toFloat();
    CurrentRecipe->Read_Diagonal1Error = TableWidget->item(5, 1)->text().toFloat();
    CurrentRecipe->Read_Diagonal2 = TableWidget->item(6, 1)->text().toFloat();
    CurrentRecipe->Read_Diagonal2Error = TableWidget->item(7, 1)->text().toFloat();

    CurrentRecipe->WriteParams();
    lbl_OperationResult->setText("Recipe Param Saved");
    lbl_OperationResult->adjustSize();
    qDebug() << "Recipe Param Saved";
}

void RecipeWidget::ReadValue2Table()
{
    //    CurrentRecipe->ReadParams();
    SetValue2Table(LENGTH, QString::number(CurrentRecipe->Read_Length));
    SetValue2Table(LENGTH_ERROR, QString::number(CurrentRecipe->Read_LengthError));
    SetValue2Table(WIDTH, QString::number(CurrentRecipe->Read_Width));
    SetValue2Table(WIDTH_ERROR, QString::number(CurrentRecipe->Read_WidthError));
    SetValue2Table(DIAGONAL1, QString::number(CurrentRecipe->Read_Diagonal1));
    SetValue2Table(DIAGONAL1_ERROR, QString::number(CurrentRecipe->Read_Diagonal1Error));
    SetValue2Table(DIAGONAL2, QString::number(CurrentRecipe->Read_Diagonal2));
    SetValue2Table(DIAGONAL2_ERROR, QString::number(CurrentRecipe->Read_Diagonal2Error));
    lbl_OperationResult->setText("Recipe Param Read");
    lbl_OperationResult->adjustSize();
    qDebug() << "Recipe Param Read";
}

void RecipeWidget::InitTableWidget()
{

    QStringList HStrList;
    HStrList.push_back(QString("Data"));
    HStrList.push_back(QString("Value"));
    int HlableCnt = HStrList.count();
    TableWidget->setColumnCount(HlableCnt);
    TableWidget->setRowCount(8);

    //设置列标签
    TableWidget->setHorizontalHeaderLabels(HStrList);
    TableWidget->resizeRowsToContents();

    TableWidget->clearContents();
    ReadValue2Table();
}

void RecipeWidget::InitRecipesInFiles()
{

    cbx_RecipeSelect->clear();

    QString FoldPath = "Recipes";
    QDir Folder(FoldPath);
    QStringList Filters;
    Filters << "*.xml";
    Folder.setNameFilters(Filters);

    QStringList FileNames;
    foreach (QString fileName, Folder.entryList(QDir::Files)) {
        QString baseName = QFileInfo(fileName).baseName(); // 获取不带扩展名的文件名
        FileNames.append(baseName);
    }
    foreach (QString FileName, FileNames) {
        cbx_RecipeSelect->addItem(FileName);
        qDebug() << FileName;
    }
    int SelectIndex = cbx_RecipeSelect->findText(CurrentRecipe->m_RecipeName);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
}

QString RecipeWidget::SetItemName(int ParamName)
{
    switch (ParamName) {
    case 0:
        return "Length";
        break;
    case 1:
        return "LengthError";
        break;
    case 2:
        return "Width";
        break;
    case 3:
        return "WidthError";
        break;
    case 4:
        return "Diagonal1";
        break;
    case 5:
        return "Diagonal1Error";
        break;
    case 6:
        return "Diagonal2";
        break;
    case 7:
        return "Diagonal2Error";
        break;
    }
}

void RecipeWidget::InitWidgetLayout()
{
    cbx_RecipeSelect = new QComboBox(this);
    ui->Layout_head->setContentsMargins(10, 10, 10, 0);
    ui->Layout_head->addWidget(cbx_RecipeSelect);

    TableWidget = new QTableWidget(this);
    TableWidget->resize(300, 300);
    TableWidget->move(20, 60);
    ui->Layout_table->setContentsMargins(10, 10, 10, 0);
    ui->Layout_table->addWidget(TableWidget);

    btn_SelectRecipe = new QPushButton(this);
    btn_SelectRecipe->setText("Select");
    connect(btn_SelectRecipe, SIGNAL(clicked()), this, SLOT(SelectRecipe()));

    btn_NewRecipe = new QPushButton(this);
    btn_NewRecipe->setText("New");
    connect(btn_NewRecipe, SIGNAL(clicked()), this, SLOT(CreateNewRecipe()));

    btn_DeleteRecipe = new QPushButton(this);
    btn_DeleteRecipe->setText("Delete");
    connect(btn_DeleteRecipe, SIGNAL(clicked()), this, SLOT(DeleteRecipe()));

    btn_Read = new QPushButton(this);
    btn_Read->setText("Read");
    connect(btn_Read, SIGNAL(clicked()), this, SLOT(ReadValue2Table()));

    btn_Save = new QPushButton(this);
    btn_Save->setText("Save");
    connect(btn_Save, SIGNAL(clicked()), this, SLOT(SaveTable2Value()));

    ui->Layout_btns->setContentsMargins(20, 20, 20, 20);
    ui->Layout_btns->addWidget(btn_SelectRecipe);
    ui->Layout_btns->addWidget(btn_NewRecipe);
    ui->Layout_btns->addWidget(btn_DeleteRecipe);
    ui->Layout_btns->addWidget(btn_Read);
    ui->Layout_btns->addWidget(btn_Save);
    ui->Layout_btns->setAlignment(Qt::AlignTop);

    lbl_OperationResult = new QLabel(this);
    lbl_OperationResult->move(20, 385);
    ui->Layout_bottom->setContentsMargins(10, 0, 10, 0);
    ui->Layout_bottom->addWidget(lbl_OperationResult);

    this->setFixedSize(400, 300);
}
