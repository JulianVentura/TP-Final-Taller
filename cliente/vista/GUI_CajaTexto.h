#ifndef __GUI_CAJA_TEXTO_H__
#define __GUI_CAJA_TEXTO_H__

#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"

#define ALTO_CARACTER  12
#define ANCHO_CARACTER 10

class GUI_CajaTexto : public IRendereable{
protected:
	Colores& paleta;
public:
	std::string entrada;
	SDL_Rect marco_entrada;
	unsigned int caracteres_max;
	GUI_CajaTexto(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void actualizarDimension();
};
#endif /*__GUI_CAJA_TEXTO_H__*/