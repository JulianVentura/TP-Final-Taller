#ifndef __BANCO_IMAGENES_EQUIPO_H__
#define __BANCO_IMAGENES_EQUIPO_H__

#include <vector>

#include "../vista/EntornoGrafico.h"
#include "../vista/Imagen.h"

#define CANT_IMG_EQUIPO 2

class BancoImagenesEquipo{
private:
	std::vector<Imagen> imagenes;
public:
	BancoImagenesEquipo(EntornoGrafico& entorno);
	void render(unsigned int indice, int x, int y);
};

#endif /*__BANCO_IMAGENES_EQUIPO_H__*/
