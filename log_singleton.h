/*******************************************
    @ClassName   : log_singleton
    @Description : 日志类
    @Creator     : Huxujie
    @Author      : Huxujie
    @Date        : 2023-07-25
********************************************/
#ifndef JIANBO_LOG_SINGLETON_H
#define JIANBO_LOG_SINGLETON_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QString>
enum Log_Level {
    General,
    Urgent,
    Error
};
class log_singleton {
public:
    static void Write_Log(const QString& Log_message, Log_Level Log_level);

    static void Write_csv(QDateTime time, int id, double edge1, double edge2, double ltrb,
        double rtlb, QString q, int num, double x,
        double y, QString type, double size);

private:
    static void Open_Log_File(const QString& filename);

    static void Close_Log_File();

    static QString Get_Log_Filename(const QString& filename);

private:
    static log_singleton* instance;

    static QMutex mutex;

    static QFile Log_File;
};

#endif // JIANBO_LOG_SINGLETON_H
