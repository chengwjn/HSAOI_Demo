#ifndef PARAMCOMM_H
#define PARAMCOMM_H

#include "TcpPackComm.h"
#include <QMutex>
#include <QtCore>
#include <QtGlobal>
#include <QtEndian>

#define HTONL qToBigEndian //htonl
#define HTONS qToBigEndian //htons
#define NTOHL qFromBigEndian //ntohl
#define NTOHS qFromBigEndian //ntohs

#define HEAD_LABEL_SC_1 0xeb
#define HEAD_LABEL_SC_2 0x90

#define OP_SUCCESS	0x01
#define OP_FAIL		0x02

typedef struct _SC_PackHead
{
    unsigned char  packType1;  //包类型；0xeb 0x90；
    unsigned char  packType2;
    unsigned char  opCode1;   //操作码1
    unsigned char  opCode2;   //操作码2
    unsigned short custom1;   //自定义1
    unsigned short custom2;   //自定义2
    unsigned short custom3;   //自定义3
    unsigned short custom4;   //自定义4
    unsigned int  dataLength;//数据长度
}SC_PackHead;

const int RECV_BUF_LENGTH = 2048;
const int PACK_BUF_LENGTH = 4096;
const int SlEEP_MSEC = 20;
const int LOOP_COUNT = 100;

class ParamComm : public TcpPackComm
{
    Q_OBJECT
public:
    ParamComm();

    int WriteCommand(const char *send_data, int send_len, char * recv_data, int &recv_len);

protected:
    void ProcessData(const char * data, qint64 len);

private:
    enum { BUFFERSIZE_MAX = 8192 };

    char    m_recvBuf_t[BUFFERSIZE_MAX*2];
    int     m_recvLen_t;
    QMutex  m_lockRecvBuf_t;

    QMutex  m_lockOp;

    int     ReadRecvBuf(char * data, int max_size);
    int     GetAndAnalyseData(char * pOutBuf, int& recvLength);

    char m_pAlysBuf[RECV_BUF_LENGTH];//接收缓存
    char m_pPackBuf[PACK_BUF_LENGTH];//粘包缓存
    int m_nAlysOffset;

};

#endif // PARAMCOMM_H
