#ifndef __BANCO_IMAGENES_EQUIPO_H__
#define __BANCO_IMAGENES_EQUIPO_H__

#include <vector>
#include <map>
#include "../vista/EntornoGrafico.h"
#include "../vista/Imagen.h"

#define CANT_EQUIPO 5
#define CANT_IMG_EQUIPO {9,3,3,2,2}

class BancoImagenesEquipo{
private:
	Imagen textErr;
	std::unordered_map<int, Imagen> imagenes;
public:
	explicit BancoImagenesEquipo(EntornoGrafico& entorno);
	void render(uint16_t indice, int x, int y);
};

#endif /*__BANCO_IMAGENES_EQUIPO_H__*/
