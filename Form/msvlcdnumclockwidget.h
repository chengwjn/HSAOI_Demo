#ifndef MSVLCDNUMCLOCKWIDGET_H
#define MSVLCDNUMCLOCKWIDGET_H

#include <QTimer>
#include <QWidget>
namespace Ui {
class MsvLCDNumClockWidget;
}

class MsvLCDNumClockWidget : public QWidget {
    Q_OBJECT

public:
    explicit MsvLCDNumClockWidget(QWidget* parent = 0);
    ~MsvLCDNumClockWidget();

private:
    Ui::MsvLCDNumClockWidget* ui;

    QTimer* time_update_show_timer;
private slots:
    void updateTimeShow();
};

#endif // MSVLCDNUMCLOCKWIDGET_H
