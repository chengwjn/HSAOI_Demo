#include "ImageAcquisition.h"
#include "DVPCamera.h"

QImageAcquisition::QImageAcquisition(dvpHandle& handle, QObject* parent, int FieldCount)
    : QObject(parent)
{
    // 初始化成员变量
    m_handle = handle;
    pBuffer = NULL;
    m_FieldCount = FieldCount;

    ImageLineSize = WIDTH_BYTES(8, 8192);
    Last_Buffer = new byte*[m_FieldCount];
    for (int i = 0; i < m_FieldCount; i++) {
        Last_Buffer[i] = new byte[ImageLineSize * ImageOffset];
    }

    m_timer = new QTimer();

    //将定时器超时信号与槽(功能函数)联系起来
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotGrabFrames()));

    //定时器每50毫秒采集一次，显示帧率大概维持在20帧每秒
    m_timer->start(50);
    //qDebug()<< __FUNCTION__ << " id = "<< QThread::currentThreadId();
}

QImageAcquisition::~QImageAcquisition()
{
    if (m_timer->isActive()) {
        m_timer->stop();
        delete m_timer;
    }
}

bool QImageAcquisition::IsValidHandle(dvpHandle handle)
{
    bool bValidHandle = false;
    dvpIsValid(handle, &bValidHandle);

    return bValidHandle;
}

int QImageAcquisition::WIDTH_BYTES(int BitCount, int Width)
{
    int nwBytePerLine;
    nwBytePerLine = (Width * BitCount + 31) / 32 * 4;
    return nwBytePerLine;
}

