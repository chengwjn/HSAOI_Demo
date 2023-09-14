/*
 * 使用代码 log_singleton *log=log_singleton::Get_Instance(); 创建一个实例
 *
 * 在需要输出普通日志的地方，使用代码 log->Write_Log("此处替换为输出的日志内容",log_singleton::General); 输出普通日志
 *
 * 在需要输出紧急日志的地方，使用代码 log->Write_Log("此处替换为输出的日志内容",log_singleton::Urgent); 输出紧急日志
 *
 * 在需要输出错误日志的地方，使用代码 log->Write_Log("此处替换为输出的日志内容",log_singleton::Error); 输出错误日志
*/

#include "log_singleton.h"

log_singleton* log_singleton::instance = nullptr;

QMutex log_singleton::mutex;

QFile log_singleton::Log_File;

QString log_singleton::Get_Log_Filename(const QString& filename)
{
    QDateTime current_datetime = QDateTime::currentDateTime();

    QString date_string = current_datetime.toString("yyyyMMdd");

    QString time_string = current_datetime.toString("hh");

    //    QString Log_filename = "D:/Jianbo_Log/"+date_string + "_" + time_string + filename;

    QString Log_filename = "Log/" + date_string + "_" + time_string + filename;

    return Log_filename;
}

void log_singleton::Open_Log_File(const QString& filename)
{
    Close_Log_File();

    Log_File.setFileName(filename);

    Log_File.open(QIODevice::Append | QIODevice::Text);
}

void log_singleton::Close_Log_File()
{
    if (Log_File.isOpen()) {
        Log_File.close();
    }
}

void log_singleton::Write_Log(const QString& Log_message, Log_Level Log_level)
{
    QString Log_Filename;

    switch (Log_level) {
    case General:
        Log_Filename = Get_Log_Filename("_General.log");
        break;
    case Urgent:
        Log_Filename = Get_Log_Filename("_Urgent.log");
        break;
    case Error:
        Log_Filename = Get_Log_Filename("_Error.log");
        break;
    default:
        Log_Filename = Get_Log_Filename("_General.log");
        break;
    }

    {
        QMutexLocker mutex_locker(&mutex);

        Open_Log_File(Log_Filename);

        if (Log_File.isOpen()) {
            QTextStream stream(&Log_File);
            stream << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss.zzz") << "] " << Log_message << endl;
            qDebug() << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss.zzz") << "] " << Log_message;
        }

        Close_Log_File();
    }
}

void log_singleton::Write_csv(QDateTime time, int id, double edge1, double edge2,
    double ltrb, double rtlb, QString q, int num, double x, double y, QString type, double size)
{
    QString Log_Filename;

    Log_Filename = Get_Log_Filename(".csv");

    {
        QMutexLocker mutex_locker(&mutex);

        Open_Log_File(Log_Filename);

        if (Log_File.isOpen()) {
            QTextStream stream(&Log_File);

            stream.setFieldAlignment(QTextStream::AlignCenter);

            if (Log_File.size() == 0) {
                stream << "Time,ID,Edge1,Edge2,Diagonal_LTRB,Diagonal_RTLB,Quality,Flows_Num,Flows_X,Flows_Y,Flows_Type,Flows_Size) "
                       << "\n";
            }

            stream << "\"" << time.toString("yyyy-MM-dd hh:mm:ss.zzz") << "\t"
                   << "\""
                   << ","
                   << "\"" << id << "\t"
                   << "\""
                   << ","
                   << "\"" << edge1 << "\t"
                   << "\""
                   << ","
                   << "\"" << edge2 << "\t"
                   << "\""
                   << ","
                   << "\"" << ltrb << "\t"
                   << "\""
                   << ","
                   << "\"" << rtlb << "\t"
                   << "\""
                   << ","
                   << "\"" << q << "\t"
                   << "\""
                   << ","
                   << "\"" << num << "\t"
                   << "\""
                   << ","
                   << "\"" << x << "\t"
                   << "\""
                   << ","
                   << "\"" << y << "\t"
                   << "\""
                   << ","
                   << "\"" << type << "\t"
                   << "\""
                   << ","
                   << "\"" << size << "\t"
                   << "\""
                   << "\n";
        }

        Close_Log_File();
    }
}
