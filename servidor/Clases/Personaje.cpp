#include "Personaje.h"
#include "Mapa.h"
#include "Configuraciones.h"
#include "Estado.h"
#include "EstadoNormal.h"
#include "EstadoFantasma.h"
#include "EstadoMeditacion.h"
#include "EstadoInmovilizado.h"
#include "Arma.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "Excepcion.h"
#include "Criatura.h"
#include "FabricaDeItems.h"
#include "Divulgador.h"
#include "../../common/TCPIDs.h"        //Para el IDTCP de item nulo.
#include <utility>
#include <cstring>

#define TAMANIO_ALMACEN 18 //Esto se tiene que levantar de configuraciones.json
#define NIVEL_INICIAL 1

Personaje::Personaje() : Entidad(""),
                         experiencia(0),
                         limiteParaSubir(0),
                         limiteExpInferior(0),
                         cantidadOro(0),
                         oroEnAlmacen(0),
                         arma(NO_EQUIPADO),
                         armadura(NO_EQUIPADO),
                         escudo(NO_EQUIPADO),
                         casco(NO_EQUIPADO),
                         estado(nullptr){
    nivel = NIVEL_INICIAL;
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    std::string idArma = "Espada";
    arma = 0;
    almacen.resize(TAMANIO_ALMACEN, fabricaItems -> crearItemNulo());
    inventario.almacenar(fabricaItems->crearArma(idArma));
    actualizarAtributos();
}

Personaje::Personaje(float x, float y, std::string id, std::string idClase, std::string idRaza) : 
                                       Entidad(id),
                                       experiencia(0),
                                       limiteParaSubir(0),
                                       limiteExpInferior(0),
                                       cantidadOro(0),
                                       oroEnAlmacen(0),
                                       arma(NO_EQUIPADO),
                                       armadura(NO_EQUIPADO),
                                       escudo(NO_EQUIPADO),
                                       casco(NO_EQUIPADO),
                                       raza(idRaza),
                                       clase(idClase),
                                       estado(nullptr){
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
    almacen.resize(TAMANIO_ALMACEN, fabricaItems -> crearItemNulo());   //La idea es levantar el tamaño del almacen del json
}

