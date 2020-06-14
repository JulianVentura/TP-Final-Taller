#include "Rectangulo.h"

Rectangulo::Rectangulo(const float inicioX, 
                       const float inicioY, 
                       const float ancho, 
                       const float alto) :
                       inicioX(inicioX),
                       inicioY(inicioY),
                       ancho(ancho),
                       alto(alto){}
Rectangulo::Rectangulo(){}
Rectangulo::Rectangulo(Rectangulo &&otro) : 
Rectangulo(otro.inicioX, otro.inicioY, otro.ancho, otro.alto){}

Rectangulo& Rectangulo::operator=(Rectangulo &&otro){
    inicioX = otro.inicioX;
    inicioY = otro.inicioY;
    ancho   = otro.ancho;
    alto    = otro.alto;
    return *this;
}   

bool Rectangulo::seSuperponeCon(Rectangulo &rectangulo){
    bool seSuperponeX = false;
    bool seSuperponeY = false;

    if (inicioX <= rectangulo.inicioX && 
    (inicioX + ancho) >= rectangulo.inicioX){
        seSuperponeX = true;
    }

    if (rectangulo.inicioX <= inicioX &&
    (rectangulo.inicioX + rectangulo.ancho) >= inicioX){
        seSuperponeX = true;
    }

    if (inicioY <= rectangulo.inicioY && 
    (inicioY + alto) >= rectangulo.inicioY){
        seSuperponeY = true;
    }

    if (rectangulo.inicioY <= inicioY &&
    (rectangulo.inicioY + rectangulo.alto) >= inicioY){
        seSuperponeY = true;
    }

    if (seSuperponeY && seSuperponeX) return true;

    return false;
}

bool Rectangulo::contieneA(Rectangulo &rectangulo){
    bool resultado = false;
    if (rectangulo.inicioX >= inicioX && (rectangulo.inicioX + rectangulo.ancho) <= (inicioX + ancho)){
        if (rectangulo.inicioY >= inicioY && (rectangulo.inicioY + rectangulo.alto) <= (inicioY + alto)){
            resultado = true;
        }
    }
    return resultado;
}
float Rectangulo::obtenerX(){ return inicioX; }
float Rectangulo::obtenerY(){ return inicioY; }
float Rectangulo::obtenerAncho(){ return ancho; }
float Rectangulo::obtenerAlto(){ return alto; }

void Rectangulo::set(float x, float y, float ancho, float alto){
    x = x;
    y = y;
    ancho = ancho;
    alto = alto;
}