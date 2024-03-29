#ifndef IOBSTRUIBLE_H
#define IOBSTRUIBLE_H
#include "IRendereable.h"
#include "ITargeteable.h"

class IObstruible: public IRendereable, public ITargeteable {
public:
    int getX() override;
    int getY() override;
    void getFrontera(SDL_Rect& frontera);
    static bool comparar(IObstruible* obstruible,  IObstruible* otro);
};

#endif
