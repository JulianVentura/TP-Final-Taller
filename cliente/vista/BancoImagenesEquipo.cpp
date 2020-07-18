#include <string>
#include <iostream>
#include "BancoImagenesEquipo.h"

BancoImagenesEquipo::BancoImagenesEquipo(EntornoGrafico& entorno)
: textErr(entorno, "assets/equipo/textErr.png"){
	char cantidades[CANT_EQUIPO] = CANT_IMG_EQUIPO;
	for(int i = 0; i < CANT_EQUIPO; i++){
		for(int j = 1;j <= cantidades[i];j++){
			imagenes.emplace(std::piecewise_construct, std::forward_as_tuple(100*i + j),
	 		 std::forward_as_tuple(entorno, "assets/equipo/" + 
	 		 std::to_string(100*i + j) +  ".png"));
		}
	}	
}

void BancoImagenesEquipo::render(uint16_t indice, int x, int y){
	if(indice == 0) return;
	try{
		imagenes.at(indice).setPosicion(x, y);
		imagenes.at(indice).render();
	}catch(std::exception& e){
		textErr.setPosicion(x, y);
		textErr.render();
	}
}
