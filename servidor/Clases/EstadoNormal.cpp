#include "EstadoNormal.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Arma.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Interactuable.h"
#include "Sacerdote.h"
#include "Cliente.h"
#include "Item.h"
#include "Divulgador.h"
#include <utility>

EstadoNormal::EstadoNormal(Personaje *unPersonaje) : Estado(unPersonaje){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id = "EstadoNormal";
    idTCP = config->obtenerEstadoIDTCP(id);
}

//Ataque

std::string EstadoNormal::atacar(Entidad *objetivo, Arma *arma){
    return std::move(arma->atacar(objetivo, personaje, personaje->mapaAlQuePertenece));
}

std::string EstadoNormal::serAtacadoPor(Entidad *atacante){
    return std::move(atacante->atacar(personaje));
}

//Otras acciones

void EstadoNormal::meditar(){
    if (personaje->manaActual == personaje->manaMaximo) return;
    personaje->estadoMeditacion();
}

void EstadoNormal::dejarDeMeditar(){
    //Do nothing
}

void EstadoNormal::actualizar(double tiempo){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    float regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    float regenMana = config->calcularRecupManaTiempo(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    Posicion nuevaPosicion = personaje->posicion.mover(tiempo);
    personaje->mapaAlQuePertenece->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

//Comerciar

void EstadoNormal::interactuar(Entidad *entidad){
    //entidad->interactuar(personaje);
}

void EstadoNormal::sanar(){
    personaje->curar(personaje->vidaMaxima, personaje->manaMaximo);
    personaje->estadoNormal();
}

bool EstadoNormal::curar(float curVida, float curMana){
    personaje->curar(curVida, curMana);
    return true;
}

void EstadoNormal::pedirListado(Interactuable *interactuable, Cliente *cliente){
    interactuable->listar(personaje, cliente);
}

void EstadoNormal::pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    interactuable->comprar(pos, personaje, cliente);
}

void EstadoNormal::pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente){
    Item *item = personaje->inventario.obtenerItem(pos);
    item->desequipar(personaje, pos);
    personaje->inventario.eliminar(pos);
    interactuable->vender(item, personaje, cliente);
}


EstadoNormal::~EstadoNormal(){}