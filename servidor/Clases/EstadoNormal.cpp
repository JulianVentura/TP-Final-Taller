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

void EstadoNormal::interactuar(Entidad *entidad){
    //entidad->interactuar(personaje);
}

void EstadoNormal::atacar(Entidad *objetivo, Arma *arma, Divulgador *divulgador){
    if (arma){
        arma->atacar(objetivo, personaje, divulgador);
    }
}

void EstadoNormal::actualizar(double tiempo, Mapa *mapa){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    unsigned int regenVida = config->calcularRecuperacionVida(personaje, tiempo);
    unsigned int regenMana = config->calcularRecupManaTiempo(personaje, tiempo);
    personaje->curar(regenVida, regenMana);
    Posicion nuevaPosicion = personaje->posicion.mover();
    mapa->actualizarPosicion(personaje, std::move(nuevaPosicion));
}


void EstadoNormal::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    personaje->vidaActual -= danio;
    unsigned int exp = configuraciones->calcularExpPorGolpe(personaje, atacante, danio);
    atacante->obtenerExperiencia(exp);
    if (personaje->vidaActual <= 0){
        exp = configuraciones->calcularExpPorMatar(personaje, atacante);
        atacante->obtenerExperiencia(exp);
        personaje->dropearItems(atacante);
        personaje->estadoFantasma();
    }
}

void EstadoNormal::serAtacadoPor(Entidad *atacante, Divulgador *divulgador){
    atacante->atacar(personaje, divulgador);
}

void EstadoNormal::meditar(){
    personaje->estadoMeditacion();
}

void EstadoNormal::dejarDeMeditar(){
    //Do nothing
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
    personaje->inventario.eliminar(pos);
    interactuable->vender(item, personaje, cliente);
}


EstadoNormal::~EstadoNormal(){}