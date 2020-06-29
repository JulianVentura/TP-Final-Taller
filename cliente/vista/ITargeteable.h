#ifndef ITARGETEABLE_H
#define ITARGETEABLE_H

#include "IDimensionable.h"

class ITargeteable: public IDimensionable {
public:
    virtual int getX();
    virtual int getY();
protected:
    int x;
    int y;
};

#endif
