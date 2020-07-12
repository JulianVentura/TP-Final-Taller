#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Estado.h"
#include "EstadoNormal.h"
#include "EstadoFantasma.h"
#include "EstadoMeditacion.h"
#include "Arma.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "Excepcion.h"
#include "Criatura.h"
#include "FabricaDeItems.h"
#include "Divulgador.h"
#include <utility>

#define TAMANIO_ALMACEN 18 //Esto se tiene que levantar de configuraciones.json
#define NIVEL_INICIAL 1

Personaje::Personaje() : Entidad(""),
                         experiencia(0),
                         limiteParaSubir(0),
                         cantidadOro(0),
                         arma(NO_EQUIPADO),
                         armadura(NO_EQUIPADO),
                         escudo(NO_EQUIPADO),
                         casco(NO_EQUIPADO),
                         estado(nullptr){
    nivel = NIVEL_INICIAL;
    almacen.resize(TAMANIO_ALMACEN, nullptr);
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    std::string idArma = "Espada";
    arma = 0;
    inventario.almacenar(fabricaItems->crearArma(idArma));
    actualizarAtributos();
}

Personaje::Personaje(float x, float y, std::string id, std::string idClase, std::string idRaza) : 
                                       Entidad(id),
                                       experiencia(0),
                                       limiteParaSubir(0),
                                       cantidadOro(0),
                                       arma(NO_EQUIPADO),
                                       armadura(NO_EQUIPADO),
                                       escudo(NO_EQUIPADO),
                                       casco(NO_EQUIPADO),
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
    arma = 0;
    inventario.almacenar(fabricaItems->crearArma(idArma));
    almacen.resize(TAMANIO_ALMACEN, nullptr);   //La idea es levantar el tamaño del almacen del json
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

void Personaje::actualizarEstado(double tiempo){
    estado->actualizar(tiempo);
}

bool Personaje::_recibirDanio(int danio, Entidad *atacante){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    std::stringstream mensaje;
    if (config->seEsquivaElGolpe(this)){
        mensaje << "El oponente ha esquivado el golpe";
        divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
        mensaje.str() = "Has esquivado el golpe";
        divulgador->encolarMensaje(this->id, mensaje.str());
        return true;
    }
    unsigned int defensa = config->calcularDefensa(this);
    if (danio - defensa < 0){
        danio = 0;
    }else{
        danio -= defensa;
    }
    mensaje << "Realizas " << danio << "de danio";
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
    mensaje.str("");
    mensaje << "Recibes " << danio << "de danio";
    divulgador->encolarMensaje(this->id, mensaje.str());
    unsigned int exp = config->calcularExpPorGolpe(this, atacante, danio);
    atacante->obtenerExperiencia(exp);
    if (vidaActual - danio <= 0){
        vidaActual = 0;
        exp = config->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(exp);
        dropearItems(atacante);
        mensaje.str() = "Has muerto";
        divulgador->encolarMensaje(this->id, mensaje.str());
        estadoFantasma();
    }else{
        vidaActual -= danio;
    }
    return true;
}

bool Personaje::recibirDanio(int danio, Entidad *atacante){
    return estado->recibirDanio(danio, atacante);
}

void Personaje::atacar(Personaje *objetivo){
    if (arma == NO_EQUIPADO) return;
    //Estoy seguro de que el casteo sera valido.
    
    /* COMENTO POR DEBUG
    Configuraciones *config = Configuraciones::obtenerInstancia();
    
    if (!config->sePuedeAtacar(objetivo, this)){
        Divulgador *divulgador = Divulgador::obtenerInstancia();
        std::string mensaje = "No se puede realizar el ataque por FairPlay";
        divulgador->encolarMensaje(this->obtenerId(), mensaje);
        return;
    }
    */
    estado->atacar(objetivo, (Arma*)inventario.obtenerItem(arma));
}

void Personaje::atacar(Criatura *objetivo){
    if (arma == NO_EQUIPADO) return;
    //Estoy seguro de que el casteo sera valido.
    estado->atacar(objetivo, (Arma*)inventario.obtenerItem(arma));
}

void Personaje::serAtacadoPor(Entidad *atacante){
    estado->serAtacadoPor(atacante);
}

void Personaje::serAtacadoPor(Personaje *atacante){
    //Chequeo FairPlay
    estado->serAtacadoPor(atacante);
}

void Personaje::serAtacadoPor(Criatura *atacante){
    estado->serAtacadoPor(atacante);
}


void Personaje::curar(float curVida, float curMana){
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
    Configuraciones *config = Configuraciones::obtenerInstancia();
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    std::vector<Item*> drop = std::move(*this->inventario.obtenerTodosLosItems());
    inventario.eliminarTodosLosItems();
    for (std::size_t i=0; i<drop.size(); i++){
        if (drop[i]) drop[i]->desequipar(this, i);
    }
    std::unique_ptr<BolsaDeItems> bolsa(new BolsaDeItems(this->posicion, 
                                                         std::move(drop)));
    unsigned int oroSeguro = config->calcularMaxOroSeguro(this);
    std::stringstream mensaje;
    if (cantidadOro > oroSeguro){
        unsigned int oroAEntregar = cantidadOro - oroSeguro;
        atacante->recibirOro(oroAEntregar);
        restarOro(oroAEntregar);
        mensaje << "Recibes " << oroAEntregar << " oro";
        divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
    }

    //No hay riesgo de RC al cargar algo a mapa porque este es el unico hilo que accede a el.
    mapaAlQuePertenece->cargarEntidad(std::move(bolsa));
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

void Personaje::almacenar(Item *item){
    inventario.almacenar(item);
}

void Personaje::equipar(Arma *arma, unsigned int pos){
    this->arma = pos;
}

void Personaje::equipar(Armadura *armadura, unsigned int pos){
    this->armadura = inventario.almacenar(armadura);
}

void Personaje::equipar(Casco *casco, unsigned int pos){
    this->casco = pos;
}

void Personaje::equipar(Escudo *escudo, unsigned int pos){
    this->escudo = pos;
}

void Personaje::desequipar(Arma *arma, int pos){
    if (this->arma == pos){
        this->arma = NO_EQUIPADO;
    }
}

void Personaje::desequipar(Armadura *armadura, int pos){
    if (this->armadura == pos){
        this->armadura = NO_EQUIPADO;
    }
}

void Personaje::desequipar(Escudo *escudo, int pos){
    if (this->escudo == pos){
        this->escudo = NO_EQUIPADO;
    }
}

void Personaje::desequipar(Casco *casco, int pos){
    if (this->casco == pos){
        this->casco = NO_EQUIPADO;
    }
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


void Personaje::tirar(unsigned int pos){
    Item *item = inventario.obtenerItem(pos);
    inventario.eliminar(pos);
    item->desequipar(this, pos);
    std::unique_ptr<BolsaDeItems> bolsa(new BolsaDeItems(this->posicion, 
                                                         std::move(item)));
    mapaAlQuePertenece->cargarEntidad(std::move(bolsa));
}

void Personaje::utilizar(unsigned int pos){
    Item *item = inventario.obtenerItem(pos);
    item->utilizar(this, pos);
}

void Personaje::interactuar(Estado *estado, Cliente *cliente){
    //No hago nada
}

void Personaje::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    //No hago nada
}

void Personaje::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    //No hago nada
}

void Personaje::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    //No hago nada
}

void Personaje::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //No hago nada
}

void Personaje::listar(Personaje *personaje, Cliente *cliente){
    //No hago nada
}
