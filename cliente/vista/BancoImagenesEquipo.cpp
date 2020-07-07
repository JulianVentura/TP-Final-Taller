#include <string>
#include <iostream>
#include "BancoImagenesEquipo.h"

BancoImagenesEquipo::BancoImagenesEquipo(EntornoGrafico& entorno){
	imagenes.emplace_back(entorno, "assets/equipo/1.png");
	imagenes.emplace_back(entorno, "assets/equipo/1.png");
	imagenes.emplace_back(entorno, "assets/equipo/2.png");
	imagenes.emplace_back(entorno, "assets/equipo/3.png");
	imagenes.emplace_back(entorno, "assets/equipo/4.png");
	/*
	for(int i = 1; i < CANT_IMG_EQUIPO + 1; i++){
		imagenes.emplace_back(entorno, "assets/equipo/" +
		 std::to_string(i) + ".png");
	}
	*/
}

void BancoImagenesEquipo::render(uint16_t indice, int x, int y){
	if(indice == 0) return;
	if(indice > CANT_IMG_EQUIPO){
		std::cerr << "Indice no encontrado:" << indice;
		return;
	} 
	imagenes[indice].setPosicion(x, y);
	imagenes[indice].render();
}
