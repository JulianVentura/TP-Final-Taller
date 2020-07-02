#ifndef __FABRICA_DE_ITEMS_H__
#define __FABRICA_DE_ITEMS_H__
#include <memory>
class Item;
//class Pocion;
class Arma;
class FabricaDeItems{
    public:
    FabricaDeItems();
    std::unique_ptr<Item> obtenerItemAleatorio();
    //std::unique_ptr<Pocion> obtenerPocionDeVida();
    //Armas
    std::unique_ptr<Arma> obtenerEspadaDeHierro();
};

#endif



/*

Cuando una criatura muere se llama a FabricaDeItems y se le pide un item random.
Esto podra ser:

- Armas
- Armaduras
- Escudos
- Cascos
- Pociones
- Oro

Por lo tanto no es necesario crear una Fabrica para cada cosa, es tan simple como hacer una FabricaDeItems.

FabricaDeItems::obtenerItemAleatorio(){
    Devuelve un item aleatorio.
}

Todo item tendra el metodo utilizar, esto permite variar cada item utilizando polimorfismo

virtual Item::utilizar(Personaje *objetivo) = 0;

Por ej:
Estilo double dispatch

Personaje::utilizar(std::string &id){
    Item *item = inventario.obtenerItem(id);
    item->utilizar();
}

Arma::utilizar(Personaje *objetivo){
    objetivo->equipar(this);
}

Armadura::utilizar(Personaje *objetivo){
    objetivo->equipar(this);
}

Pocion::utilizar(Personaje *objetivo){
    objetivo->curar(vidaACurar, manaACurar);
    personaje->consumir(this->id);
}

//Equipar un arma/armadura

Personaje::equipar(Arma *arma){
    if (armaEquipada){
        inventario.almacenar(armaEquipada);
        armaEquipada = nullptr;
    }
    armaEquipada = arma;
}


Cuando una entidad muere se le indicara al mapa que cargue una BolaDeItems, la cual es una lista de Item con una posicion
que permite ser recogida por el jugador y abierta.

Cuando una Criatura muere se llama a FabricaDeItems y se pide un Item aleatorio, el cual sera devuelto a traves
de un std::unique_ptr<> por movimiento, el cual se entregará a BolaDeItems.
Finalmente BolsaDeItems sera cargada en el inventario.

Cuando un jugador recoge la BolsaDeItems la misma sera descargada del mapa y cargada en el inventario del jugador.
El jugador podra hacer click sobre la BolsaDeItems para liberar el contenido.

- Si el espacio disponible en el inventario es menor a la cantidad de elementos de la bolsa entonces:
    * La bolsa debera abrirse parcialmente, solo cargando algunos items en el inventario. El resto queda en la Bolsa.
    * Cuando la bolsa se vacia completamente se elimina del inventario.
- Si el espacio disponible en el inventario es mayor o igual a la cantidad de elementos de la bolsa entonces:
    * La bolsa carga los items en el inventario y luego se elimina del mismo.

El inventario sera owner de los std::unique_ptr<Item> y cuando se requiera alguna accion sobre alguno de ellos
se devolvera el puntero que almacenan.
En una descarga del elemento se le indicara al inventario si se debe eliminar tal Item o si se debe mover hacia otro lugar
por ejemplo una BolsaDeDrop o un Almacen.
*/

/* PASOS PARA LA IMPLEMENTACION

Crear algunos Items, por ejemplo Arma
Crear la BolsaDeDrop.
Crear el Inventario.

*/


/*
Cambio de implementacion de BolsaDeItems

La implementacion sera similar a la de una Tienda.

La Bolsa seguira siendo recogida del mapa, lo unico que cambiara sera su comportamiento


*/


/*
Implementacion del inventario:

Sera un contenedor de Items.

- Debera permitir obtener un item guardado en la posicion X.
- Debera permitir guardar un item, no hay razon para indicar una posicion especifica.
- Debera permitir eliminar un item guardado en la posicion X.


void Inventario::almacenar(std::unique_ptr<Item> item){
    items.push_back(item);
}

Item* Inventario::obtenerItem(unsigned int pos){
    if (!items[pos]){
        throw Excepcion();
    }
    return items[pos].get();
}

void Inventario::eliminar(unsigned int pos){
    items[pos] = nullptr;
}

std::vector<std::string> Inventario::obtenerTodosLosItems(){
    std::vector<std::string> resultado;
    for (auto &item : items){
        resultado.push_back(item.get()->obtenerId());
    }
    return resultado;
}

Entonces el proceso de equipar un item es:

1- El cliente abre el inventario, manda la operacion VER_INVENTARIO
2- La operacion se desencola del GameLoop, obtiene el vector de ids de los items del inventario y la envia.
3- El cliente recibe el vector y dibuja.
4- El cliente selecciona un elemento y efectua una accion, como por ejemplo utilizar.
5- Se envia la operacion UTILIZAR_ITEM junto a la posicion del item en el inventario.
6- La Operacion se desencola y ejecuta en el GameLoop.
7- Se llama a inventario indicando el objeto a obtener.
8- Se ejecuta la accion utilizar() sobre el objeto obtenido.

Si no se puede obtener el objeto del inventario se lanza una excepcion desde el, la cual sera atrapada en Operacion para
decidir si se le envia algun mensaje en particular al Cliente.


*/