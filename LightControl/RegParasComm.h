#ifndef REGPARASCOMM_H
#define REGPARASCOMM_H

#include <QObject>
#include "ParamComm.h"
#include <QMutex>

class RegParasComm : public ParamComm
{
    Q_OBJECT
public:
    explicit RegParasComm();
    ~RegParasComm(void);

    int SetRegs(unsigned short addr_s, unsigned short addr_e, unsigned int *data);
    int GetRegs(unsigned short addr_s, unsigned short addr_e, unsigned int *data);
    int SaveRegs();

};

#endif // REGPARASCOMM_H
