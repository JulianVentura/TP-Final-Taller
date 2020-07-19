#ifndef __PORTAL_H__
#define __PORTAL_H__
#include "Entidad.h"

class Personaje;
class Portal : public Entidad{
    public:
    Portal(float x, float y, const std::string &id, const std::string &idMapaATeletransportar);
    std::string idMapa;
    //Ataques
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    std::string atacar(Personaje *objetivo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    std::string atacar(Criatura *objetivo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void serAtacadoPor(Personaje *atacante) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void serAtacadoPor(Criatura *atacante) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    std::string recibirDanio(int danio, Entidad *atacante) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void recibirCuracion(unsigned int curacion, Entidad *lanzador) override;
    //Comercio
    /*
    Le indicara al cliente pasado por parametro que debera realizar un cambio de mapa al mapa que es almacenado
    como atributo en this.
    La interaccion se efectua sin importar el estado.
    La interaccion no se efectua si la distancia entre this y la entidad es mayor a la distancia de interaccion.
    */
    void interactuar(Estado *estado, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void listar(Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;
    //Estado
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void actualizarEstado(double tiempo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    std::string dropearItems(Entidad *atacante) override;
    ~Portal() override;
};

#endif