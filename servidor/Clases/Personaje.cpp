#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Estado.h"
#include "EstadoNormal.h"
#include "EstadoFantasma.h"
#include "EstadoMeditacion.h"
#include "Criatura.h"
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

void Personaje::recibirDanio(int danio, Personaje *atacante){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    if (!config->sePuedeAtacar(this, atacante)) return;
    estado->recibirDanio(danio, atacante);
}

void Personaje::recibirDanio(int danio, Criatura *atacante){
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
- Se le debe poder indicar una venta, el item vendido no tiene por que mostrarse.

- Las compras y ventas deben manejar transacciones de dinero al personaje que las efectua, las tiendas tienen
dinero infinito (inflation incoming).

Mas puntualmente:

std::vector<Item*> Tienda::listar(){
    return items;
}

Tienda::vender(unsigned int pos, Personaje *comprador){
    if (!items[pos]) return nullptr;
    comprador->pagar(items[pos]->obtenerPrecio());
    return items[pos];
}

Tienda::comprar(Item *item, Personaje *vendedor){
    vendedor->cobrar(item->obtenerPrecio());
}

Banquero:

std::vector<Item*> Banquero::listar(){
    return items;
}

Banquero::vender(unsigned int pos, Personaje *comprador){
    return items[pos];
}

Banquero::comprar(Item* item, Personaje *vendedor){
    for (size_t i=0; i<items.size(); i++){
        if (items[i] = nullptr){
            items[i] = item;
        }
    }
    throw Excepcion("No hay espacio en el almacen");
}

Sacerdote::sanar(Personaje *personaje){
    personaje->curar();
}

Cuando reciba una operacion de listar:

Operacion::ejecutar(){
    Personaje *personaje = Cliente->obtenerPersonaje();
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.interactuar(personaje->estado());
}

Banquero::interactuar(Fantasma *fantasma){
    //Lanzar excepcion.
}

Sacerdote::interactuar(Fantasma *fantasma){
    fantasma->curar();
}

Personaje::interactuarCon(Banquero banquero){

}


Seguimiento de OP_INTERACTUAR:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.interactuar(personaje, cliente);
}

Banquero::interactuar(personaje, cliente){
    personaje.pedirTienda(this, cliente);
}

Personaje::pedirleTiendaA(Ciudadano, cliente){
    estado.pedirTienda(Ciudadano, cliente);
}

EstadoNormal::pedirTienda(Ciudadano, cliente){
    lista = ciudadano.listar();
    cliente.enviar(lista);
}

EstadoFantasma::pedirTienda(Ciudadano, cliente){
    //Nada
}


Seguimiento de OP_COMPRAR:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.comprar(personaje, cliente);
}

Banquero::comprar(personaje, cliente){
    personaje.comprarDe(this, cliente);
}

O sino

Sacerdote::interactuar(personaje, cliente){
    //Nada
}

Personaje::comprarDe(Ciudadano, cliente){
    estado.comprarDe(Ciudadano, cliente);
}

EstadoNormal::comprarDe(Ciudadano, cliente){
    ciudadano.comprar();
    cliente.actualizarInventario();
}

EstadoFantasma::comprarDe(Ciudadano, cliente){
    //Nada
}


Seguimiento de OP_INTERACTUAR con Sacerdote:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.interactuar(personaje, cliente);
}

Sacerdote::interactuar(personaje, cliente){
    personaje.pedirCuracion(this, cliente);
}

Personaje::pedirCuracion(Sacerdote, cliente){
    estado.pedirCuracion(Sacerdote, cliente);
}

EstadoNormal::pedirCuracion(Sacerdote, cliente){
    sacerdote.curar(this);
}

EstadoFantasma::pedirTienda(Sacerdote, cliente){
    sacerdote.curar(this);
}




OTRA OPCION

Seguimiento de OP_INTERACTUAR:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.interactuar(personaje, personaje->estado, cliente);
}

Banquero::interactuar(personaje, estado, cliente){
    estado.pedirTienda(this, cliente);
}

EstadoNormal::pedirTienda(Banquero, cliente){
    lista = banquero.listar();
    cliente.enviar(lista);
}

EstadoFantasma::pedirTienda(Banquero, cliente){
    //Nada
}

Seguimiento de OP_INTERACTUAR con Sacerdote:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.interactuar(personaje, estado, cliente);
}

Sacerdote::interactuar(personaje, cliente){
    estado.pedirCuracion(this, cliente);
}

EstadoNormal::pedirCuracion(Sacerdote, cliente){
    sacerdote.curar(this);
}

EstadoFantasma::pedirTienda(Sacerdote, cliente){
    sacerdote.curar(this);
}



Seguimiento de OP_COMPRAR:

Operacion::ejecutar(){
    Ciudadano *ciudadano = mapa.obtenerCiudadano(id);
    ciudadano.comprar(personaje, estado, cliente);
}

Banquero::comprar(personaje, cliente){
    estado.comprarDe(this, cliente);
}

O sino

Sacerdote::interactuar(personaje, cliente){
    //Nada
}

EstadoNormal::comprarDe(Ciudadano, cliente){
    ciudadano.comprar();
    cliente.actualizarInventario();
}

EstadoFantasma::comprarDe(Ciudadano, cliente){
    //Nada
}

*/