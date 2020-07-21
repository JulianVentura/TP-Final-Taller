#ifndef __POCION_H__
#define __POCION_H__
#include "Item.h"
class Personaje;
class Pocion : public Item{
    private:
    unsigned int curacionVida;
    unsigned int curacionMana;

    public:
    Pocion(unsigned int curacionVida, 
           unsigned int curacionMana, 
           std::string unId,
           uint16_t idTCP,
           unsigned int unPrecio);
    /*
    Utiliza la pocion, curando al personaje segun los niveles de curacion de la misma.
    Elimina la pocion de la posicion pos del inventario del personaje.
    */
    void utilizar(Personaje *personaje, unsigned int pos) override;
    /*
    No realiza accion alguna
    */
    void desequipar(Personaje *personaje, unsigned int pos) override;
};


#endif
