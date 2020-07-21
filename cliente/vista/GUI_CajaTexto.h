#ifndef __GUI_CAJA_TEXTO_H__
#define __GUI_CAJA_TEXTO_H__

#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"

#define ALTO_CARACTER  12
#define ANCHO_CARACTER 10

/*
*	Dibuja un rectangulo y la cadena "entrada". Si la cantidad de caracteres
*	de entrada excede el ancho del rectángulo, dibuja el fragmento que encaja
*	priorizando las últimas letras.
*	Tambien se muestra un cursor que requiere de la llamada periódica del
*	método actualizar.
*/

class GUI_CajaTexto : public IRendereable{
protected:
	Colores& paleta;
	int tiempo;
	bool mostrar_cursor;
	bool en_foco;

public:
	std::string entrada;
	SDL_Rect marco_entrada;
	unsigned int caracteres_max;
	GUI_CajaTexto(EntornoGrafico& entorno, Colores& paleta);
	void actualizar(unsigned int delta_t) override;
	void render() override;
	void darFoco(bool en_foco);
	void actualizarDimension();
};
#endif /*__GUI_CAJA_TEXTO_H__*/
