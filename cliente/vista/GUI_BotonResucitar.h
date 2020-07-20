#ifndef __GUI_BOTON_RESUCITAR_H__
#define __GUI_BOTON_RESUCITAR_H__

#include "../vista/GUI_Boton.h"

class GUI_BotonResucitar final : public GUI_Boton{
public:
	GUI_BotonResucitar(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_BOTON_RESUSITAR_H__*/