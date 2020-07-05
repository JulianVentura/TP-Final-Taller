#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Estado.h"
#include "EstadoNormal.h"
#include "EstadoFantasma.h"
#include "EstadoMeditacion.h"
#include <utility>

#define NIVEL_INICIAL 1

Personaje::Personaje() : Entidad(""){
    nivel = NIVEL_INICIAL;
    fuerza = 0;
    inteligencia = 0;
    agilidad = 0;
    constitucion = 0;
    vidaMaxima = 0;
    vidaActual = 0;
    manaMaximo = 0;
    manaActual = 0;
    desplazamiento = 0;
}

Personaje::Personaje(float x, float y, std::string id, std::string idClase, std::string idRaza) : 
                                       Entidad(id),
                                       raza(idRaza),
                                       clase(idClase),
                                       estado(nullptr){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los campos.
    nivel = NIVEL_INICIAL;
    experiencia = 0;
    actualizarAtributos();
    float ancho = config->obtenerPersonajeAncho();
    float alto = config->obtenerPersonajeAlto();
    posicion = std::move(Posicion(x, y, ancho, alto));
    desplazamiento = config->obtenerPersonajeVelDesplazamiento();
    estado = std::move(std::unique_ptr<Estado>(new EstadoNormal(this)));
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
    otro.estado = nullptr;
    
    return *this;
}

Personaje::~Personaje(){}


void Personaje::actualizarAtributos(){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    vidaMaxima = configuraciones->calcularVidaMax(this);
    manaMaximo = configuraciones->calcularManaMax(this);
    limiteParaSubir = configuraciones->calcularLimiteParaSubir(this);
    fuerza = configuraciones->calcularFuerza(this);
    inteligencia = configuraciones->calcularInteligencia(this);
    agilidad = configuraciones->calcularAgilidad(this);
    constitucion = configuraciones->calcularConstitucion(this);
}

void Personaje::obtenerExperiencia(unsigned int cantidad){
    experiencia += cantidad;
    if (experiencia >= limiteParaSubir){
        nivel++;
        actualizarAtributos();
    }
}

void Personaje::actualizarEstado(double tiempo, Mapa *mapa){
    estado->actualizar(tiempo, mapa);
}

void Personaje::recibirDanio(int danio, Entidad *atacante){
    estado->recibirDanio(danio, atacante);
}


void Personaje::curar(unsigned int curVida, unsigned int curMana){
    vidaActual += curVida;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    manaActual += curMana;
    if (manaActual > manaMaximo) manaActual = manaMaximo;
}

void Personaje::eliminarDeInventario(unsigned int pos){
    inventario.eliminar(pos);
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


/*

Diseño de las tiendas:

Requisitos:

- Se le debe pedir que muestren su contenido, que debe ser un vector de items ordenado.
- Se le debe poder indicar una compra, direccionada por el orden del item segun el vector antes entregado.
- Se le debe poder indicar una venta, el item se debera guardar en la primera posicion disponible.

- Las compras y ventas deben manejar transacciones de dinero al personaje que las efectua, las tiendas tienen
dinero infinito (inflation incoming).

Mas puntualmente:

std::vector<Item*> Tienda::listar(){
    std::vector<Item*> resultado;
    for (size_t i=0; i<items.size(); i++){
        if (items[i] == nullptr) continue;
        resultado.push_back(items[i].get());
    }

    return resultado;
}

Tienda::vender(unsigned int pos, Personaje *comprador){
    comprador->pagar(items[pos]->obtenerPrecio());
    std::unique_ptr<Item> compra = std::move(items[pos]);
    items[pos] = nullptr;
    return compra;
}

Tienda::comprar(std::unique_ptr<Item> item, Personaje *vendedor){
    bool comprado = false;
    for (size_t i=0; i<items.size(); i++){
        if (items[i] == nullptr){
            items[i] = std::move(item);
            comprado = true;
        }
    }
    if (!comprado){
        //No hay espacio
        vendedor->almacenar(std::move(item));
    }
    vendedor->cobrar(item->obtenerPrecio());
}

Tienda::

*/