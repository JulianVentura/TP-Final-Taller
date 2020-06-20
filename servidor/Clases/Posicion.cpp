#include "Posicion.h"
#include <utility>
#include <sstream>
#include <cmath>
#define ANCHO 3
#define ALTO 3
Posicion::Posicion(float x, float y) : 
                   areaQueOcupa(x - ANCHO/2, y - ALTO/2, ANCHO, ALTO),
                   x(x), 
                   y(y){}

Posicion::Posicion() : areaQueOcupa(0, 0, 0, 0), x(0), y(0){} 

Posicion::Posicion(Posicion &otro) : Posicion(otro.x, otro.y) {}

Posicion::Posicion(Posicion &&otro) : Posicion(otro.x, otro.y) {}

Posicion& Posicion::operator=(Posicion &&otro){
    x = otro.x;
    y = otro.y;
    areaQueOcupa = std::move(otro.areaQueOcupa);
    return *this;
}

void Posicion::PosicionAvanzarHaciaArriba(float desplazamiento){
    y -= desplazamiento;
    actualizarArea(); 
}
void Posicion::PosicionAvanzarHaciaAbajo(float desplazamiento){
    y += desplazamiento;
    actualizarArea(); 
}
void Posicion::PosicionAvanzarHaciaDerecha(float desplazamiento){
    x += desplazamiento;
    actualizarArea(); 
}
void Posicion::PosicionAvanzarHaciaIzquierda(float desplazamiento){
    x -= desplazamiento;
    actualizarArea(); 
}

void Posicion::actualizarArea(){
    areaQueOcupa = std::move(quadtree::Box<float>(x - ANCHO/2, y - ALTO/2, ANCHO, ALTO));
}

const quadtree::Box<float>& Posicion::obtenerAreaQueOcupa() const{
    return areaQueOcupa;
}

float Posicion::longitudMaximaDeColision() const{
    return sqrt(ANCHO * ANCHO + ALTO * ALTO);
}

Posicion Posicion::nuevaPosicionDesplazada(float x, float y) const{
    return std::move(Posicion(this->x + x, this->y + y));
}

std::string Posicion::imprimirPosicion(){
    std::stringstream resultado;
    resultado << x << "/" << y;
    return std::move(resultado.str());
}

const float Posicion::obtenerX() const{
    return x;
}
const float Posicion::obtenerY() const{
    return y;
}
