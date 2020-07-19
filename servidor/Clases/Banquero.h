#ifndef __BANQUERO_H__
#define __BANQUERO_H__

#include "Item.h"
#include "Entidad.h"
#include <vector>

class Personaje;
class Item;
class Banquero : public Entidad{
    private:
    uint32_t limiteTransaccion;
    float fraccionTransaccion;
    Item* itemNulo;
    public:
    Banquero(float x, float y);
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
    Permite realizar una interaccion entre el Banquero (this) y la entidad de estado Estado que comienza
    la interaccion.
    Utilizando double-dispatch se delegara en estado el pedido a listar, que es el que corresponde al Banquero.
    */
    void interactuar(Estado *estado, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de compra.
    */
    void comprar(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Permite al Personaje obtener un item en la posicion pos del almacen, el cual sera almacenado
    en su inventario.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item almacenado.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    */
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de venta.
    */
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Permite al Personaje almacenar un item en la posicion pos del inventario, el cual sera almacenado
    en el almacen.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item obtenido.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    */
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    /*
    Se le enviara al cliente la señal de actualizacion de contenedor para que pueda observar
    el contenido del almacen.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se efectuara la accion.
    */
    void listar(Personaje *personaje, Cliente *cliente) override;
    /*
    Utilizando double-dispatch se delega en el estado que se pasa por parametro el pedido de transaccion.
    */
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;
    /*
    Permite al Personaje depositar o retirar oro del almacen segun el valor de esDeposito.
    Las transacciones se realizaran progresivamente en base a la fraccion del monto almacenado que se quiere
    mover.
    Una vez superado el monto limite la transaccion se realizara en montos constantes hasta agotar la cantidad de oro.
    Tras finalizar se le enviara al cliente la señal de actualizacion de contenedor e inventario.
    Ademas se le enviara al cliente un mensaje descriptivo del item almacenado.
    En caso de que la distancia con el personaje sea mayor a la distancia de interaccion no se realizara
    intercambio.
    */
    void transaccion(bool esDeposito, Personaje *personaje, Cliente *cliente);
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
    Devuelve una serializacion de los items y oro contenidos en el almacen
    */
    SerializacionContenedor serializarAlmacen(const std::vector<Item*> &almacen, uint32_t oro);
    ~Banquero() override;
};

#endif