/*******************************************
    @ClassName   : ImageCombine
    @Description : 图像拼接模块，包括拆分功能
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-06-30
********************************************/
#ifndef IMAGECOMBINE_H
#define IMAGECOMBINE_H

#include <QObject>

class ImageCombine : public QObject
{
    Q_OBJECT
public:
    explicit ImageCombine(QObject *parent = nullptr);

signals:

};

#endif // IMAGECOMBINE_H
