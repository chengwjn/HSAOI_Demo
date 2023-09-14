#include "TcpPackComm.h"
#include <QtEndian>
#include "ElemMatch.h"

TcpPackComm::TcpPackComm(qint64 parseBufLen, qint64 bufLength, QObject *parent) : Tcp(bufLength, parent)
  , m_pRecvDataBuff(NULL)
  , m_nMaxDataBuffLength(parseBufLen)
  , m_nCurDataOffset(0)
  , m_pHeaderTagBuff(NULL)
  , m_nHeaderLen(0)
  , m_nHeaderTagLen(0),m_dataLenMode(0)
{
    m_pRecvDataBuff = new char[m_nMaxDataBuffLength];
}

TcpPackComm::~TcpPackComm()
{
    delete [] m_pRecvDataBuff;
    m_pRecvDataBuff = NULL;
}

void TcpPackComm::SetHeaderByte(const char* _header, int tag_len, int h_len, int dataLenMode)
{
    if(h_len <= 0)
        return;
    if(m_pHeaderTagBuff)
        delete []m_pHeaderTagBuff;
    m_pHeaderTagBuff = NULL;
    m_pHeaderTagBuff = new char[tag_len];
    memcpy(m_pHeaderTagBuff, _header, tag_len);
    m_nHeaderLen = h_len;
    m_nHeaderTagLen = tag_len;


    m_dataLenMode = dataLenMode;

    ResetStatus();
}

void TcpPackComm::ResetStatus()
{
    m_nCurDataOffset = 0;
}

void TcpPackComm::ParseData(const char *data, qint64 len)
{
    const char * l_pRecvData = data;
    qint64 l_recvLength = len;

    while(l_recvLength > 0)
    {
        qint64 t_left_buff_len = m_nMaxDataBuffLength - m_nCurDataOffset;
        qint64 t_copy_len = l_recvLength < t_left_buff_len ? l_recvLength : t_left_buff_len;
        memcpy(m_pRecvDataBuff+m_nCurDataOffset, l_pRecvData, t_copy_len);
        l_pRecvData += t_copy_len;
        l_recvLength -= t_copy_len;
        m_nCurDataOffset += t_copy_len;

        while (m_nCurDataOffset >= m_nHeaderLen)
        {
            int pos =  KMPElemMatching(m_pRecvDataBuff, m_nCurDataOffset, m_pHeaderTagBuff, m_nHeaderTagLen);
            if (pos >= 0)
            {
                if (pos > 0)
                {
                    memmove(m_pRecvDataBuff, m_pRecvDataBuff+pos, m_nCurDataOffset - pos);
                    m_nCurDataOffset -= pos;
                }
                if (m_nCurDataOffset < m_nHeaderLen)
                    break;
                    //continue;

                unsigned int msg_len = 0;
                if(m_dataLenMode == 0)
                {
                    msg_len = *((unsigned int*)(m_pRecvDataBuff + m_nHeaderLen - L_T_DATA_LEN_BYTE));
                    msg_len = qFromBigEndian(msg_len);
                }
                else
                {
                    unsigned short t_len = *((unsigned short*)(m_pRecvDataBuff + m_nHeaderLen - S_T_DATA_LEN_BYTE));
                    t_len = qFromBigEndian(t_len);
                    msg_len = t_len;
                }

                msg_len += m_nHeaderLen;
                if (msg_len <= m_nMaxDataBuffLength)
                {
                    if (m_nCurDataOffset >= msg_len )
                    {
                        ProcessData(m_pRecvDataBuff, msg_len);
                        memmove(m_pRecvDataBuff, m_pRecvDataBuff+msg_len, m_nCurDataOffset-msg_len);
                        m_nCurDataOffset -= msg_len;
                    }
                    else
                        break;
                }
                else
                {
                    qDebug()<<"Msg Len Exceed Max Size";
                    m_nCurDataOffset = 0;
                }
            }
            else
            {
                qDebug()<<"can't find head remove data";
                memmove(m_pRecvDataBuff, m_pRecvDataBuff+m_nCurDataOffset - m_nHeaderLen +1, m_nHeaderLen -1 );
                m_nCurDataOffset = m_nHeaderLen -1;
            }
        }
    }
}
