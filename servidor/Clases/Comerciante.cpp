#include "Comerciante.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "Arma.h"
#include "Armadura.h"
#include "Casco.h"
#include "Escudo.h"
#include "Pocion.h"
#include "FabricaDeItems.h"

Comerciante::Comerciante(float x, float y) : Entidad("Comerciante#"), tamTienda(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id_base = "Comerciante";
    uint32_t ancho = config->obtenerCiudadanoAncho(id_base);
    uint32_t alto = config->obtenerCiudadanoAlto(id_base);
    tamTienda = config->obtenerTamanioTienda();
    posicion = std::move(Posicion(x, y, ancho, alto));
    
    std::string idItem;
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    itemNulo = fabrica -> crearItemNulo();
    /*
    idItem = "Hacha";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "Martillo";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "VaraDeFresno";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "ArmaduraDeCuero";
    items.push_back(fabrica->crearArmadura(idItem));
    idItem = "ArmaduraDePlacas";
    items.push_back(fabrica->crearArmadura(idItem));
    idItem = "Capucha";
    items.push_back(fabrica->crearCasco(idItem));
    idItem = "EscudoDeTortuga";
    items.push_back(fabrica->crearEscudo(idItem));
    */
    idItem = "Espada";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "VaraDeFresno";
    items.push_back(fabrica->crearArma(idItem));
    idItem = "PocionVida";
    items.push_back(fabrica->crearPocion(idItem));
    idItem = "PocionMana";
    items.push_back(fabrica->crearPocion(idItem));
    for(int i = 0;i < 14;i++){
        items.push_back(itemNulo);
    }
}

void Comerciante::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}
void Comerciante::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}
void Comerciante::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirVenta(pos, this, cliente);
}

void Comerciante::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        return;
    }
    if (pos >= tamTienda || items[pos] == itemNulo){
        //No hay nada que comprar
        return;
    }
    if (personaje->tieneOroSuficiente(items[pos]->obtenerPrecio())){
        personaje->almacenar(items[pos]);
        personaje->restarOro(items[pos]->obtenerPrecio());
        cliente -> enviarInventario();
        cliente -> enviarTienda(items);
        std::string mensaje = "Se compro " + items[pos]->obtenerId();
        cliente->enviarChat(mensaje, false);
    }else{
        std::string mensaje = "No tiene oro suficiente";
        cliente->enviarChat(mensaje, false);
    }
}

void Comerciante::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarChat(mensaje, false);
        personaje->almacenar(item);
        return;
    }
    
    personaje->recibirOro(item->obtenerPrecio());
    cliente -> enviarInventario();
    cliente -> enviarTienda(items);
    std::string mensaje = "Se vendio " + item->obtenerId();
    cliente->enviarChat(mensaje, false);
}

void Comerciante::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    cliente -> enviarTienda(items);
}

//Ataque

void Comerciante::atacar(Personaje *objetivo){
    //Nada
}

void Comerciante::atacar(Criatura *objetivo){
    //Nada
}

void Comerciante::serAtacadoPor(Personaje *atacante){
    //Nada
}

void Comerciante::serAtacadoPor(Criatura *atacante){
    //Nada
}

bool Comerciante::recibirDanio(int danio, Entidad *atacante){
    return false;
}

//Estado

void Comerciante::actualizarEstado(double tiempo){
    //Nada
}

void Comerciante::dropearItems(Entidad *atacante){
    //Nada
}


Comerciante::~Comerciante(){}