#include "Entidad.h"
#include "Mapa.h"

Entidad::Entidad(unsigned int vida, 
                 unsigned int mana,
                 unsigned int valorAgilidad,
                 unsigned int unNivel,
                 float x,
                 float y, 
                 std::string &unId) : 
                 Posicionable(x, y),
                 vidaMaxima(vida),
                 vidaActual(vida),
                 agilidad(valorAgilidad),
                 nivel(unNivel),
                 id(unId),
                 arma(0,0,0){}


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
    arma.atacar(objetivo, this);
}
void Entidad::recibirDanio(unsigned int danio, Entidad *atacante){
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

void Entidad::obtenerExperiencia(unsigned int cantidad){
    //Do nothing
}

void Entidad::dropearItems(){
    //TODO
}

Entidad::~Entidad(){}
