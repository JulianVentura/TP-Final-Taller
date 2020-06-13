#include "dibujable.h"
#include "ente.h"
#include "vector2D.h"

Ente::Ente(float x,float y,int ancho,int largo, const char* camino_textura,SDL_Renderer* renderer)
 	: Dibujable(x,y,ancho,largo,camino_textura,renderer)
 {
 	posicion.x = x;
 	posicion.y = y;
 	marco.x = posicion.x - marco.w/2;
	marco.y = posicion.y - marco.h/2;
 }

void Ente::tic(){
	marco.x = posicion.x - marco.w/2;
	marco.y = posicion.y - marco.h/2;
}

void Ente::mover(vector2D& incremento){
	posicion += incremento;
}