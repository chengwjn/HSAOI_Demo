/*******************************************
    @ClassName   : QImageAcquisition
    @Description : 图像采集类，在原采集功能上进行修改，包含多场图像拆分功能
    @Creator     : Chengwenjie
    @Author      : Chengwenjie,Huxujie,Yangruyi
    @Date        : 2023-07-12
********************************************/
//============================================================================================
//用QT 4.8之后推荐的方式创建线程，只需要将一个继承于QObject的类通过moveToThread移到QThread的一个对象中
//需要注意的是：
//只有在槽中执行的操作才是在线程中执行的，所以需要通过连接信号槽的方式来实现
//如果object对象存在父对象，不能将其移到子线程中执行。
//============================================================================================
#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include "DVPCamera.h"
#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QWaitCondition>

#define GRABTIMEOUT 3000 // 图像获取的超时时间 ms

class QImageAcquisition : public QObject {
    Q_OBJECT
public:
    QImageAcquisition(dvpHandle& handle, QObject* parent = nullptr, int FieldCount = 0);
    ~QImageAcquisition();
    bool IsValidHandle(dvpHandle handle); // 判断句柄是否有效
    dvpHandle m_handle;
    QImage m_ShowImage;
    //    bool         m_bAcquireImg;              // 采集线程是否结束的标志：true 运行；false 退出
    //    bool         ThreadSoftTriggerFlag;      // 软触发标志

    dvpFrame m_pFrame; // 采集到的图像的结构体指针
    void* pBuffer; // 采集到的图像的内存首地址

    QMutex m_threadMutex; // 互斥量
    QTimer* m_timer;

    int WIDTH_BYTES(int BitCount, int Width);
    int m_FieldCount; //场计数
    QList<QImage> ImageList;

    dvpFrameCount FrameCount;
    byte* Src_Buffer;
    byte* View_Buffer;
    int FrameWidth = 8192;
    int FrameHeight = 1000;
    int ImageOffset = 100;
    int ImageLineSize = 0;
    byte** Last_Buffer;

private slots:
    void slotGrabFrames(); // 抓帧函数

signals:
    void signalDisplay(); // 显示图像信号
    void sig_buffer(dvpFrame Frame, void* Buffer);
    void sig_DeliverImage(QList<QImage> ImageList);
};

#endif // IMAGEACQUISITION_H
