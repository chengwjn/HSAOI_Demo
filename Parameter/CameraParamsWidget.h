#ifndef CAMERAPARAMSWIDGET_H
#define CAMERAPARAMSWIDGET_H

#include "Parameter/JsonRecipeParse.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

class CameraParamsWidget : public QWidget {
    Q_OBJECT
public:
    explicit CameraParamsWidget(QWidget* parent = nullptr, JsonRecipeParse* RecipeParse = nullptr);

    JsonRecipeParse* CurrentRecipe;

private:
    QPushButton* btn_Save;
    QPushButton* btn_Read;

    QTreeWidget* TreeWidget;

    QTreeWidgetItem* rootItem0;
    QTreeWidgetItem* rootItem1;
    QTreeWidgetItem* rootItem2;
    QTreeWidgetItem* rootItem3;

    void InitWidgetLayout();
    void InitTreeWidget();
    void ReadValue2Tree();
    void SetValue2Tree(QString paramName, QString Value, QTreeWidgetItem* ParentItem);
signals:
public slots:
    void slot_SaveValue2Recipe();
    //    void slot_ReadValue2Recipe();
    void slot_ChangeRecipe();
private slots:
    void slot_ItemDoubleClicked(QTreeWidgetItem* item, int column);
};

#endif // CAMERAPARAMSWIDGET_H
