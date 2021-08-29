#ifndef TORREABSTRATA_H
#define TORREABSTRATA_H
#include <disco.h>

class torreAbstrata{

public:
    virtual void push(Disco *d)=0;
    virtual void pop()=0;
    virtual bool empty()=0;
    virtual Disco*getDiscoArrastavel()=0;
    virtual void discosBuilder(int size)=0;
    virtual Disco *getLastDisco()=0;
    virtual void moveDiscos()=0;
    virtual int getSizeAtual()=0;
    virtual void resetTower()=0;
};

#endif // TORREABSTRATA_H
