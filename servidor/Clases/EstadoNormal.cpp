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

EstadoNormal::EstadoNormal(Personaje *unPersonaje) : Estado(unPersonaje){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id = "EstadoNormal";
    idTCP = config->obtenerEstadoIDTCP(id);
}

//Ataque

void EstadoNormal::atacar(Entidad *objetivo, Arma *arma){
    if (arma){
        arma->atacar(objetivo, personaje, personaje->mapaAlQuePertenece);
    }
}


bool EstadoNormal::recibirDanio(int danio, Entidad *atacante){
    return personaje->_recibirDanio(danio, atacante);
}

void EstadoNormal::serAtacadoPor(Entidad *atacante){
    atacante->atacar(personaje);
}

//Otras acciones

void EstadoNormal::meditar(){
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
    Posicion nuevaPosicion = personaje->posicion.mover();
    personaje->mapaAlQuePertenece->actualizarPosicion(personaje, std::move(nuevaPosicion));
}

//Comerciar

void EstadoNormal::interactuar(Entidad *entidad){
    //entidad->interactuar(personaje);
}

void EstadoNormal::pedirCuracion(Sacerdote *sacerdote, Cliente *cliente){
    sacerdote->curar(personaje, cliente);
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