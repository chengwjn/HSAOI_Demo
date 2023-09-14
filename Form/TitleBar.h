/*******************************************
    @ClassName   : TitleBar
    @Description : 标题栏
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-08-08
********************************************/
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent = nullptr);

protected:
    // 双击标题栏进行界面的最大化/还原
    //    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    // 进行鼠界面的拖动
    //    virtual void mousePressEvent(QMouseEvent* event);

    // 设置界面标题与图标
    //    virtual bool eventFilter(QObject* obj, QEvent* event);

private slots:
    // 进行最小化、最大化/还原、关闭操作
    //    void onClicked();
    //    void user_button_clicked();
    //    void update_user_name(QString& name);

private:
    // 最大化/还原
    //    void updateMaximize();
    //    void updateFullscreen();

private:
    QLabel* m_pIconLabel;
    QLabel* m_pTitleLabel;
    QPushButton* m_pMinimizeButton;
    QPushButton* m_pMaximizeButton;
    QPushButton* m_pCloseButton;
    QPushButton* m_pFullScreenButton;
    QPushButton* m_pUserButton;
};

#endif // TITLEBAR_H
