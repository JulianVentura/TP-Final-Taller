#include "Posicion.h"
#include "Configuraciones.h"
#include <utility>
#include <sstream>
#include <cmath>

Posicion::Posicion(float unX, float unY, float anch, float alt) : 
                   x(unX), 
                   y(unY),
                   ancho(anch),
                   alto(alt),
                   desplazamientoX(0),
                   desplazamientoY(0),
                   areaQueOcupa(x - ancho/2, y - alto/2, ancho, alto){
}

Posicion::Posicion() : x(0), y(0), ancho(0), alto(0), areaQueOcupa(0, 0, 0, 0){} 

Posicion::Posicion(Posicion &&otro) : Posicion(otro.x, otro.y, otro.ancho, otro.alto) {}

Posicion& Posicion::operator=(Posicion &&otro){
    x = otro.x;
    y = otro.y;
    ancho = otro.ancho;
    alto = otro.alto;
    areaQueOcupa = std::move(otro.areaQueOcupa);
    return *this;
}

void Posicion::actualizarPosicion(Posicion &&otro){
    //Solo actualizo coordenadas, no cambio el area que ocupo.
    this->x = otro.x;
    this->y = otro.y;
    actualizarArea();
}

void Posicion::moverHaciaArriba(float desplazamiento){
    desplazamientoY = -1 * desplazamiento;
    desplazamientoX = 0;
}
void Posicion::moverHaciaAbajo(float desplazamiento){
    desplazamientoY = desplazamiento;
    desplazamientoX = 0;
}
void Posicion::moverHaciaDerecha(float desplazamiento){
    desplazamientoX = desplazamiento;
    desplazamientoY = 0;
}
void Posicion::moverHaciaIzquierda(float desplazamiento){
    desplazamientoX = -1 * desplazamiento;
    desplazamientoY = 0;
}

Posicion Posicion::mover(){
    Posicion nuevaPosicion(x + desplazamientoX, y + desplazamientoY, ancho, alto);
    return nuevaPosicion;
}


void Posicion::detenerse(){
    desplazamientoX = 0;
    desplazamientoY = 0;
}

void Posicion::actualizarArea(){
    areaQueOcupa = std::move(quadtree::Box<float>(x - ancho/2, y - alto/2, ancho, alto));
}

const quadtree::Box<float>& Posicion::obtenerAreaQueOcupa() const{
    return areaQueOcupa;
}

float Posicion::longitudMaximaDeColision() const{
    return sqrt(ancho * ancho + alto * alto);
}

//Se utiliza para algo esto? Muy similar a Posicion::mover()
Posicion Posicion::nuevaPosicionDesplazada(float x, float y) const{
    return std::move(Posicion(this->x + x, this->y + y, ancho, alto));
}
//DEBUG
std::string Posicion::imprimirPosicion(){
    std::stringstream resultado;
    resultado << x << "/" << y;
    return std::move(resultado.str());
}
//


const float Posicion::obtenerX() const{
    return x;
}

const float Posicion::obtenerY() const{
    return y;
}

float Posicion::calcularDistancia(const Posicion &otra) const{
    float deltaX = otra.x - x;
    float deltaY = otra.y - y;
    float distancia = deltaX * deltaX + deltaY * deltaY;
    return sqrt(distancia);
}