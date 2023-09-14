#include "MainForm.h"
#include "Global.h"
#include "ui_MainForm.h"

MainForm::MainForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    vbox = new QVBoxLayout();
    setLayout(vbox);

    Global::InitGlobalParam(); //全局参数初始化
    title_bar = new TitleBar(this);
    main_window = new MainWindow(this);

    vbox->addWidget(title_bar);
    vbox->addWidget(main_window);

    showFullScreen();
}

MainForm::~MainForm()
{
    delete ui;
}
