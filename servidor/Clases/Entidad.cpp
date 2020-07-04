#include "Entidad.h"
#include "Mapa.h"

Entidad::Entidad(std::string unId) : 
                 Posicionable(0, 0, 0, 0),
                 vidaMaxima(0),
                 vidaActual(0),
                 manaMaximo(0),
                 manaActual(0),
                 fuerza(0),
                 inteligencia(0),
                 agilidad(0),
                 constitucion(0),
                 nivel(0),
                 id(unId),
                 arma(nullptr),
                 inventario(){}


const quadtree::Box<float>& Entidad::obtenerArea() const{
    return posicion.obtenerAreaQueOcupa();
}

bool Entidad::colisionaCon(const Colisionable &otro) const{
    return otro.colisionaCon(posicion.obtenerAreaQueOcupa());
}

bool Entidad::colisionaCon(const quadtree::Box<float> &area) const{
    return posicion.obtenerAreaQueOcupa().intersects(area);
}
std::string Entidad::obtenerId(){
    return std::move(id);
}

void Entidad::actualizarEstado(double tiempo, Mapa *mapa){
    /* Actualizar estado */
    /*
    1- Regenerar vida
    2- Regenerar mana
    3- Moverse
    */
    Posicion nuevaPosicion = posicion.mover();
    mapa->actualizarPosicion(this, std::move(nuevaPosicion));
}


void Entidad::atacar(Entidad *objetivo){
    arma->atacar(objetivo, this);
}
void Entidad::recibirDanio(int danio, Entidad *atacante){
    Configuraciones *configuraciones = Configuraciones::obtenerInstancia();
    this->vidaActual -= danio;
    unsigned int experiencia = configuraciones->calcularExpPorGolpe(this,
                                                                    atacante,
                                                                    danio);
    atacante->obtenerExperiencia(experiencia);
    if (vidaActual <= 0){
        experiencia = configuraciones->calcularExpPorMatar(this, atacante);
        atacante->obtenerExperiencia(experiencia);
        dropearItems();
    }
}

void Entidad::consumirMana(unsigned int cantidad){
    manaActual -= cantidad;
    if (manaActual < 0) manaActual = 0;
}

void Entidad::obtenerExperiencia(unsigned int cantidad){
    //Do nothing
}

void Entidad::dropearItems(){
    //TODO
}

void Entidad::equipar(Arma *unArma){
    arma = unArma;
}

void Entidad::almacenar(std::unique_ptr<Item> item){
    //Guarda que si falla se pierde el item.
    inventario.almacenar(std::move(item));
}


Entidad::~Entidad(){}
