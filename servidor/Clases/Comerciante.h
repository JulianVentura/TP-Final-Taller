#ifndef __COMERCIANTE_H__
#define __COMERCIANTE_H__

#include "Entidad.h"
#include <vector>

class Personaje;
class Item;
class Comerciante : public Entidad{
    protected:
    std::vector<Item*> items;
    Item* itemNulo;
    
    public:
    Comerciante(float x, float y);
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
    Permite realizar una interaccion entre el Comerciante (this) y la entidad de estado Estado que comienza
    la interaccion.
    Utilizando double-dispatch se delegara en estado el pedido a listar, que es el que corresponde al Comerciante.
    */
    void interactuar(Estado *estado, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de compra.
    */
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    /*
    Permite al Personaje comprar un item almacenado en la posicion pos de la tienda.
    Si el oro del personaje no es suficiente la compra no se realizara y se le enviara un mensaje descriptivo.
    Si el oro es suficiente la compra se realizara y el oro sera disminuido segun el precio del item.
    Todo item que figure en la tienda tiene stock ilimitado, por lo tanto puede ser comprado infinitas veces.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item comprado.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    */
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de venta.
    */
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Permite al Personaje vender el item almacenado en la posicion pos del inventario.
    El Comerciante tiene oro infinito, por lo tanto puede realizar todas las compras solicitadas.
    Una vez vendido el item el mismo desaparecera del inventario del Personaje y su oro se incrementara segun
    el valor de dicho item.
    Los items vendidos al Comerciante no podran ser obtenidos nuevamente, los mismos no figuraran en stock.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item obtenido.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    */
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    /*
    Se le enviara al cliente la señal de actualizacion de contenedor para que pueda observar
    el contenido de la tienda.
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
    Devuelve una serializacion de los items en stock de la tienda.
    */
    SerializacionContenedor serializarTienda();
    ~Comerciante() override;
};

#endif