/*******************************************
    @ClassName   : SingleFlawShowWidget
    @Description : Description
    @Creator     : Zhangjun
    @Author      : Zhangjun
    @Date        : 2023-09-01
********************************************/
#ifndef SINGLEFLAWSHOWWIDGET_H
#define SINGLEFLAWSHOWWIDGET_H

#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QWidget>

namespace Ui {
class SingleFlawShowWidget;
}

class SingleFlawShowWidget : public QWidget {
    Q_OBJECT

public:
    explicit SingleFlawShowWidget(Qt::Orientation ori, Qt::Orientation pic_ori,
        QWidget* parent = 0);
    ~SingleFlawShowWidget();

signals:

public:
    void initLayout();

public slots:
    void showFlawImage(QTableWidgetItem* item);

    void onItemDoubleClicked(QTableWidgetItem*);

    void showTableData();

private:
    Ui::SingleFlawShowWidget* ui;
    Qt::Orientation m_orientation;
    Qt::Orientation m_pic_orientation;
};

#endif // SINGLEFLAWSHOWWIDGET_H
