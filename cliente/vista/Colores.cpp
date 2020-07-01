#include "Colores.h"

#define MAX_COLOR_VALUE 0xFF
#define HEXA_INICIO '#'

Colores::Colores(){
	barra_vida = {134,19,19,255};
	barra_vida2 = {78,16,16,255};
	barra_mana= {6,49,130,255};
	barra_mana2= {7,36,90,255};
	barra_exp = {248,186,107,255};
	barra_exp2 = {194,143,84,255};
	barra_fondo = {24,24,24,255};
	inv_frente = {80,57,37,255};
	inv_fondo = {46,31,21,255};
	inv_fondo2 = {57,38,26,255};
	inv_sombra = {33,22,14,255};
	inv_luz = {94,75,51,255};
	chat_fondo = {0,0,0,125};
	chat_entrada = {0,0,0,80};
	chat_borde = {0,0,0,255};
	chat_texto = {255,255,255,240};
	chat_texto_privado = {237,211,35,240};
}

SDL_Color Colores::colorDesdeHexa(std::string hexa) {
	if (hexa[0] == HEXA_INICIO) 
        hexa.erase(0, 1);
    unsigned long valor = std::stoul(hexa, nullptr, 16);
    SDL_Color temp_color = {};
    temp_color.a = MAX_COLOR_VALUE;
    temp_color.r = (valor >> 16) & MAX_COLOR_VALUE;
    temp_color.g = (valor >> 8) & MAX_COLOR_VALUE;
    temp_color.b = (valor >> 0) & MAX_COLOR_VALUE;
    return temp_color;
}
