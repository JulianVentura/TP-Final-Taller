#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Estado.h"
#include "EstadoNormal.h"
#include "EstadoFantasma.h"
#include "EstadoMeditacion.h"
#include "Excepcion.h"
#include "Criatura.h"
#include "FabricaDeItems.h"
#include <utility>

#define TAMANIO_ALMACEN 18 //Esto se tiene que levantar de configuraciones.json
#define NIVEL_INICIAL 1

Personaje::Personaje() : Entidad(""),
                         manaMaximo(0),
                         manaActual(0),
                         experiencia(0),
                         limiteParaSubir(0),
                         cantidadOro(0),
                         armadura(nullptr),
                         escudo(nullptr),
                         casco(nullptr),
                         estado(nullptr){
    nivel = NIVEL_INICIAL;
    almacen.resize(TAMANIO_ALMACEN, nullptr);
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    std::string idArma = "Espada";
    arma = fabricaItems->crearArma(idArma);   //La idea es levantar esto del json, como con las criaturas
    inventario.almacenar(arma);
    actualizarAtributos();
}

Personaje::Personaje(float x, float y, std::string id, std::string idClase, std::string idRaza) : 
                                       Entidad(id),
                                       manaMaximo(0),
                                       manaActual(0),
                                       experiencia(0),
                                       limiteParaSubir(0),
                                       cantidadOro(0),
                                       armadura(nullptr),
                                       escudo(nullptr),
                                       casco(nullptr),
                                       raza(idRaza),
                                       clase(idClase),
                                       estado(nullptr),
                                       almacen(){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los campos.
    nivel = NIVEL_INICIAL;
    actualizarAtributos();
    float ancho = config->obtenerPersonajeAncho();
    float alto = config->obtenerPersonajeAlto();
    posicion = std::move(Posicion(x, y, ancho, alto));
    desplazamiento = config->obtenerPersonajeVelDesplazamiento();
    estado = std::move(std::unique_ptr<Estado>(new EstadoNormal(this)));
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    std::string idArma = "Espada";
    arma = fabricaItems->crearArma(idArma);   //La idea es levantar esto del json, como con las criaturas
    inventario.almacenar(arma);
    almacen.resize(TAMANIO_ALMACEN, nullptr);
}
Personaje& Personaje::operator=(Personaje &&otro){
    this->vidaActual = otro.vidaActual;
    this->manaActual = otro.manaActual;
    this->vidaMaxima = otro.vidaMaxima;
    this->manaMaximo = otro.manaMaximo;
    this->agilidad   = otro.agilidad;
    this->nivel      = otro.nivel;
    this->experiencia = otro.experiencia;
    this->limiteParaSubir = otro.limiteParaSubir;
    this->id = std::move(otro.id);
    this->posicion = std::move(otro.posicion);
    this->desplazamiento = otro.desplazamiento;
    this->estado = std::move(otro.estado);
    this->almacen = std::move(otro.almacen);
    otro.estado = nullptr;
    
    return *this;
}

Personaje::~Personaje(){}


void Personaje::actualizarAtributos(){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    fuerza = configuraciones->calcularFuerza(this);
    inteligencia = configuraciones->calcularInteligencia(this);
    agilidad = configuraciones->calcularAgilidad(this);
    constitucion = configuraciones->calcularConstitucion(this);
    limiteParaSubir = configuraciones->calcularLimiteParaSubir(this);
    vidaMaxima = configuraciones->calcularVidaMax(this);
    vidaActual = vidaMaxima;
    manaMaximo = configuraciones->calcularManaMax(this);
    manaActual = manaMaximo;
}

void Personaje::obtenerExperiencia(unsigned int cantidad){
    experiencia += cantidad;
    if (experiencia >= limiteParaSubir){
        nivel++;
        actualizarAtributos();
    }
}

uint16_t Personaje::obtenerOro(){
    return cantidadOro;
}

void Personaje::actualizarEstado(double tiempo, Mapa *mapa){
    estado->actualizar(tiempo, mapa);
}

void Personaje::recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador){
    estado->recibirDanio(danio, atacante, divulgador);
}

void Personaje::atacar(Personaje *objetivo, Divulgador *divulgador){
    estado->atacar(objetivo, arma, divulgador);
}

void Personaje::atacar(Criatura *objetivo, Divulgador *divulgador){
    estado->atacar(objetivo, arma, divulgador);
}

void Personaje::serAtacadoPor(Personaje *atacante, Divulgador *divulgador){
    //Chequeo FairPlay
    Configuraciones *config = Configuraciones::obtenerInstancia();
    if (!config->sePuedeAtacar(this, atacante)){
        //Enviar mensaje a atacante: "No se puede realizar el ataque por FairPlay"
        return;
    }
    estado->serAtacadoPor(atacante, divulgador);
}

void Personaje::serAtacadoPor(Criatura *atacante, Divulgador *divulgador){
    estado->serAtacadoPor(atacante, divulgador);
}


void Personaje::curar(unsigned int curVida, unsigned int curMana){
    vidaActual += curVida;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    manaActual += curMana;
    if (manaActual > manaMaximo) manaActual = manaMaximo;
}

void Personaje::curar(){
    this->curar(vidaMaxima, manaMaximo);
}

void Personaje::eliminarDeInventario(unsigned int pos){
    inventario.eliminar(pos);
}

void Personaje::dropearItems(Entidad *atacante){
    std::vector<Item*> drop = std::move(*this->inventario.obtenerTodosLosItems());
    inventario.eliminarTodosLosItems();
    std::unique_ptr<BolsaDeItems> bolsa(new BolsaDeItems(this->posicion, 
                                                         std::move(drop)));
    //Falta eliminar el oro en exceso
    //No hay riesgo de RC al cargar algo a mapa porque este es el unico hilo que accede a el.
    mapaAlQuePertenece->cargarDrop(std::move(bolsa));
}

std::vector<Item*>& Personaje::obtenerAlmacen(){
    return almacen;
}

std::vector<Item*>* Personaje::obtenerInventario(){
    return inventario.obtenerTodosLosItems();
}

bool Personaje::tieneOroSuficiente(unsigned int cantOro){
    if (this->cantidadOro >= cantOro) return true;
    return false;
}

void Personaje::restarOro(unsigned int cantOro){
    if (!tieneOroSuficiente(cantOro)){
        throw Excepcion("Error: Se ha intentado obtener mas oro del que Personaje dispone");
    }
    this->cantidadOro -= cantOro;
}

void Personaje::recibirOro(unsigned int cantOro){
    this->cantidadOro += cantOro;
}


void Personaje::equipar(Arma *arma){
    this->arma = arma;
}

void Personaje::equipar(Armadura *armadura){
    this->armadura = armadura;
}

void Personaje::equipar(Casco *casco){
    this->casco = casco;
}

void Personaje::equipar(Escudo *escudo){
    this->escudo = escudo;
}

void Personaje::meditar(){
    estado->meditar();    
}

void Personaje::frenarMeditacion(){
    estado->dejarDeMeditar();
}

void Personaje::estadoNormal(){
    estado = std::move(std::unique_ptr<Estado>(new EstadoNormal(this)));
}

void Personaje::estadoFantasma(){
    estado = std::move(std::unique_ptr<Estado>(new EstadoFantasma(this)));
}

void Personaje::estadoMeditacion(){
    estado = std::move(std::unique_ptr<Estado>(new EstadoMeditacion(this)));
}

Estado *Personaje::obtenerEstado(){
    return this->estado.get();
}