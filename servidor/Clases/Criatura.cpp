#include "Criatura.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Configuraciones.h"
#include "FabricaDeItems.h"
#include "BolsaDeItems.h"
#include "Divulgador.h"
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
                                       objetivo(nullptr),
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
    std::stringstream nuevoId;
    nuevoId << this->id << numero;
    id = nuevoId.str();
}

const std::string Criatura::obtenerId() const {
    std::stringstream _id;
    _id << this->id << "#" << diferenciador;
    return _id.str();
}


bool Criatura::recibirDanio(int danio, Entidad *atacante){
    Divulgador *divulgador = Divulgador::obtenerInstancia();
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::stringstream mensaje;
    if (config->seEsquivaElGolpe(this)){
        //Informarle a atacante que el golpe se esquiva.
        mensaje << "El oponente ha esquivado el golpe";
        divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
        return true;
    }
    unsigned int experiencia = config->calcularExpPorGolpe(this,
                                                           atacante,
                                                           danio);
    atacante->obtenerExperiencia(experiencia);
    mensaje << "Realizas " << danio << "de daño";
    divulgador->encolarMensaje(atacante->obtenerId(), mensaje.str());
    if (vidaActual - danio <= 0){
        this->vidaActual = 0;
        experiencia = config->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(experiencia);
        dropearItems(atacante);
    }else{
        this->vidaActual -= danio;
    }
    return true;
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
        //No hay riesgo de RC al cargar algo a mapa porque este es el unico hilo que accede a el.
        this->mapaAlQuePertenece->cargarEntidad(std::unique_ptr<BolsaDeItems>(new BolsaDeItems(this->posicion, item)));
    }
    this->mapaAlQuePertenece->eliminarEntidad(id);
}

//Estado / IA

void Criatura::actualizarEstado(double tiempo){
    if (vidaActual <= 0){
        tiempoTranscurrido += tiempo;
        if (tiempoTranscurrido >= tiempoDespawn){
            mapaAlQuePertenece->eliminarEntidad(this);
            finalizado = true;
        }
    }else if (objetivo){
		continuarAtacando();
	}else{
		buscarObjetivo();	
	}
}

void Criatura::buscarObjetivo(){
    quadtree::Box<float> areaVisibilidad = std::move(posicion.obtenerAreaCentradaEnPosicion(radioVisibilidad));
    std::vector<Entidad*> entidades = mapaAlQuePertenece->obtenerEntidades(std::move(areaVisibilidad));
	std::vector<Entidad*>::iterator it = entidades.begin();
	while (!objetivo && it != entidades.end()){
		(*it)->serAtacadoPor(this);	
	}
}

void Criatura::perseguir(){
    if (!objetivo) return;
	Posicion nuevaPos = std::move(this->posicion.perseguir(objetivo->obtenerPosicion(), this->desplazamiento));
	mapaAlQuePertenece->actualizarPosicion(this, std::move(nuevaPos));
}

bool Criatura::haFinalizado(){
    return finalizado;
}

//Ataque


void Criatura::atacar(Personaje *personaje){
	this->objetivo = personaje;
	this->arma->atacar(personaje, this, mapaAlQuePertenece); //Si esto falla es porque no me da el radio de ataque.
	perseguir();
}

void Criatura::atacar(Criatura *objetivo){
    //No puedo atacar a una criatura.
}

void Criatura::serAtacadoPor(Criatura *atacante){
    //No hago nada, no me puede atacar una criatura.
}

void Criatura::serAtacadoPor(Personaje *atacante){
    atacante->atacar(this);
}

void Criatura::serAtacadoPor(Entidad *atacante){
    atacante->atacar(this);
}

void Criatura::continuarAtacando(){
    Personaje *temp = this->objetivo;
	this->objetivo = nullptr;
    float distancia = this->posicion.calcularDistancia(temp->obtenerPosicion());
	if (distancia > radioAgresividad) return;
	//Esto se hace porque quizas el objetivo muere o entra en estado pacifico y no puede ser atacado, entonces se tiene que liberar el objetivo.
	serAtacadoPor(temp);
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