Personaje::Personaje(std::string idPersonaje, std::string idRaza,
    std::string idClase, serializacionPersonaje& datos):
                                       Entidad(idPersonaje),
                                       arma(NO_EQUIPADO),
                                       armadura(NO_EQUIPADO),
                                       escudo(NO_EQUIPADO),
                                       casco(NO_EQUIPADO),
                                       raza(idRaza),
                                       clase(idClase),
                                       estado(nullptr){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    float ancho = config->obtenerPersonajeAncho();
    float alto = config->obtenerPersonajeAlto();
    posicion = std::move(Posicion(datos.x, datos.y, ancho, alto));
    desplazamiento = config->obtenerPersonajeVelDesplazamiento();
    if (datos.vidaActual <= 0){
        estado = std::move(std::unique_ptr<Estado>(new EstadoFantasma(this)));
    }else{
        estado = std::move(std::unique_ptr<Estado>(new EstadoNormal(this)));
    }
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    almacen.resize(TAMANIO_ALMACEN, fabricaItems -> crearItemNulo());
    experiencia = datos.experiencia;
    nivel = datos.nivel;
    actualizarAtributos();
    vidaActual = datos.vidaActual;
    manaActual = datos.manaActual;
    cantidadOro = datos.cantidadOro;
    oroEnAlmacen = datos.oroEnAlmacen;

    auto inventarioTemp = inventario.obtenerTodosLosItems();

    for(unsigned int i = 0; i < inventarioTemp -> size();i++){
        (*inventarioTemp)[i] = fabricaItems
         -> obtenerItemIDTCP(datos.inventario[i]);
    }

    for(unsigned int i = 0; i < almacen.size();i++){
        almacen[i] = fabricaItems
         -> obtenerItemIDTCP(datos.almacen[i]);
    }
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
    this->limiteExpInferior = otro.limiteExpInferior;
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
    limiteExpInferior = configuraciones->calcularLimiteExpInferior(this);
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



//Ataque

std::string Personaje::recibirDanio(int danio, Entidad *atacante){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    std::stringstream mensaje;
    std::string mensajeGolpeCritico = "";
    std::string mensajeDrop = "";
    if (config->esGolpeCritico(atacante, this)){
        danio *= 2;
        mensajeGolpeCritico = "Golpe critico. ";
    }else if (config->seEsquivaElGolpe(this)){
        mensaje << "Has esquivado el golpe";
        divulgador->encolarMensaje(this->id, mensaje.str());
        return "El oponente ha esquivado el golpe";
    }
    int defensa = config->calcularDefensa(this);
    //Guarda que quizas haya que hacer esto mismo con vidaActual < danio mas abajo.
    if (danio <= defensa){
        danio = 0;
    }else{
        danio -= defensa;
    }
    mensaje << "Recibes " << danio << " de danio";
    divulgador->encolarMensaje(this->id, mensaje.str());
    unsigned int exp = config->calcularExpPorGolpe(this, atacante, danio);
    atacante->obtenerExperiencia(exp);
    if ((vidaActual - danio) <= 0){
        vidaActual = 0;
        exp = config->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(exp);
        mensajeDrop = std::move(dropearItems(atacante));
        mensaje.str() = "Has muerto";
        divulgador->encolarMensaje(this->id, mensaje.str());
        estadoFantasma();
    }else{
        vidaActual -= danio;
    }
    mensaje.str("");
    mensaje << mensajeGolpeCritico << "Realizas " << danio << " de danio. " << mensajeDrop;
    return mensaje.str();
}


std::string Personaje::atacar(Personaje *objetivo){
    if (arma == NO_EQUIPADO) return "";
    Configuraciones *config = Configuraciones::obtenerInstancia();
    
    if (!config->sePuedeAtacar(objetivo, this)){
        return "No se puede realizar el ataque por FairPlay";
    }
    //Estoy seguro de que el casteo sera valido.
    return std::move(estado->atacar(objetivo, (Arma*)inventario.obtenerItem(arma)));
}

std::string Personaje::atacar(Criatura *objetivo){
    if (arma == NO_EQUIPADO) return "";
    //Estoy seguro de que el casteo sera valido.
    return std::move(estado->atacar(objetivo, (Arma*)inventario.obtenerItem(arma)));
    //Envio danio realizado
}

void Personaje::serAtacadoPor(Personaje *atacante){
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    if (mapaAlQuePertenece->esMapaSeguro()){
        divulgador->encolarMensaje(atacante->obtenerId(), "No puede atacar en una zona segura.");
        return;
    }
    std::string mensaje = estado->serAtacadoPor(atacante);
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje);
}

void Personaje::serAtacadoPor(Criatura *atacante){
    estado->serAtacadoPor(atacante);
}

void Personaje::recibirCuracion(unsigned int curacion, Entidad *lanzador){
    if (estado->curar(curacion, 0)){
        Divulgador *divulgador = Divulgador::obtenerInstancia();
        divulgador->encolarMensaje(this->id, "Has sido curado");
    }
}

void Personaje::curar(float curVida, float curMana){
    vidaActual += curVida;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    manaActual += curMana;
    if (manaActual > manaMaximo) manaActual = manaMaximo;
}

void Personaje::sanar(){
    estado->sanar();
}

void Personaje::eliminarDeInventario(unsigned int pos){
    inventario.eliminar(pos);
}

std::string Personaje::dropearItems(Entidad *atacante){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::vector<Item*> drop = std::move(*this->inventario.obtenerTodosLosItems());
    inventario.eliminarTodosLosItems();
    for (std::size_t i=0; i<drop.size(); i++){
        drop[i]->desequipar(this, i);
    }
    std::unique_ptr<BolsaDeItems> bolsa(new BolsaDeItems(this->posicion, 
                                                         std::move(drop)));
    unsigned int oroSeguro = config->calcularMaxOroSeguro(this);
    std::stringstream mensaje;
    if (cantidadOro > oroSeguro){
        unsigned int oroAEntregar = cantidadOro - oroSeguro;
        atacante->recibirOro(oroAEntregar);
        restarOro(oroAEntregar);
        mensaje <<  "Recibes " << oroAEntregar << " oro.";
    }
    //El mapa se asegura de que no haya una RC al cargar
    mapaAlQuePertenece->cargarEntidad(std::move(bolsa));
    return mensaje.str();
}

