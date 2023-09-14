#include "singleflawshowwidget.h"
#include "ui_singleflawshowwidget.h"
#include <QDebug>

SingleFlawShowWidget::SingleFlawShowWidget(Qt::Orientation ori,
    Qt::Orientation pic_ori,
    QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SingleFlawShowWidget)
{
    m_orientation = ori;
    m_pic_orientation = pic_ori;
    ui->setupUi(this);

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this,
        SLOT(onItemDoubleClicked(QTableWidgetItem*)));

    showTableData();
    initLayout();
}

void SingleFlawShowWidget::showFlawImage(QTableWidgetItem* item)
{

    if (item) {
        // 获取选中的行
        int row = item->row();
        if (row == 1) {
            QPixmap pixmap("C:/Users/zhangjun/Desktop/微信图片_20230814131625.png");
            ui->label->setPixmap(pixmap.scaled(320, 320));
            ui->label->setFixedSize(320, 320);
            ui->label_2->setPixmap(pixmap.scaled(320, 320));
            ui->label_2->setFixedSize(320, 320);
            ui->label_3->setPixmap(pixmap.scaled(320, 320));
            ui->label_3->setFixedSize(320, 320);
        } else if (row == 0) {
            ui->label->clear();
            ui->label_2->clear();
            ui->label_3->clear();
        }
    }
}

void SingleFlawShowWidget::initLayout()
{

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void SingleFlawShowWidget::onItemDoubleClicked(QTableWidgetItem*)
{
    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
}

void SingleFlawShowWidget::showTableData()
{
    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this,
        &SingleFlawShowWidget::showFlawImage);
    ui->tableWidget->setRowCount(5);

    QTableWidgetItem* item1 = new QTableWidgetItem("1");
    QTableWidgetItem* item2 = new QTableWidgetItem("2");
    ui->tableWidget->setItem(0, 0, item1);
    ui->tableWidget->setItem(1, 0, item2);
}

SingleFlawShowWidget::~SingleFlawShowWidget() { delete ui; }
