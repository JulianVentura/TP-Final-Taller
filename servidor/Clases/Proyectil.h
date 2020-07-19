#ifndef __PROYECTIL_H__
#define __PROYECTIL_H__
#include "Entidad.h"
#include <atomic>

class Proyectil : public Entidad{
    private:
    Posicion destino;
    bool finalizado;
    bool haLlegadoADestino;
    double tiempoTranscurrido;
    double tiempoDespawn;
    static std::atomic<int> contador;
    
    public:
    Proyectil(std::string id, Posicion origen, Posicion destino);
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
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
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
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void curar(Personaje *personaje, Cliente *cliente);
    //Estado
    /*
    Lleva la logica de movimiento del proyectil desde su origen hacia la posicion destino.
    Tras llegar a la posicion destino y cumplirse el tiempo de despawn se indicara como finalizado y
    podra ser descargado del mapa.
    */
    void actualizarEstado(double tiempo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    std::string dropearItems(Entidad *atacante) override;
    /*
    Indica si puede ser descargado del mapa.
    */
    bool haFinalizado() override;

    ~Proyectil() override;
};


#endif
