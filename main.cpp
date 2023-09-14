#include "MainForm.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainForm AppForm;
    AppForm.show();
    return a.exec();
}
