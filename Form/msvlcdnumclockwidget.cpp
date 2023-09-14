#include "msvlcdnumclockwidget.h"
#include "ui_msvlcdnumclockwidget.h"
#include<QDateTime>
#include<QFontDatabase>
MsvLCDNumClockWidget::MsvLCDNumClockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsvLCDNumClockWidget)
{
    ui->setupUi(this);
    time_update_show_timer = new QTimer(this);
    ui->label_date->setAlignment(Qt::AlignCenter);
    ui->label_time->setAlignment(Qt::AlignCenter);
    ui->label_day->setAlignment(Qt::AlignCenter);
//    ui->label_date->setStyleSheet("font:24px;color:#00FF00;");
//    ui->label_time->setStyleSheet("font:48px;color:#00FF00;");
//    ui->label_day->setStyleSheet("font:24px;color:#00FF00;");

    ui->label_date->setStyleSheet("color:#00FF00;");
    ui->label_time->setStyleSheet("color:#00FF00;");
    ui->label_day->setStyleSheet("color:#00FF00;");

    QFontDatabase::addApplicationFont(":/font/res/DINCond-Black.otf");
    ui->label_time->setFont(QFont("DINCond-Black",48));
    ui->label_day->setFont(QFont("DINCond-Black",24));
    ui->label_date->setFont(QFont("DINCond-Black",24));

    connect(time_update_show_timer,SIGNAL(timeout()),this,SLOT(updateTimeShow()));
    time_update_show_timer->start(1000);
    updateTimeShow();
}

MsvLCDNumClockWidget::~MsvLCDNumClockWidget()
{
    delete ui;
}

void MsvLCDNumClockWidget::updateTimeShow()
{
    QString text = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->label_time->setText(text);
    text = QDateTime::currentDateTime().toString("yyyy.MM.dd");
    ui->label_date->setText(text);

    text = QDateTime::currentDateTime().toString("dddd");
    QString day_text = "";

    if(text == "Monday")
    {
        day_text = tr("Monday");
    }
    else if(text == "Tuseday")
    {
        day_text = tr("Tuseday");
    }
    else if(text == "Wednesday")
    {
        day_text = tr("Wednesday");
    }
    else if(text == "Thursday")
    {
        day_text = tr("Thursday");
    }
    else if(text == "Friday")
    {
        day_text = tr("Friday");
    }
    else if(text == "Saturday")
    {
        day_text = tr("Saturday");
    }
    else if(text == "Sunday")
    {
        day_text = tr("Sunday");
    }
    else
    {
        day_text = text;
    }

    ui->label_day->setText(day_text);
}
