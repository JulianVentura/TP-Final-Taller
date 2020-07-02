#ifndef __ORO_H__
#define __ORO_H__
#include "Item.h"

class Oro : public Item{
    private:
    unsigned int cantidadOro;
    
    public:
    Oro(unsigned int cantOro);
    void utilizar(Personaje *personaje, unsigned int pos) override;
};

#endif
