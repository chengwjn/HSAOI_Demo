#include "Tcp.h"
#include <QTimer>

Tcp::Tcp(qint64 bufLength, QObject *parent) : QObject(parent)
    , MaxBuffLength(bufLength)
    , m_bManClosed(false)
    , m_bConnFlag(false)
    , m_bReconnectFlag(false)
    , m_bAutoReConnect(true)
{
    ConstructorInit();
}

void Tcp::ConstructorInit()
{
    ReadBuff = new char[MaxBuffLength];

    m_pSock = new QTcpSocket();
    m_pThread = new QThread();
    m_pSock->moveToThread(m_pThread);
    this->moveToThread(m_pThread);

    connect(this, SIGNAL(sig_connect()), this, SLOT(slot_connect()), Qt::QueuedConnection);
    connect( this, SIGNAL(sig_disconnect()), this, SLOT(slot_disconnect()), Qt::QueuedConnection);
    connect(m_pSock, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
    connect(m_pSock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this , SLOT(OnSockStateChanged(QAbstractSocket::SocketState)));
    connect(this, SIGNAL(sig_writeData(QByteArray)), this, SLOT(slot_writeData(QByteArray)));
    connect(m_pThread, SIGNAL(started()), this, SLOT(slot_threadStarted()));

    m_pThread->start();
}

Tcp::~Tcp()
{
    m_bManClosed = true;
    if(m_pSock)
    {
        if(m_pSock->isOpen() && m_bConnFlag)
        {
            m_pSock->disconnectFromHost();
            m_bConnFlag = false;
        }
    }
    m_pThread->exit(0);
    m_pThread->wait(2000);
    m_pThread->deleteLater();
    m_pSock->deleteLater();
    delete [] ReadBuff;
    ReadBuff = NULL;
}

void Tcp::slot_threadStarted()
{
    vThreadStarted();
}

void Tcp::InitSock(const char * ip, int port)
{
    QString strip( ip );
    m_addr.setAddress( strip );
    m_nPort = port;
}

void Tcp::ConnectToServer()
{
    emit sig_connect();
}

void Tcp::ConnectToServer(const char * ip, int port)
{
    InitSock(ip, port);
    ConnectToServer();
}

void Tcp::Close(bool bManClosed)
{
    m_bManClosed = bManClosed;
    emit sig_disconnect();
}

bool Tcp::WriteData( const char *data, int len )
{
    if( NULL == data || len <= 0 )
        return false;

    if (!m_pSock)
        return false;

    if (!m_bConnFlag)
        return false;

    QByteArray s_data(data, len);
    emit sig_writeData(s_data);

    return true;
}

bool Tcp::WriteData( const QByteArray & data )
{
    if( data.length() <= 0 )
        return false;

    if (!m_pSock)
        return false;

    if (!m_bConnFlag)
        return false;

    emit sig_writeData(data);

    return true;
}

void Tcp::slot_connect()
{
    if (m_pSock)
    {
        m_pSock->connectToHost( m_addr, m_nPort );
    }
}

void Tcp::slot_disconnect()
{
    if (m_pSock)
    {
        if (m_pSock->isOpen() && m_bConnFlag)
        {
            m_pSock->disconnectFromHost();
            m_bConnFlag = false;
        }
    }
}

void Tcp::slot_writeData( QByteArray data )
{
    if( data.length() <= 0 )
        return ;
    if (!m_pSock)
        return ;

    if (!m_bConnFlag)
        return;

    qint64 ret = m_pSock->write(data);

    if( ret > 0 )
    {
        if (m_nPort == 7002)
        {
            //GlobalLogger.addLog("write heart beat request to net");

        }
    }
}

void Tcp::OnReadyRead()
{
//    QByteArray buffer;
//    buffer = m_pSock->readAll();
//    qDebug() << buffer;
    qint64 len = m_pSock->read( ReadBuff, MaxBuffLength );
    if( len <= 0 )
        return;
    else
        ParseData( ReadBuff, len );

}

void Tcp::OnSockStateChanged(QAbstractSocket::SocketState state)
{
    {
        qDebug() << "port" << m_nPort << ", state changed" << state;
    }

    if (QAbstractSocket::UnconnectedState == state)
    {
        m_bConnFlag = false;
        if (m_bAutoReConnect && !m_bManClosed)
        {
            //if (!m_bReConnectFlag)
            {
                //m_bReConnectFlag = true;
                //重连...
                QTimer::singleShot(10, this, SLOT(slot_connect()));

                {
                    qDebug() << "port" << m_nPort << ", OnSockStateChanged 0 and reconnect!!!";
                }
            }
        }
    }
    else if (QAbstractSocket::ConnectedState == state)
    {
        m_bManClosed = false;
        m_bConnFlag = true;
        m_bReconnectFlag = false;
        {
            qDebug() << "port" << m_nPort << ", connected";
        }
    }
    else
    {
        //do nothing
    }
}
