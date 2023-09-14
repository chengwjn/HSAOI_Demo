#ifndef TCP_H
#define TCP_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

class Tcp : public QObject {
    Q_OBJECT
public:
    explicit Tcp(qint64 bufLength = DEFAULT_BUFF_LENGTH, QObject* parent = nullptr);
    ~Tcp();

    void ConnectToServer();
    void ConnectToServer(const char* IP, int port);
    void Close(bool bManClosed = true);
    bool WriteData(const char* data, int len);
    bool WriteData(const QByteArray& data);
    void InitSock(const char* IP, int port);
    void SetAutoConnect(bool bAuto) { m_bAutoReConnect = bAuto; }
    bool IsOpen()
    {
        if (!m_pSock)
            return false;
        return m_bConnFlag;
    }

private:
    void ConstructorInit();

public:
    enum { DEFAULT_BUFF_LENGTH = 1600 };

protected:
    virtual void ParseData(const char*, qint64) { }

protected:
    QHostAddress m_addr;
    int m_nPort;

    QTcpSocket* m_pSock;
    QThread* m_pThread;

    qint64 MaxBuffLength;
    char* ReadBuff;

private:
    bool m_bManClosed;
    bool m_bConnFlag;
    bool m_bReconnectFlag;
    bool m_bAutoReConnect;

signals:
    void sig_connect();
    void sig_disconnect();
    void sig_writeData(const char* data, int len);
    void sig_writeData(QByteArray data);

protected:
    virtual void vThreadStarted() { }

public slots:
    void slot_threadStarted();

private slots:
    void slot_connect();
    void slot_disconnect();
    void slot_writeData(QByteArray data);
    void OnReadyRead();
    void OnSockStateChanged(QAbstractSocket::SocketState);
};

#endif // TCP_H
