#ifndef __BOLSA_DE_ITEMS_H__
#define __BOLSA_DE_ITEMS_H__

#include "Entidad.h"
#include <vector>
#include <atomic>
class Personaje;
class Item;
class BolsaDeItems : public Entidad{
    private:
    static std::atomic<uint32_t> contadorInstancias;
    std::vector<Item*> items;
    Item* itemNulo;
    uint32_t elementos;
    bool bolsaVacia;
    public:
    BolsaDeItems(Posicion posicion, std::vector<Item*> items);
    BolsaDeItems(Posicion posicion, Item *item);
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
    Permite realizar una interaccion entre la BolsaDeItems (this) y la entidad de estado Estado que comienza
    la interaccion.
    Utilizando double-dispatch se delegara en estado el pedido a listar, que es el que corresponde al BolsaDeItems.
    */
    void interactuar(Estado *estado, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de compra.
    */
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    /*
    Permite al Personaje obtener un item en la posicion pos de la bolsa, el cual sera almacenado
    en su inventario.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item almacenado.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    Si tras la compra la bolsa queda sin items su estado pasara a vacio, permitiendo ser eliminada del mapa.
    */
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    /*
    Se le enviara un mensaje al cliente indicandole que no se pueden almacenar items en una BolsaDeItems
    */
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    /*
    Se le enviara al cliente la señal de actualizacion de contenedor para que pueda observar
    el contenido de la BolsaDeItems.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se efectuara la accion.
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

    /*
    Permite saber si la bolsa esta vacia. En tal caso sera eliminada del mapa al que pertenece.
    */
    bool haFinalizado() override;
    /*
    Devuelve una serializacion de los items contenidos en la bolsa.
    */
    SerializacionContenedor serializarBolsa();
    ~BolsaDeItems() override;
};

#endif