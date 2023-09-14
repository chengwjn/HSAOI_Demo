#include "ParamComm.h"

ParamComm::ParamComm() : TcpPackComm(BUFFERSIZE_MAX, BUFFERSIZE_MAX, 0)
    , m_recvLen_t(0)
    , m_nAlysOffset(0)
{
    memset(m_recvBuf_t, 0, sizeof(m_recvBuf_t));
    memset(m_pAlysBuf, 0, sizeof(m_pAlysBuf)); //接收缓存
    memset(m_pPackBuf, 0, sizeof(m_pPackBuf)); //粘包缓存

    unsigned char header_buff[]={0xeb,0x90};
    SetHeaderByte((char *)(header_buff),2,16);
}

int ParamComm::WriteCommand(const char *send_data, int send_len, char * recv_data, int &recv_len)
{
    m_lockRecvBuf_t.lock();
    m_recvLen_t = 0;
    m_lockRecvBuf_t.unlock();

    m_lockOp.lock();

    if (!WriteData(send_data, send_len))
    {
        m_lockOp.unlock();
        return -1;
    }

    if ( GetAndAnalyseData(recv_data, recv_len) < 0)
    {
        m_lockOp.unlock();
        return -2;
    }
    m_lockOp.unlock();
    return 1;
}

void ParamComm::ProcessData(const char *data, qint64 len)
{
    m_lockRecvBuf_t.lock();
    memcpy(m_recvBuf_t+m_recvLen_t, data, len);
    m_recvLen_t += len;
    m_lockRecvBuf_t.unlock();
}

int ParamComm::ReadRecvBuf(char * data, int max_size)
{
    int copy_len = 0;
    m_lockRecvBuf_t.lock();
    copy_len = m_recvLen_t < max_size ? m_recvLen_t : max_size;
    memcpy(data, m_recvBuf_t, copy_len);
    m_recvLen_t -= copy_len;
    m_lockRecvBuf_t.unlock();
    return copy_len;
}

int ParamComm::GetAndAnalyseData(char * pOutBuf, int& recvLength)
{
    int nRet = -1;

    int l_count = 0;
    do
    {
        int nRecv = ReadRecvBuf(m_pAlysBuf, RECV_BUF_LENGTH);
        if (nRecv > 0)
        {
            memcpy(m_pPackBuf+m_nAlysOffset,m_pAlysBuf,nRecv);
            m_nAlysOffset = m_nAlysOffset + nRecv;

            if (m_nAlysOffset >= (int)sizeof(SC_PackHead))
            {
                int indexStart = -1;
                for (int i = 0; i < m_nAlysOffset-1; ++i)
                {
                    if ( (unsigned char)m_pAlysBuf[i] == (unsigned char)HEAD_LABEL_SC_1 && (unsigned char)m_pAlysBuf[i+1] == (unsigned char)HEAD_LABEL_SC_2)
                    {
                        indexStart = i;
                        break;
                    }
                }

                if (indexStart < 0)
                {
                    m_nAlysOffset = 0;
                    indexStart = 0;
                    memset(m_pPackBuf, 0, sizeof(m_pPackBuf));
                    QThread::msleep(SlEEP_MSEC);
                    continue;
                }
                else if (indexStart > 0)
                {
                    m_nAlysOffset -= indexStart;
                    memcpy(m_pPackBuf, m_pPackBuf+indexStart, m_nAlysOffset);
                    indexStart = 0;
                }

                SC_PackHead * pHead = (SC_PackHead *)m_pPackBuf;
                int data_len = NTOHL((unsigned int)(pHead->dataLength));
                data_len = data_len + sizeof(SC_PackHead);

                if (m_nAlysOffset >= data_len)
                {
                    memcpy(pOutBuf, m_pPackBuf, data_len);
                    recvLength = data_len;
                    m_nAlysOffset -= data_len;
                    memcpy(m_pPackBuf, m_pPackBuf+data_len, m_nAlysOffset);
                    nRet = 1;
                    break;
                }
                else
                    QThread::msleep(SlEEP_MSEC);
            }
            else
                QThread::msleep(SlEEP_MSEC);
        }
        else
        {
            QThread::msleep(SlEEP_MSEC);
        }
    }while(l_count++ < LOOP_COUNT);
    return  nRet;
}
