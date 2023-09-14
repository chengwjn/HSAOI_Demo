/*******************************************
    @ClassName   : GlassStatisticTableWidget
    @Description : Description
    @Creator     : Huxujie
    @Author      : Huxujie
    @Date        : 2023-09-01
********************************************/
#ifndef GLASSSTATICTABLEWIDGET_H
#define GLASSSTATICTABLEWIDGET_H

#include "Global.h"
#include <QDateTime>
#include <QFile>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QXmlStreamReader>
#include <QtDebug>

class GlassStatisticTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit GlassStatisticTableWidget(QWidget* parent = 0);

public:
    QLabel* TableTitle;

    QTableWidget* tableWidget;

public:
    void InitTable(QTableWidget* tableWidget);
    void InitTableFromXml(QTableWidget* tableWidget);
public slots:
    void slot_insertRowData(GLASSINFO* info);
};

#endif // GLASSSTATICTABLEWIDGET_H
