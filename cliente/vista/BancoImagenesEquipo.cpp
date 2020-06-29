#include <string>
#include "BancoImagenesEquipo.h"

BancoImagenesEquipo::BancoImagenesEquipo(EntornoGrafico& entorno){
	imagenes.emplace_back(entorno, "assets/equipo/1.png");
	for(int i = 1; i < CANT_IMG_EQUIPO + 1;i++){
		imagenes.emplace_back(entorno, "assets/equipo/" +
		 std::to_string(i) + ".png");
	}
}

void BancoImagenesEquipo::render(unsigned int indice, int x, int y){
	if(indice == 0) return;
	imagenes[indice].setPosicion(x, y);
	imagenes[indice].render();
}
