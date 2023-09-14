#ifndef TCPPACKCOMM_H
#define TCPPACKCOMM_H

#include "Tcp.h"

#define S_T_DATA_LEN_BYTE 2
#define L_T_DATA_LEN_BYTE 4

class TcpPackComm : public Tcp
{
    Q_OBJECT
public:
    explicit TcpPackComm(qint64 parseBufLen = DEFAULT_BUFF_LENGTH, qint64 bufLength = DEFAULT_BUFF_LENGTH, QObject *parent = nullptr);
    ~TcpPackComm();

    void SetHeaderByte(const char* _header,int tag_len,int h_len,int dataLenMode = 0);

protected:
    virtual void ParseData(const char *, qint64);
    virtual void ProcessData(const char *data, qint64 len){}
    virtual void ResetStatus();

protected:
    char * m_pRecvDataBuff;
    qint64 m_nMaxDataBuffLength;
    qint64 m_nCurDataOffset;

    char * m_pHeaderTagBuff;
    int m_nHeaderLen;
    int m_nHeaderTagLen;

    int m_dataLenMode;
};

#endif // TCPPACKCOMM_H
