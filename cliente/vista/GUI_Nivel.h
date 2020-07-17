#ifndef __GUI_NIVEL_H_
#define __GUI_NIVEL_H_

#include <string>
#include <atomic>

#include "../vista/IRendereable.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

class GUI_Nivel : public IRendereable{
private:
	std::atomic<uint16_t>& nivel;
	Colores& paleta;
	Imagen imagen;
	int x,y;
public:
	GUI_Nivel(EntornoGrafico& entorno, Colores& paleta, std::atomic<uint16_t>& nivel);
	void render();
	void actualizarDimension();
};

#endif /*__NIVEL_H_*/