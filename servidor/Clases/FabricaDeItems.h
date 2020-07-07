#ifndef __FABRICA_DE_ITEMS_H__
#define __FABRICA_DE_ITEMS_H__
#include <memory>
#include <mutex>
#include <unordered_map>
class Item;
class Pocion;
class Arma;
class Armadura;
class Casco;
class Escudo;
class FabricaDeItems{
    private:
    std::unordered_map<std::string, std::unique_ptr<Arma>> armas;
    std::unordered_map<std::string, std::unique_ptr<Armadura>> armaduras;
    std::unordered_map<std::string, std::unique_ptr<Casco>> cascos;
    std::unordered_map<std::string, std::unique_ptr<Escudo>> escudos;
    std::unordered_map<std::string, std::unique_ptr<Pocion>> pociones;
    std::mutex mutex;

    public:
    Item* obtenerItemAleatorio(std::string &idCriatura);
    static FabricaDeItems* obtenerInstancia();

    //Arma
    Arma* crearArma(std::string &id);
    //Armadura
    Armadura* crearArmadura(std::string &id);
    //Escudo
    Escudo* crearEscudo(std::string &id);
    //Casco
    Casco* crearCasco(std::string &id);
    //Pocion
    Pocion* crearPocion(std::string &id);
    
    private:
    FabricaDeItems();
    static FabricaDeItems instancia;
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

FabricaDeItems::obtenerItemAleatorio(){
    Devuelve un item aleatorio.
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


Como sera la estructura de creacion de items.


FabricaDeItems::fabricarArma(id){
    int danioMax = configuraciones.obtenerArmaDanioMax(id);
    int danioMin = configuraciones.obtenerArmaDanioMax(id);
    unsigned int rangoAtaque = configuraciones.obtenerArmaDanioMax(id);
    unsigned int consumoMana = configuraciones.obtenerArmaDanioMax(id);
    return std::unique_ptr(new Arma(danioMax, danioMin, rangoAtaque, consumoMana));
}

FabricaDeItems::fabricarArmadura(id){
    idem al anterior.
}

FabricaDeItems::fabricarEscudo(id){
    
}

FabricaDeItems::fabricarCasco(id){
    
}

FabricaDeItems::fabricarPocion(id){
    
}

FabricaDeItems::fabricarOro(unsigned int cantidad){
    
}

FabricaDeItems::fabricarItemAleatorio(){

}


Para los items aleatorios:

Cada criatura podria tener una lista de los items que puede dropear, de la sig forma.

Golum: {
    Drops: {
        Armas: {
            "Probabilidad" = 0.03,
            "Armas": [["Espada", 0.5],["Varaculo", 0.5]]
        }
        Armaduras: {
            "Probabilidad" = 0.03,
            "Armaduras":["ArmaduraDeCuero"]
        }
        Cascos: {
            "Probabilidad" = 0,
            "Cascos" = []
        }
        Pociones: ["PocionDeVida"],
        Oro: ["100"]                        //Esto indica la cant maxima de oro dropeable
    }
}

Luego cada Criatura almacenara esta lista en forma de:

std::unordered_map<std::vector<std::string>> drops;

La cual le pasara a FabricaDeItems al momento de necesitar dropear algo.

FabricaDeItems se encargara de llamar a Configuraciones para ver que clase de item debe ser dropeado (puede ser ninguno)
Luego FabricaDeItems se encargara de dropear un item segun el resultado de Configuraciones, esto es:

Si toca "Armas" entonces dropea un arma fijandose los drops de armas de Golum, seleccionando uno uniformemente.
Lo mismo si toca "Cascos", "Escudos", "Armaduras" o "Pociones".
Si toca "Oro" entonces se leera la cantidad maxima dropeable


Entonces se tendra que tener un parseo al momento de crear los items dentro de FabricaDeItems, del estilo:





*/

