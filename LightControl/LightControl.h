#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include "Global.h"
#include "Parameter/XmlParse.h"
#include "RegParasComm.h"
#include <QTreeWidget>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#define ADDR0 0x0070
#define ADDR1 0x0010
#define ADDR2 0x0860
#define ADDR3 0x0864
#define ADDR4 0x0868
#define ADDR5 0x086C
#define ADDR6 0x0800
#define ADDR7 0x001C
#define ADDR8 0x0074
#define ADDR9 0x0078
#define ADDR10 0x007C
#define ADDR11 0x0090
#define ADDR12 0x0094
#define ADDR13 0x00C8
#define ADDR14 0x00CC
#define ADDR15 0x00D0
#define ADDR16 0x00D8
#define ADDR17 0x00DC
#define ADDR18 0x00DD
#define ADDR19 0x0098
#define ADDR20 0x009C
#define ADDR21 0x00A0
#define ADDR22 0x00A4
#define ADDR23 0x00A8
#define ADDR24 0x00AC
#define ADDR25 0x00B0
#define ADDR26 0x00B4
#define ADDR27 0x00B8
#define ADDR28 0x00BC
#define ADDR29 0x00C0
#define ADDR30 0x00C4
#define ADDR31 0x0040
#define ADDR32 0x00D4

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControl;
}
QT_END_NAMESPACE

class LightControl : public QWidget {
    Q_OBJECT

public:
    explicit LightControl(RegParasComm& sig_comm, QWidget* parent = nullptr);
    ~LightControl();

private slots:
    void slot_getButton_clicked();

    void slot_setButton_clicked();

    void slot_saveButton_clicked();

    void onItemDoubleClicked(QTreeWidgetItem* item, int column);

private:
    RegParasComm& m_pSig_comm;
    //    RegParasComm *regComm;
    QTreeWidgetItem* specificItem0;
    QTreeWidgetItem* specificItem1;
    QTreeWidgetItem* specificItem2;
    QTreeWidgetItem* childItem0;
    QTreeWidgetItem* childItem1;
    QTreeWidgetItem* childItem2;
    QTreeWidgetItem* childItem3;
    QTreeWidgetItem* childItem4;
    QTreeWidgetItem* childItem5;
    QTreeWidgetItem* childItem6;
    QTreeWidgetItem* childItem7;
    QTreeWidgetItem* childItem8;
    QTreeWidgetItem* childItem9;
    QTreeWidgetItem* childItem10;
    QTreeWidgetItem* childItem11;
    QTreeWidgetItem* childItem12;
    QTreeWidgetItem* childItem13;
    QTreeWidgetItem* childItem14;
    QTreeWidgetItem* childItem15;
    QTreeWidgetItem* childItem16;
    QTreeWidgetItem* childItem17;
    QTreeWidgetItem* childItem18;
    QTreeWidgetItem* childItem19;
    QTreeWidgetItem* childItem20;
    QTreeWidgetItem* childItem21;
    QTreeWidgetItem* childItem22;
    QTreeWidgetItem* childItem23;
    QTreeWidgetItem* childItem24;
    QTreeWidgetItem* childItem25;
    QTreeWidgetItem* childItem26;
    QTreeWidgetItem* childItem27;
    QTreeWidgetItem* childItem28;
    QTreeWidgetItem* childItem29;
    QTreeWidgetItem* childItem30;
    QTreeWidgetItem* childItem31;
    QTreeWidgetItem* childItem32;

    void GetData();

private:
    QHBoxLayout* Layout0;
    QVBoxLayout* Layout1;

private:
    Ui::LightControl* ui;
};
#endif // LIGHTCONTROL_H
