#include "BolsaDeItems.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "FabricaDeItems.h"
#include "Configuraciones.h"
#include <sstream>
#include "Excepcion.h"

static unsigned int contadorDeInstancias = 0;

BolsaDeItems::BolsaDeItems(Posicion unaPosicion, Item *item) : 
                                                            Entidad(""),
                                                            elementos(1),
                                                            bolsaVacia(false),
                                                            tamBolsa(0){
    
    Configuraciones *config = Configuraciones::obtenerInstancia();
    uint32_t ancho = config->obtenerBolsaDeDropAncho();
    uint32_t alto = config->obtenerBolsaDeDropAlto();
    tamBolsa = config->obtenerTamanioTienda();
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    itemNulo = fabrica -> crearItemNulo();
    items.resize(tamBolsa, itemNulo);
    items[0] = item;
    std::stringstream nuevoId;
    nuevoId << "BolsaDeItems#" << contadorDeInstancias;
    contadorDeInstancias++;
    id = nuevoId.str(); 
    this->posicion = std::move(Posicion(0, 0, ancho, alto));
    this->posicion.actualizarPosicion(std::move(unaPosicion));
}

BolsaDeItems::BolsaDeItems(Posicion unaPosicion, std::vector<Item*> unosItems) :
                                                           Entidad(""),
                                                           items(std::move(unosItems)),
                                                           elementos(0),
                                                           bolsaVacia(true),
                                                           tamBolsa(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    uint32_t ancho = config->obtenerBolsaDeDropAncho();
    uint32_t alto = config->obtenerBolsaDeDropAlto();
    tamBolsa = config->obtenerTamanioTienda();    
    std::stringstream nuevoId;
    nuevoId << "BolsaDeItems#" << contadorDeInstancias;
    contadorDeInstancias++;
    id = nuevoId.str(); 
    for (auto &item : items){
        if (item != itemNulo) elementos++;
    }
    if (elementos > 0) bolsaVacia = false;
    this->posicion = std::move(Posicion(0, 0, ancho, alto));
    this->posicion.actualizarPosicion(std::move(unaPosicion));
}

void BolsaDeItems::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}
void BolsaDeItems::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}
void BolsaDeItems::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    std::string mensaje = "No puede almacenar items en una bolsa de drop";
    cliente->enviarChat(mensaje, false);
}

void BolsaDeItems::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return;
    }
    if (pos >= tamBolsa || items[pos] == itemNulo){
        //No hay nada que entregarle
        return;
    }
    personaje->almacenar(items[pos]);
    //Si falla al almacenar no se pisa el puntero
    items[pos] = itemNulo;
    elementos--;
    if (elementos <= 0) bolsaVacia = true;
    cliente -> enviarInventario();
    cliente -> enviarContenedor(items);
}
void BolsaDeItems::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //No se puede almacenar un item en una bolsa de items.
}
void BolsaDeItems::listar(Personaje *personaje, Cliente *cliente){
    cliente -> enviarContenedor(items);
}

bool BolsaDeItems::haFinalizado(){
    if (bolsaVacia){
        mapaAlQuePertenece->eliminarEntidad(this);
    }
    return bolsaVacia;
}

//Ataque

void BolsaDeItems::atacar(Personaje *objetivo){
    //Nada
}

void BolsaDeItems::atacar(Criatura *objetivo){
    //Nada
}

void BolsaDeItems::serAtacadoPor(Personaje *atacante){
    //Nada
}

void BolsaDeItems::serAtacadoPor(Criatura *atacante){
    //Nada
}

bool BolsaDeItems::recibirDanio(int danio, Entidad *atacante){
    return false;
}

void BolsaDeItems::actualizarEstado(double tiempo){
    //Logica de despawn.
}

void BolsaDeItems::dropearItems(Entidad *atacante){
    //Nada
}

BolsaDeItems::~BolsaDeItems(){

}