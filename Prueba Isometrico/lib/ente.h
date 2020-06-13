#ifndef ENTE_H
#define ENTE_H

#include "dibujable.h"
#include "vector2D.h"

class Ente : public Dibujable{
		vector2D posicion;
	public:
		Ente(float x,float y,int ancho,int largo, const char* camino_textura,SDL_Renderer* renderer);
		void mover(vector2D& incremento);
		void tic();
};


#endif /*ENTE_H */