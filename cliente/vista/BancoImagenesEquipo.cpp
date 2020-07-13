#include <string>
#include <iostream>
#include "BancoImagenesEquipo.h"

BancoImagenesEquipo::BancoImagenesEquipo(EntornoGrafico& entorno){
	
	imagenes.emplace(std::piecewise_construct, std::forward_as_tuple(401),
	 std::forward_as_tuple(entorno, "assets/equipo/401.png"));
	imagenes.emplace(std::piecewise_construct, std::forward_as_tuple(402),
	 std::forward_as_tuple(entorno, "assets/equipo/402.png"));
	imagenes.emplace(std::piecewise_construct, std::forward_as_tuple(1),
	 std::forward_as_tuple(entorno, "assets/equipo/1.png"));
	imagenes.emplace(std::piecewise_construct, std::forward_as_tuple(4),
	 std::forward_as_tuple(entorno, "assets/equipo/4.png"));
	/*
	for(int i = 1; i < CANT_IMG_EQUIPO + 1; i++){
		imagenes.emplace_back(entorno, "assets/equipo/" +
		 std::to_string(i) + ".png");
	}
	*/
}

void BancoImagenesEquipo::render(uint16_t indice, int x, int y){
	if(indice == 0) return;
	try{
		imagenes.at(indice).setPosicion(x, y);
		imagenes.at(indice).render();
	}catch(std::exception& e){}
}