void QImageAcquisition::slotGrabFrames()
{
    dvpStatus status;
    //pBuffer为图片缓存,在此处做多场分离
    status = dvpGetFrame(m_handle, &m_pFrame, &pBuffer, GRABTIMEOUT);
    if (status == DVP_STATUS_OK) {
        if (m_threadMutex.tryLock()) {

            //帧计数
            dvpGetFrameCount(m_handle, &FrameCount);
            int strFrameCount = FrameCount.uFrameCount;
            //单通道图像宽度
            FrameWidth = m_pFrame.iWidth;
            //单通道图像高度
            if (strFrameCount % 20 == 1) {
                FrameHeight = m_pFrame.iHeight / m_FieldCount;
            } else {
                FrameHeight = m_pFrame.iHeight / m_FieldCount + ImageOffset;
            }

            qDebug() << "strFrameCount " << strFrameCount << pBuffer;

            if (m_pFrame.format == FORMAT_BGR24) {

                //其他版本先把BGR数据转成RGB数据，再用RGB数据转QImage
                DWORD A = GetCurrentTime();
                int ImageLineSize = WIDTH_BYTES(24, FrameWidth);
                int ImageSize = 0;

                ImageSize = ImageLineSize * FrameHeight;

                byte* Src_Buffer = new byte[ImageLineSize * m_pFrame.iHeight];
                Src_Buffer = (byte*)pBuffer;

                byte** Dest_Buffer = new byte*[m_FieldCount];
                for (int i = 0; i < m_FieldCount; i++) {
                    Dest_Buffer[i] = new byte[ImageSize];
                }

                byte** Last_Buffer = new byte*[m_FieldCount];
                for (int i = 0; i < m_FieldCount; i++) {
                    Last_Buffer[i] = new byte[ImageLineSize * ImageOffset];
                }
                //重叠区域复制
                if (strFrameCount % 20 > 1) {
                    for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
                        memcpy(Dest_Buffer[lightnum], Last_Buffer[lightnum], ImageLineSize * ImageOffset);
                    }
                }
                // 图片重组
                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
                    for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
                        if (strFrameCount % 20 == 1) {
                            memcpy(Dest_Buffer[lightnum] + HeightCount * ImageLineSize, Src_Buffer + (m_FieldCount * HeightCount + lightnum) * ImageLineSize, ImageLineSize);
                        } else {
                            memcpy(Dest_Buffer[lightnum] + (HeightCount + ImageOffset) * ImageLineSize, Src_Buffer + (m_FieldCount * HeightCount + lightnum) * ImageLineSize, ImageLineSize);
                        }
                    }
                    //重叠区域获取
                    if (HeightCount >= m_pFrame.iHeight / m_FieldCount - ImageOffset) {
                        for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
                            memcpy(Last_Buffer[lightnum] + (HeightCount - (m_pFrame.iHeight / m_FieldCount - ImageOffset)) * ImageLineSize, Src_Buffer + (m_FieldCount * HeightCount + lightnum) * ImageLineSize, ImageLineSize);
                        }
                    }
                }

                DWORD F = GetCurrentTime();
                DWORD G = F - A;
                for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
                    m_ShowImage = QImage((uchar*)Dest_Buffer[lightnum], FrameWidth, FrameHeight, QImage::Format_RGB888);
                    m_ShowImage = m_ShowImage.rgbSwapped();
                    ImageList.append(m_ShowImage); //将图片接入到Qlist中
                    //                    ImageList.insert(0, m_ShowImage);
                    //              QString strFilePath = QString("D:\\TEST%1.bmp").arg(lightnum);
                    //            m_ShowImage.save(strFilePath, "bmp", -1);
                }
                qDebug() << G;
            } else {
                DWORD A = GetCurrentTime();
                int ImageSize = 0;
                ImageSize = ImageLineSize * FrameHeight;
                byte** Dest_Buffer = new byte*[m_FieldCount];
                for (int i = 0; i < m_FieldCount; i++) {
                    Dest_Buffer[i] = new byte[ImageSize];
                }
                //重叠区域复制
                if (strFrameCount % 20 > 1) {
                    for (int lightnum1 = 0; lightnum1 < m_FieldCount; lightnum1++) {
                        memcpy(Dest_Buffer[lightnum1], Last_Buffer[lightnum1], ImageLineSize * ImageOffset);
                    }
                }
                // 图片重组
                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
                    for (int lightnum2 = 0; lightnum2 < 6; lightnum2++) {
                        if (strFrameCount % 20 == 1) {
                            memcpy(Dest_Buffer[lightnum2] + HeightCount * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                        } else {
                            memcpy(Dest_Buffer[lightnum2] + (HeightCount + ImageOffset) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum2) * ImageLineSize, ImageLineSize);
                        }
                    }
                    //重叠区域获取
                    if (HeightCount >= m_pFrame.iHeight / m_FieldCount - ImageOffset) {
                        for (int lightnum3 = 0; lightnum3 < m_FieldCount; lightnum3++) {
                            memcpy(Last_Buffer[lightnum3] + (HeightCount - (m_pFrame.iHeight / m_FieldCount - ImageOffset)) * ImageLineSize, (byte*)pBuffer + (m_FieldCount * HeightCount + lightnum3) * ImageLineSize, ImageLineSize);
                        }
                    }
                }
                for (int lightnum4 = 0; lightnum4 < m_FieldCount; lightnum4++) {

                    //          m_ShowImage = QImage((uchar*)Dest_Buffer[lightnum4], FrameWidth, FrameHeight, QImage::Format_Grayscale8);
                    //         delete[] Dest_Buffer[lightnum];
                    //
                    //             QString strFilePath = QString("D:\\TEST%1.bmp").arg(lightnum4);
                    //           m_ShowImage.save(strFilePath, "bmp", -1);
                }

                DWORD F = GetCurrentTime();
                DWORD G = F - A;
                qDebug() << G;

                for (int lightnum5 = 0; lightnum5 < m_FieldCount; lightnum5++) {
                    delete[] Dest_Buffer[lightnum5];
                }
                delete[] Dest_Buffer;
                Dest_Buffer = nullptr;

                //                    delete[] Src_Buffer;
                //                    Src_Buffer = nullptr;
                //    m_ShowImage = QImage((uchar*)pBuffer, m_pFrame.iWidth, m_pFrame.iHeight, QImage::Format_Grayscale8); //5.7
            }

            //            emit sig_buffer(m_pFrame, pBuffer);//传递缓存出去处理-23070121
            m_threadMutex.unlock();
            qDebug() << "ImageList has iamge conunt: " << ImageList.size();
        }

        emit signalDisplay();
    }
}