std::vector<Item*>& Personaje::obtenerAlmacen(){
    return almacen;
}

uint32_t& Personaje::obtenerOroAlmacen(){
    return oroEnAlmacen;
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
    this->armadura = pos;
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

void Personaje::estadoInmovilizado(double tiempo){
    estado = std::move(std::unique_ptr<Estado>(new EstadoInmovilizado(this, tiempo)));
}

Estado *Personaje::obtenerEstado(){
    return this->estado.get();
}

void Personaje::resucitar(double tiempo){
    estado->resucitar(tiempo);
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

void Personaje::transaccion(bool esDeposito, Estado *estado, Cliente *cliente){}

//Serializacion


serializacionPersonaje Personaje::serializar(){
    serializacionPersonaje datos;
    datos.x = posicion.obtenerX();
    datos.y = posicion.obtenerY();
    datos.vidaActual = vidaActual;
    datos.manaActual = manaActual;
    datos.experiencia =  experiencia;
    datos.nivel = nivel;
    datos.cantidadOro = cantidadOro;
    datos.oroEnAlmacen = oroEnAlmacen;

    auto inventarioTemp = inventario.obtenerTodosLosItems();
    for(unsigned int i = 0; i < inventarioTemp -> size();i++){
        datos.inventario[i] = (*inventarioTemp)[i] -> obtenerIDTCP();
    }

    for(unsigned int i = 0; i < almacen.size();i++){
        datos.almacen[i] = almacen[i] -> obtenerIDTCP();
    }

    return datos;
}

SerializacionEstado Personaje::serializarEstado(){
    SerializacionEstado serEstado = {0};
    serEstado.experiencia       = this->experiencia;
    serEstado.limiteParaSubir   = this->limiteParaSubir;
    serEstado.limiteExpInferior = this->limiteExpInferior;
    serEstado.vidaMaxima        = this->vidaMaxima;
    serEstado.vidaActual        = this->vidaActual;
    serEstado.manaMaximo        = this->manaMaximo;
    serEstado.manaActual        = this->manaActual;
    serEstado.nivel             = this -> nivel;
    return serEstado;
}

SerializacionDibujado Personaje::serializarDibujado(){
    SerializacionDibujado serDibujado = {0};
    strncpy(serDibujado.id, id.c_str(), TAM_ID - 1);
    serDibujado.id[TAM_ID - 1] = 0;
    if (arma == NO_EQUIPADO){
        serDibujado.idArmaEquipada = ID_NO_EQUIPADO;
    }else{
        serDibujado.idArmaEquipada = inventario.obtenerItem(arma)->obtenerIDTCP();
    }
    if (armadura == NO_EQUIPADO){
        serDibujado.idArmaduraEquipada = ID_NO_EQUIPADO;
    }else{
        serDibujado.idArmaduraEquipada = inventario.obtenerItem(armadura)->obtenerIDTCP();
    }
    if (casco == NO_EQUIPADO){
        serDibujado.idCascoEquipado = ID_NO_EQUIPADO;
    }else{
        serDibujado.idCascoEquipado = inventario.obtenerItem(casco)->obtenerIDTCP();
    }
    if (escudo == NO_EQUIPADO){
        serDibujado.idEscudoEquipado = ID_NO_EQUIPADO;
    }else{
        serDibujado.idEscudoEquipado = inventario.obtenerItem(escudo)->obtenerIDTCP();
    }
    serDibujado.idRaza = raza.obtenerIDTCP();
    serDibujado.idClase = clase.obtenerIDTCP();
    serDibujado.idEstado = estado->obtenerIDTCP();
    
    return serDibujado;
}

SerializacionEquipo Personaje::serializarEquipo(){
    SerializacionEquipo ser = {0, 0, 0, 0, 0, {0}};
    ser.armaEquipada        = (uint16_t)arma;
    ser.armaduraEquipada    = (uint16_t)armadura;
    ser.cascoEquipado       = (uint16_t)casco;
    ser.escudoEquipado      = (uint16_t)escudo;
    ser.oro                 = (uint16_t)cantidadOro;
    inventario.serializar(ser.items);
    return ser;
}
