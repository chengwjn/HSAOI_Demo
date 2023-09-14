#include "RegParasComm.h"

RegParasComm::RegParasComm() : ParamComm()
{
}

RegParasComm::~RegParasComm()
{
    ;
}

int RegParasComm::SetRegs(unsigned short addr_s, unsigned short addr_e, unsigned int *data)
{
    char sendData[8192] = {0};
    uint i;
    SC_PackHead * pSendHead = (SC_PackHead *)sendData;
    pSendHead->packType1 = HEAD_LABEL_SC_1;
    pSendHead->packType2 = HEAD_LABEL_SC_2;
    pSendHead->opCode1 = 0x02;

    pSendHead->custom1 = HTONS(addr_s);
    pSendHead->custom2 = HTONS(addr_e);
    if((addr_e < addr_s) || (addr_s + 2000 < addr_e))
        return  -10;

    unsigned int data_len = addr_e - addr_s + 4;
    pSendHead->dataLength = HTONL(data_len);
    unsigned int * pSendParam = (unsigned int *)(sendData + sizeof (SC_PackHead));
    for(i = 0; i < data_len; i++)
        *(pSendParam + i) = HTONL(data[i]);

    char recvRegData[1600] = {0};
    int recvLength = 0;
    int ret = 0;
    ret = WriteCommand((char *)sendData, sizeof (SC_PackHead) + HTONL(pSendHead->dataLength), recvRegData, recvLength);
    if(ret < 0)
        return -1;  //超时
    SC_PackHead *pHead = (SC_PackHead *) recvRegData;
    if((pHead->opCode1 == 0x09) && (pHead->opCode2 == 0x01))
    {
        if(0x01 == NTOHS(pHead->custom1))
        {
            return 1;   //修改成功
        }

        if(0x02 == NTOHS(pHead->custom1))
            return 0;   //修改失败
    }
    else
        return -2;  //操作码无效

    return 1;
}

int RegParasComm::GetRegs(unsigned short addr_s, unsigned short addr_e, unsigned int *data)
{
    uint i;
    char sendData[1600] = {0};
    SC_PackHead * pSendHead = (SC_PackHead *)sendData;
    pSendHead->packType1 = HEAD_LABEL_SC_1;
    pSendHead->packType2 = HEAD_LABEL_SC_2;
    pSendHead->opCode1 = 0x05;

    pSendHead->custom1 = HTONS(addr_s);
    pSendHead->custom2 = HTONS(addr_e);
    if((addr_e < addr_s) || (addr_s + 2000) < addr_e)
        return -10;

    char recvRegData[8192] = {0};
    int recvLength = 0;
    int ret = 0;
    ret = WriteCommand((char *)sendData, sizeof (SC_PackHead), recvRegData, recvLength);
    if(ret < 0)
        return  -1;     //超时
    SC_PackHead * pHead = (SC_PackHead *)recvRegData;
    unsigned int data_len = (addr_e - addr_s) / 4 + 1;
    if(pHead->opCode1 == 0x0D)
    {
        unsigned int * pSendParam = (unsigned int *)(recvRegData + sizeof (SC_PackHead));
        for(i = 0; i < data_len; i++)
            data[i] = HTONL(*(pSendParam + i));
        return 1;   //读取成功
    }
    else
        return -2;  //操作码无效

    return 1;
}

int RegParasComm::SaveRegs()
{
    char sendData[1600] = {0};
    SC_PackHead * pSendHead = (SC_PackHead *)sendData;
    pSendHead->packType1 = HEAD_LABEL_SC_1;
    pSendHead->packType2 = HEAD_LABEL_SC_2;
    pSendHead->opCode1 = 0x07;
    pSendHead->dataLength = HTONL(0);

    char recvRegData[8192] = {0};
    int recvLength = 0;
    int ret = 0;
    ret = WriteCommand((char *)sendData, sizeof(SC_PackHead), recvRegData, recvLength);
    if(ret < 0)
        return -1;  //超时
    SC_PackHead * pHead = (SC_PackHead *)recvRegData;
    if((pHead->opCode1 == 0x0a) && (pHead->opCode2 == 0x01))
    {
        if(0x01 == NTOHS(pHead->custom1))
            return 1;   //修改成功
        else if(0x02 == NTOHS(pHead->custom1))
            return 0;   //修改失败
    }
    else
        return -2;  //操作码无效

    return 1;
}
