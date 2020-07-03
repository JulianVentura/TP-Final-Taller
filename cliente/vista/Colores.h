#ifndef __COLORES_H__
#define __COLORES_H__

#include <SDL2/SDL_render.h>
#include <string>

class Colores{
public:
	Colores();
	SDL_Color 
	barra_vida,
	barra_vida2,
	barra_mana,
	barra_mana2,
	barra_exp,
	barra_exp2,
	barra_fondo,
	inv_frente,
	inv_fondo,
	inv_fondo2,
	inv_sombra,
	inv_luz,
	chat_fondo,
	chat_entrada,
	chat_borde,
	chat_texto,
	chat_texto_privado;

	/**
     * @brief Color de SDL dado un color en formato hexadecimal.
     * @param hexa cadena con el color en forma hexadecimal, de la forma:
     * #RRGGBB, donde RR, GG, BB, son números hexadecimales que determinan la 
     * combinación de rojo, verde, azul, respectivamente. 
     */
	static SDL_Color colorDesdeHexa(std::string hexa);
};

#endif /*__COLORES_H__*/
