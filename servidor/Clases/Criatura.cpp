#include "Criatura.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Configuraciones.h"
#include "FabricaDeItems.h"
#include "BolsaDeItems.h"
#include "Divulgador.h"
#include "ErrorServidor.h"
#include <sstream>
#include <utility>
#include <memory>
#include <sstream>

Criatura::Criatura(float x, float y, std::string unId) : 
                                       Entidad(unId),
                                       diferenciador(0),
                                       tiempoDespawn(0),
                                       tiempoTranscurrido(0),
                                       radioAgresividad(0),
                                       radioVisibilidad(0),
                                       finalizado(false),
                                       idObjetivo(""),
                                       arma(nullptr){
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los stats
    vidaMaxima = config->obtenerCriaturaVidaMax(unId);
    vidaActual = vidaMaxima;
    manaMaximo = config->obtenerCriaturaManaMax(unId);
    manaActual = manaMaximo;
    nivel = config->obtenerCriaturaNivel(unId);
    fuerza = config->obtenerCriaturaFuerza(unId);
    inteligencia = config->obtenerCriaturaInteligencia(unId);
    agilidad = config->obtenerCriaturaAgilidad(unId);
    constitucion = config->obtenerCriaturaConstitucion(unId);
    //Seteo el arma
    std::string idArma = config->obtenerCriaturaIdArma(id);
    this->arma = fabricaItems->crearArma(idArma);
    //Su posicion, area que ocupa y movimiento
    float ancho = config->obtenerCriaturaAncho(unId);
    float alto = config->obtenerCriaturaAncho(unId);
    posicion = std::move(Posicion(x, y, ancho, alto));
    desplazamiento = config->obtenerCriaturaVelDesplazamiento(unId);
    //Tiempo despawn
    tiempoDespawn = config->obtenerCriaturaTiempoDespawn(unId);
    //Atributos de IA
    radioAgresividad = config->obtenerCriaturaRadioAgresividad(unId);
    radioVisibilidad = config->obtenerCriaturaRadioVisibilidad(unId);

}

void Criatura::agregarDiferenciador(const unsigned int numero){
    diferenciador = numero;
}

const std::string Criatura::obtenerId() const {
    std::stringstream _id;
    _id << this->id << "#" << diferenciador;
    return _id.str();
}


std::string Criatura::recibirDanio(int danio, Entidad *atacante){
    this->idObjetivo = atacante->obtenerId();   //Mi objetivo sera mi ultimo atacante.
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::stringstream mensaje;
    if (config->seEsquivaElGolpe(this)){
        //Informarle a atacante que el golpe se esquiva.
        return "El oponente ha esquivado el golpe";
    }
    unsigned int experiencia = config->calcularExpPorGolpe(this,
                                                           atacante,
                                                           danio);
    atacante->obtenerExperiencia(experiencia);
    mensaje << "Realizas " << danio << "de danio";
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
    if (vidaActual - danio <= 0){
        this->vidaActual = 0;
        experiencia = config->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(experiencia);
        dropearItems(atacante);
    }else{
        this->vidaActual -= danio;
    }
    return mensaje.str();
}


void Criatura::dropearItems(Entidad *atacante){
    FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    TipoDrop tipo = config->calcularDrop(id);
    if (tipo == ORO){
        unsigned int cantidad = config->calcularDropOro(this);
        atacante->recibirOro(cantidad);
    }else if (tipo == ITEM){
        //Siempre se va a obtener un drop
        Item* item = fabricaItems->obtenerItemAleatorio(id);
        //No hay riesgo de RC al cargar algo a mapa porque este es el unico hilo que accede a el.
        this->mapaAlQuePertenece->cargarEntidad(std::unique_ptr<BolsaDeItems>(new BolsaDeItems(this->posicion, item)));
    }
}

//Estado / IA

void Criatura::actualizarEstado(double tiempo){
    if (vidaActual <= 0){
        tiempoTranscurrido += tiempo;
        if (tiempoTranscurrido >= tiempoDespawn) finalizado = true;
    }else if (idObjetivo != ""){
		continuarAtacando();
	}else{
		buscarObjetivo();	
	}
}

void Criatura::buscarObjetivo(){
    quadtree::Box<float> areaVisibilidad = std::move(posicion.obtenerAreaCentradaEnPosicion(radioVisibilidad));
    std::vector<Entidad*> entidades = mapaAlQuePertenece->obtenerEntidades(std::move(areaVisibilidad));
	std::vector<Entidad*>::iterator it = entidades.begin();
	while ((idObjetivo == "") && it != entidades.end()){
		(*it)->serAtacadoPor(this);
        ++it;
	}
}

void Criatura::perseguir(Personaje *objetivo){
	Posicion nuevaPos = std::move(this->posicion.perseguir(objetivo->obtenerPosicion(), this->desplazamiento));
	mapaAlQuePertenece->actualizarPosicion(this, std::move(nuevaPos));
}

bool Criatura::haFinalizado(){
    if (finalizado){
        mapaAlQuePertenece->eliminarEntidad(this);
        mapaAlQuePertenece->eliminarCriatura();
    }
    return finalizado;
}

//Ataque


std::string Criatura::atacar(Personaje *personaje){
    idObjetivo = personaje->obtenerId();
	arma->atacar(personaje, this, mapaAlQuePertenece); //Si esto falla es porque no me da el radio de ataque.
	perseguir(personaje);
    return "";
}

std::string Criatura::atacar(Criatura *objetivo){
    return "";
}

void Criatura::serAtacadoPor(Criatura *atacante){
    //No hago nada, no me puede atacar una criatura.
}

void Criatura::serAtacadoPor(Personaje *atacante){
    atacante->atacar(this);
}

void Criatura::continuarAtacando(){
    Entidad *objetivo = nullptr;
    try{ 
        objetivo = mapaAlQuePertenece->obtener(this->idObjetivo);
    }catch(const ErrorServidor &e){
        idObjetivo = ""; //Solo sucedera si el jugador se desconecta o teletransporta.
    }
    idObjetivo = "";
    float distancia = this->posicion.calcularDistancia(objetivo->obtenerPosicion());
	if (distancia > radioAgresividad) return;
	//Esto se hace porque quizas el objetivo muere o entra en estado pacifico y no puede ser atacado, entonces se tiene que liberar el objetivo.
	objetivo->serAtacadoPor(this);
}

//Comercio

void Criatura::interactuar(Estado *estado, Cliente *cliente){
    //No hago nada
}

void Criatura::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    //No hago nada
}

void Criatura::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    //No hago nada
}

void Criatura::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    //No hago nada
}

void Criatura::vender(Item* item, Personaje *personaje, Cliente *cliente){
    //No hago nada
}

void Criatura::listar(Personaje *personaje, Cliente *cliente){
    //No hago nada
}

Criatura::~Criatura(){}
