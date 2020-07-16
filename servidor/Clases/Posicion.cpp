#include "Posicion.h"
#include "Configuraciones.h"
#include <utility>
#include <sstream>
#include <cmath>
////////////////////METODOS AUXILIARES////////////////////

static bool floatComp(float a, float b, float epsilon = 0.1){
    return fabs(a - b) < epsilon;
}

/////////////////////////METODOS//////////////////////////

Posicion::Posicion(float x, float y, float anch, float alt) : 
                   pos(x, y),
                   ancho(anch),
                   alto(alt),
                   desplazamiento(0,0),
                   areaQueOcupa(x - ancho/2, y - alto/2, ancho, alto){
}

Posicion::Posicion() : pos(0,0), 
                       ancho(0), 
                       alto(0), 
                       desplazamiento(0, 0),
                       areaQueOcupa(0, 0, 0, 0){}


Posicion::Posicion(const quadtree::Vector2<float> &unaPos, 
                   const quadtree::Vector2<float> &desp, 
                   const float anch, 
                   const float alt) : 
                   pos(unaPos),
                   ancho(anch),
                   alto(alt),
                   desplazamiento(desp){
    actualizarArea();
}

Posicion::Posicion(Posicion &&otro){
    pos = std::move(otro.pos);
    desplazamiento = std::move(otro.desplazamiento);
    ancho = std::move(otro.ancho);
    alto = std::move(otro.alto);
    actualizarArea();
}

Posicion::Posicion(const Posicion &otro){
    pos = otro.pos;
    desplazamiento = otro.desplazamiento;
    ancho = otro.ancho;
    alto = otro.alto;
    actualizarArea();
}

Posicion& Posicion::operator=(Posicion &&otro){
    pos = std::move(otro.pos);
    desplazamiento = std::move(otro.desplazamiento);
    ancho = std::move(otro.ancho);
    alto = std::move(otro.alto);
    areaQueOcupa = std::move(otro.areaQueOcupa);
    return *this;
}

//Me interesa unicamente comparar la posicion, no el resto de los atributos.
bool Posicion::operator==(const Posicion &otro) const{
    bool igualX = floatComp(pos.obtenerX(), otro.pos.obtenerX());
    bool igualY = floatComp(pos.obtenerY(),otro.pos.obtenerY());
    return igualX && igualY;
}

void Posicion::actualizarPosicion(Posicion &&otro){
    //Solo actualizo coordenadas, no cambio el area que ocupo.
    this->pos = std::move(otro.pos);
    actualizarArea();
}

void Posicion::moverHaciaArriba(float factorDesplazamiento){
    desplazamiento = std::move(quadtree::Vector2<float>(0, -1) * factorDesplazamiento);
}
void Posicion::moverHaciaAbajo(float factorDesplazamiento){
    desplazamiento = std::move(quadtree::Vector2<float>(0, 1) * factorDesplazamiento);
}
void Posicion::moverHaciaDerecha(float factorDesplazamiento){
    desplazamiento = std::move(quadtree::Vector2<float>(1, 0) * factorDesplazamiento);
}
void Posicion::moverHaciaIzquierda(float factorDesplazamiento){
    desplazamiento = std::move(quadtree::Vector2<float>(-1, 0) * factorDesplazamiento);
}

Posicion Posicion::mover(const double tiempo) const{
    Posicion nuevaPosicion(pos + desplazamiento * (float)tiempo, desplazamiento, ancho, alto);
    return nuevaPosicion;
}


void Posicion::detenerse(){
    desplazamiento = std::move(quadtree::Vector2<float>(0, 0));
}

void Posicion::actualizarArea(){
    areaQueOcupa = std::move(quadtree::Box<float>(pos.obtenerX() - ancho/2, pos.obtenerY() - alto/2, ancho, alto));
}

const quadtree::Box<float>& Posicion::obtenerAreaQueOcupa() const{
    return areaQueOcupa;
}

float Posicion::longitudMaximaDeColision() const{
    return sqrt(ancho * ancho + alto * alto);
}

Posicion Posicion::nuevaPosicionDesplazada(float x, float y) const{
    return std::move(Posicion(pos.obtenerX() + x, pos.obtenerY() + y, ancho, alto));
}

const float Posicion::obtenerX() const{
    return pos.obtenerX();
}

const float Posicion::obtenerY() const{
    return pos.obtenerY();
}

float Posicion::calcularDistancia(const Posicion &otra) const{
    return pos.calcularDistancia(otra.pos);
}

Posicion Posicion::perseguir(const Posicion &otraPosicion, 
                             const float factorDesplazamiento, 
                             const double tiempo) const{
    float distancia = pos.calcularDistancia(otraPosicion.pos);
    if (distancia <= factorDesplazamiento * tiempo){
        return otraPosicion;
    }
    quadtree::Vector2<float> temp = (otraPosicion.pos - pos);
	temp.normalizar();
	return Posicion(pos + temp * factorDesplazamiento * (float)tiempo, desplazamiento, ancho, alto);
}

const quadtree::Box<float> Posicion::obtenerAreaCentradaEnPosicion(float radio) const{
    return quadtree::Box<float>(pos.obtenerX() - radio, pos.obtenerY() - radio, radio*2, radio*2);
}

//Serializacion
struct PosicionEncapsulada Posicion::serializarPosicion() const{
    struct PosicionEncapsulada posEncap = {{0}, pos.obtenerX(), pos.obtenerY()};
    return posEncap;
}