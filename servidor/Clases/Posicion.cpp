#include "Posicion.h"
#include <utility>
#include <sstream>
#define ANCHO 1
#define ALTO 1
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
    areaQueOcupa = std::move(Rectangulo(x - ANCHO/2, y - ALTO/2, ANCHO, ALTO));
}

Rectangulo& Posicion::obtenerAreaQueOcupa(){
    return areaQueOcupa;
}

std::string Posicion::imprimirPosicion(){
    std::stringstream resultado;
    resultado << x << "/" << y;
    return std::move(resultado.str());
}
