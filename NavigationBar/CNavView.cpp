#include "CNavView.h"
#include <QColor>

CNavView::CNavView(QWidget *parent) : QListView (parent)
{
    setStyleSheet(
        QString(
        "QListView{background-color:%1;"
        "border:0px solid %2;"
        "border-right-width:1px;}")
        .arg("239, 241, 250")
        .arg("214, 216, 224"));
}

CNavView::~CNavView()
{

}