//void QImageAcquisition::slotGrabFrames()
//{
//    dvpStatus status;

//    //pBuffer为图片缓存,在此处做多场分离
//    status = dvpGetFrame(m_handle, &m_pFrame, &pBuffer, GRABTIMEOUT);

//    if (status == DVP_STATUS_OK) {
//        if (m_threadMutex.tryLock()) {

//            //帧计数
//            dvpGetFrameCount(m_handle, &FrameCount);
//            int strFrameCount = FrameCount.uFrameCount;
//            //单通道图像宽度
//            FrameWidth = m_pFrame.iWidth;
//            //单通道图像高度
//            if (strFrameCount % 20 == 1) {
//                FrameHeight = m_pFrame.iHeight / m_FieldCount;
//            } else {
//                FrameHeight = m_pFrame.iHeight / m_FieldCount + ImageOffset;
//            }

//            qDebug() << "strFrameCount " << strFrameCount << pBuffer;

//            if (m_pFrame.format == FORMAT_BGR24) {

//                DWORD A = GetCurrentTime();
//                const int ImageLineSize = WIDTH_BYTES(24, m_pFrame.iWidth);
//                const int ImageSize = ImageLineSize * m_pFrame.iHeight / m_FieldCount;
//                byte* Src_Buffer = new byte[ImageLineSize * m_pFrame.iHeight];
//                Src_Buffer = (byte*)pBuffer;

//                byte** Dest_Buffer = new byte*[m_FieldCount];
//                for (int i = 0; i < m_FieldCount; i++) {
//                    Dest_Buffer[i] = new byte[ImageSize];
//                }
//                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
//                    for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
//                        memcpy(Dest_Buffer[lightnum] + HeightCount * ImageLineSize, Src_Buffer + (m_FieldCount * HeightCount + lightnum) * ImageLineSize, ImageLineSize);
//                    }
//                }

//                DWORD F = GetCurrentTime();
//                DWORD G = F - A;

//                for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
//                    ImageList[lightnum] = QImage((uchar*)Dest_Buffer[lightnum], m_pFrame.iWidth, m_pFrame.iHeight / m_FieldCount, QImage::Format_RGB888);
//                }

//                //测试时需要增加释放资源指针代码

//                qDebug() << G;
//            } else {
//                DWORD A = GetCurrentTime();
//                const int ImageLineSize = WIDTH_BYTES(8, m_pFrame.iWidth);
//                const int ImageSize = ImageLineSize * m_pFrame.iHeight / m_FieldCount;
//                byte* Src_Buffer = new byte[ImageLineSize * m_pFrame.iHeight];
//                Src_Buffer = (byte*)pBuffer;

//                byte** Dest_Buffer = new byte*[m_FieldCount];
//                for (int i = 0; i < m_FieldCount; i++) {
//                    Dest_Buffer[i] = new byte[ImageSize];
//                }
//                for (int HeightCount = 0; HeightCount < m_pFrame.iHeight / m_FieldCount; HeightCount++) {
//                    for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
//                        memcpy(Dest_Buffer[lightnum] + HeightCount * ImageLineSize, Src_Buffer + (m_FieldCount * HeightCount + lightnum) * ImageLineSize, ImageLineSize);
//                    }
//                }

//                DWORD F = GetCurrentTime();
//                DWORD G = F - A;

//                for (int lightnum = 0; lightnum < m_FieldCount; lightnum++) {
//                    ImageList[lightnum] = QImage((uchar*)Dest_Buffer[lightnum], m_pFrame.iWidth, m_pFrame.iHeight / m_FieldCount, QImage::Format_Grayscale8);
//                }

//                qDebug() << G;
//            }

//            m_ShowImage = ImageList[0];
//            emit sig_DeliverImage(ImageList); //此处可以将图片传递出去,扔到算法接口
//            m_threadMutex.unlock();
//        }

//        emit signalDisplay();
//    }
//}
