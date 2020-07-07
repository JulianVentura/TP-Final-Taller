#include "Criatura.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Configuraciones.h"
#include "FabricaDeItems.h"
#include "BolsaDeItems.h"
#include <utility>
#include <memory>
#include <sstream>

Criatura::Criatura(float x, float y, std::string unId) : 
                                       Entidad(unId),
                                       diferenciador(0){
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los campos.
    vidaMaxima = config->obtenerCriaturaVidaMax(unId);
    vidaActual = vidaMaxima;
    manaMaximo = config->obtenerCriaturaManaMax(unId);
    manaActual = manaMaximo;
    nivel = config->obtenerCriaturaNivel(unId);
    fuerza = config->obtenerCriaturaFuerza(unId);
    inteligencia = config->obtenerCriaturaInteligencia(unId);
    agilidad = config->obtenerCriaturaAgilidad(unId);
    constitucion = config->obtenerCriaturaConstitucion(unId);
    std::string idArma = config->obtenerCriaturaIdArma(id);
    float ancho = config->obtenerCriaturaAncho(unId);
    float alto = config->obtenerCriaturaAncho(unId);
    posicion = std::move(Posicion(x, y, ancho, alto));
    this->arma = fabricaItems->crearArma(idArma);
    inventario.almacenar(this->arma);
    desplazamiento = config->obtenerCriaturaVelDesplazamiento(unId);
}

void Criatura::agregarDiferenciador(const unsigned int numero){
    diferenciador = numero;
    std::stringstream nuevoId;
    nuevoId << this->id << numero;
    id = nuevoId.str();
}

const std::string Criatura::obtenerId() const {
    std::stringstream _id;
    _id << this->id << diferenciador;
    return _id.str();
}

void Criatura::dropearItems(Entidad *atacante){
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    TipoDrop tipo = config->calcularDrop(id);
    if (tipo == ORO){
        unsigned int cantidad = config->calcularDropOro(id);
        atacante->recibirOro(cantidad);
    }else if (tipo == ITEM){
        //Siempre se va a obtener un drop
        Item* item = fabricaItems->obtenerItemAleatorio(id);
        std::unique_ptr<BolsaDeItems> bolsa(new BolsaDeItems(this->posicion, item));
        //No hay riesgo de RC al cargar algo a mapa porque este es el unico hilo que accede a el.
        this->mapaAlQuePertenece->cargarDrop(std::move(bolsa));
    }
    //No se dropea nada.
}


void Criatura::atacar(Entidad *objetivo){
    objetivo->serAtacadoPor(this);
}

void Criatura::atacar(Personaje *objetivo){
    arma->atacar(objetivo, this);
}

void Criatura::atacar(Criatura *objetivo){
    arma->atacar(objetivo, this);
}

void Criatura::serAtacadoPor(Personaje *atacante){
    atacante->atacar(this);
}

void Criatura::serAtacadoPor(Criatura *atacante){
    atacante->atacar(this);
}

Criatura::~Criatura(){}
